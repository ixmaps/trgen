//
// File: TrWorkItem.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include "TrWorkItem.h"
#include "SettingsDialog.h"
#include "traceroute.h"
#include <iostream>
#include <ctype.h>

#include <cstdlib>			// for atoi()
#include <QHostInfo>

/** A work item describing a single traceroute to be done, a 
 *  container for it's results, and to be submitted to the server.
 */
TrWorkItem::TrWorkItem(const QString &host, TrStatus *tstat, int nprobes) {
	// caller sets nprobes to zero to let us pick a value
	if ( nprobes == 0 )
		nprobes = 4;
	this->tstat = tstat;
	this->nprobes = nprobes;
	name_ok = true;

	// host may be either a hostname or a dotted quad
	QHostInfo hi;			// QHostInfo does host name lookups
	QHostAddress ha(host);		// QHostAddress represents a 32-bit IPv4 address
	if ( ha.isNull() ) {
		hi = QHostInfo::fromName(host);
		QList<QHostAddress> addrs = hi.addresses();
		if ( addrs.count() > 0 )
			ha = addrs.at(0);
		else {
			tstat->setError(TrStatus::ERR_NAME_RESOLV_FAIL);
			name_ok = false;
			return;
		}
	}
	trHost = host;
	trHostAddress = ha;
	qDebug() << "runTraceroute: ha=" << ha.toString().toAscii().data();
}

/** The hostname supplied to the ctor. needs to have been resolved as an IPv4 address 
 *  in order to proceed.  Tell if this is the case.
 */
bool TrWorkItem::isResolved() {
	return name_ok;
}

/** Parse the output from the traceroute doer process.  This output is in the
 *  canonical format as produced by the wmtrcmd or trparse programs, and is a
 * simple table of IPv4 addresses and Round Trip Times in microseconds.
 */
void TrWorkItem::parseCanonical(QByteArray& trData) {
	ip_addrs.clear();
	host_addrs.clear();
	rtts.clear();

	char *s = trData.data();	// buffer scan pointer
	char *e = s + trData.count();	// points just past the buffer end
	int lineTokenCount = 0;		// which token on the current line
	char space_char;		// terminator for current token, a space or newline
	while ( s < e ) {
		char *token = s;
		while ( !isspace(*s) )
			s++;
		if ( s >= e )
			break;	
		space_char = *s;
		*s++ = '\0';
		// Lines consist of an IP address and microsecond Round Trip Times, delimited by spaces.
		// An asterisk denotes an unknown address or time.  All lines should have the
		// same number of RTT tokens, this is not checked here.
		if ( lineTokenCount++ == 0 ) {
			QString qstr(token);
			ip_addrs << qstr;
			QHostAddress hop_addr;
			if ( qstr[0] != '*' ) {
				hop_addr = QHostAddress(qstr);
			}
			host_addrs << hop_addr;
		} else {
			rtts << atoi(token);
		}
		if ( space_char != ' ' ) 
			lineTokenCount = 0;	// newline, next token will be an IP address
		while ( isspace(*s) ) 
			s++;
	}

}

bool TrWorkItem::isRoutingLoop(int startIndex, int endIndex) {
	for ( int i=startIndex; i<endIndex; i++ ) {
		QString ip_addr = ip_addrs[i];
		if ( ip_addr[0] != '*' ) {
			for ( int j=startIndex; j<i; j++ ) {
				if ( ip_addrs[i] == ip_addrs[j] )
					return true;
			}
		}
	}
	return false;
}

/** Format the traceroute for submission to the server.
 */
bool TrWorkItem::formatForServer(QByteArray& ba, int private_ip_cnt, const QString& programVersion) {
	int n_rows = ip_addrs.count();
	int n_rtts = rtts.count();
	qDebug() << "len(ip_addrs)=" << n_rows << ", len(rtts)=" << n_rtts << ", priv_cnt=" << private_ip_cnt;
	if ( n_rows > private_ip_cnt && n_rtts == n_rows*nprobes ) {

		const QString* submitter = SettingsDialog::getUserName();
		const QString* zip_code = SettingsDialog::getUserLocation();
		QString client("tr-sub");
		Traceroute trt(trHost, trHostAddress, *submitter);
		trt.set_zip(const_cast<QString&>(*zip_code));
		trt.set_client(client, const_cast<QString&>(programVersion));
		trt.set_attempts(nprobes);
		// check for a routing loop
		if ( isRoutingLoop(private_ip_cnt, n_rows) ) {
			tstat->setError(TrStatus::ERR_ROUTING_LOOP);
			return false;
		}
		for ( int i=private_ip_cnt; i<n_rows; i++ ) {
			QString ip_addr = ip_addrs[i];
			TRItem::tri_status reply_status = TRItem::timed_out;
			//qDebug("%s", ip_addr.toAscii().data());
			std::cout << ip_addr.toAscii().data();
			if ( ip_addr[0] != '*' ) {
				reply_status = TRItem::replied;
				tstat->hosts_responding++;
			}
			for ( int j=0; j<nprobes; j++ ) {
				int rtt = rtts[j+nprobes*i];
				// rtt convert from microseconds to milliseconds.  Negative values are status.
				if ( rtt > 0 ) 
					rtt /= 1000;
				trt.add_item(i-private_ip_cnt, j, new TRItem(reply_status, &host_addrs[i], rtt));
				//qDebug(" %d", rtt);
				std::cout << " " << rtt;
			}
			std::cout << std::endl;
			tstat->nhops++;
		}
		
		if ( trHostAddress == host_addrs[n_rows-1] ) {
			trt.set_status(Traceroute::complete);
			tstat->host_responded = true;
		}
		QString tr_fmtted(trt.format());
		QByteArray ba_local(tr_fmtted.toAscii());
		ba.append(ba_local);
		return true;
	} else if ( n_rows <= private_ip_cnt ) {
		tstat->setError(TrStatus::ERR_NO_PUBLIC_HOPS);
	} else if ( n_rtts != n_rows*nprobes ) {
		tstat->setError(TrStatus::ERR_LE_MISSING_DATA);  // logic error!
	}
	return false;
}
