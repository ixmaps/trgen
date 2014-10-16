//
// File: traceroute.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include "QUrl"
#include "traceroute.h"

Traceroute::Traceroute(QString& dest, QHostAddress& dest_ip, const QString& submitter) : dest(dest), dest_ip(dest_ip), submitter(submitter) {
	this->privacy = 8;
	this->timeout = 1;
//#ifdef Q_WS_WIN
	this->protocol = icmp;
//#else	
//	this->protocol = udp;
//#endif
	this->maxhops = 255;
	this->attempts = 4;
	this->status = incomplete;
}

TRItem::TRItem(tri_status status, QHostAddress *ip_addr, int rtt_ms) : status(status), ip_addr(ip_addr), rtt_ms(rtt_ms) {}

TRItem::~TRItem() {
	delete ip_addr;
}

void
Traceroute::add_item(int hop_num, unsigned int attempt, TRItem *tr_item) {
	if ( attempt >= MAX_ATTEMPTS )
		return;  // maybe throw an exception?
	while ( items[attempt].count() < hop_num ) 
		items[attempt].append(new TRItem(TRItem::timed_out, new QHostAddress(QHostAddress::Null), -1));
	if ( items[attempt].count() == hop_num ) {
		items[attempt].append(tr_item);
	} else {
		// FIXME: verify that this doesn't leak memory
		items[attempt].replace(hop_num, tr_item);
	}
}

QString&
Traceroute::format() {
	http_repr.clear();
	http_repr += "dest="+dest;
	http_repr += "&dest_ip="+dest_ip.toString();
	http_repr += "&submitter="+QUrl::toPercentEncoding(submitter);
	http_repr += "&zip_code="+QUrl::toPercentEncoding(zip_code);
	http_repr += "&client="+QUrl::toPercentEncoding(client);
	http_repr += "&cl_ver="+QUrl::toPercentEncoding(cl_ver);
	http_repr += "&privacy="+QString("%1").arg(privacy);
	http_repr += "&timeout="+QString("%1").arg(timeout);
	http_repr += "&protocol="+QString("%1").arg(static_cast<char>(protocol));
	http_repr += "&maxhops="+QString("%1").arg(maxhops);
	http_repr += "&attempts="+QString("%1").arg(attempts);
	http_repr += "&status="+QString("%1").arg(static_cast<char>(status));

	int n_items = 0;
	for ( int a=0; a < attempts; a++ ) {
		for ( int h=0; h < items[a].count(); h++ ) {
			TRItem *ti = items[a][h];
			QString suffix = QString("_%1_%2=").arg(h+1).arg(a+1);
			QString status = QString("%1").arg(static_cast<char>(ti->status));
			http_repr += "&status"+suffix+status;
			http_repr += "&ip_addr"+suffix+ti->ip_addr->toString();
			http_repr += "&rtt_ms"+suffix+QString("%1").arg(ti->rtt_ms);
			n_items++;
		}
	}
	http_repr += "&n_items="+QString("%1").arg(n_items);
	return http_repr;
}


