//
// File: ServerComm.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include <QtGui>
#include <QtDebug>
#include <QBuffer>
#include <QUrl>
#include <cstring>

#include "ServerComm.h"
#include "HttpGet.h"
#include "TrHttp.h"


#include <QHttp>

ServerComm::ServerComm(QWidget* owner) {
	this->owner = owner;
}


/** Do an HTTP GET of the directory on the server that has the 
 *  available traceroute sets.  The directory listing is parsed
 *  for links, and these are appended to the trsets vector.
 */
bool ServerComm::getTrSets(QStringList& trsets, bool popupOnError) {
	static bool in_progress = false;
	
	if ( in_progress )
		return false;
	//in theory, a race condition is here.
	in_progress = true;
	trsets.clear();

	QBuffer buf;
	buf.open(QBuffer::WriteOnly);
	QUrl url("http://trgen.ixmaps.ca/trsets/");
	HttpGet hget(url, &buf);
	qDebug() << "HttpGet error " << hget.error();
	QHttp::Error err = hget.error();
	if ( err != QHttp::NoError ) {
		msgConnFailure(err, popupOnError);
		in_progress = false;
		return false;
	} 

	// scan the Apache directory listing.  This makes it easy to change deployment
	// of batch trace files.  
	// To see what this is parsing, fetch the link in a browser and view source.
	char prefix_str[] = "<a href=\"";
	qDebug() << "prefix_str len is " << sizeof(prefix_str);
	QByteArray ba = buf.buffer();
	char *s = ba.data();
	qDebug() << "from server got: " << s;
	char *e = s + ba.count() - (sizeof(prefix_str)+2);  // guard against read past buffer end
	while ( s < e ) {
		// look for <a href="something.trset"
		if ( strncmp(s, prefix_str, sizeof(prefix_str)-1) == 0 ) {
			// found a likely URL
			char *token = s+sizeof(prefix_str)-1;
			char *p;
			for ( p = token; *p != '"'; p++ ) {
				if ( p >= e )
					goto end_buffer;
			}
			*p = '\0';	// stomp the closing quote -> string terminator
			if ( token[0] == '.' && token[1] == '/' )
				token += 2;	// ignore superfluous ./ in ./something.trset

			// Apache directory listing contains a few unwanted URLs beginning with ? or /
			// restrict filenames to those ending with ".trset"
			if ( token[0] != '?' && token[0] != '/' && strcmp(p-6, ".trset") == 0 ) {
				QString qstr(token);
				trsets << qstr;
				qDebug() << "getTrSets got " << qstr.toAscii().data();
			}
			s = p+1;
		} else
			s++;
	} 
end_buffer:
	in_progress = false;
	return true;
}

int ServerComm::msgConnFailure(QHttp::Error err, bool popupOnError) {
	int rc;
	switch ( err ) {
	case QHttp::HostNotFound:           rc = TrStatus::ERR_HOST_NOT_FOUND; break;
	case QHttp::ConnectionRefused:      rc = TrStatus::ERR_CONNECTION_REFUSED; break;
	case QHttp::UnexpectedClose:        rc = TrStatus::ERR_UNEXPECTED_CLOSE; break;
	case QHttp::InvalidResponseHeader:  rc = TrStatus::ERR_INVALID_RESPONSE_HEADER; break;   
	case QHttp::WrongContentLength:     rc = TrStatus::ERR_WRONG_CONTENT_LENGTH; break;
	case QHttp::Aborted:                rc = TrStatus::ERR_REQUEST_ABORTED; break;
	case QHttp::ProxyAuthenticationRequiredError:  rc = TrStatus::ERR_PROXY_AUTH_REQ; break;
	case QHttp::AuthenticationRequiredError:   rc = TrStatus::ERR_AUTH_REQ; break;
	default:                            rc = TrStatus::ERR_UNKNOWN_CONNECT_ERR; break;
	}
	QString why = TrStatus::getErrorTextByCode(rc);
	if ( popupOnError ) {
		QMessageBox::critical(owner, tr("Connection failure"),
		    tr("The connection to the central database is not working.")+" ("+why+")", QMessageBox::Ok);
	}
	return rc;
}

/** Submit a traceroute formatted as HTTP POST data to the server.
 */
bool ServerComm::submitTraceroute(const char *post_data, TrStatus *tstat, bool popupOnError) {
	bool submitted_ok = true;
	qDebug() << post_data;
	TrHttp th("trgen.ixmaps.ca", post_data, tstat);
	subm_waiting_completion = true;
	connect(&th, SIGNAL(done(bool)), this, SLOT(trResultsSubmitted(bool)));
	QTime dieTime = QTime::currentTime().addSecs(5);
	while( QTime::currentTime() < dieTime ) {
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
		if ( !subm_waiting_completion ) {
			break;
		}
	}
	if ( subm_waiting_completion ) {
		if ( popupOnError ) {
			QMessageBox::critical(owner, tr("Connection failure"),
			    tr("The connection to the central database is not working."),
			    QMessageBox::Ok);
		}
		tstat->setError(TrStatus::ERR_SUBMIT_TIMEOUT);
		submitted_ok = false;
	} else {
		//qDebug() << "TrHttp error " << th.error();
		QHttp::Error err = th.error();
		if ( err != QHttp::NoError ) {
			tstat->setError(msgConnFailure(err, popupOnError));
			submitted_ok = false;
		}
	}
	qDebug() << "posting, state " << th.state() << ", error " << th.error();
	qDebug() << "TID=" << tstat->traceroute_id << ", errorMsg=" << tstat->errorMsg;
	return submitted_ok;
}

void ServerComm::trResultsSubmitted(bool error) {
	subm_error_status = error;	// not used, submitTraceroute() queries the TrHttp object for this
	subm_waiting_completion = false;
}

/** Fetch a trset batch file from the server.
  */
bool ServerComm::fetchBatch(const QString& filename, QBuffer& buf, bool popupOnError) {
	buf.open(QBuffer::WriteOnly);
	QString str_url("http://trgen.ixmaps.ca/trsets/");
	str_url += filename;
	QUrl url(str_url);
	HttpGet hget(url, &buf);
	qDebug() << "HttpGet error " << hget.error();
	QHttp::Error err = hget.error();
	if ( err != QHttp::NoError ) {
		msgConnFailure(err, popupOnError);
		return false;
	} 
	return true;
}

