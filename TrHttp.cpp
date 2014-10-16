//
// File: TrHttp.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include <QtGui>
#include <QtNetwork>
#include "TrHttp.h"

/** Issue the traceroute submission request.  The HTTP request headers
  * are set for a POST transaction.  A temporary file is opened to
  * receive the results from the server.
  */
TrHttp::TrHttp(const QString &host, const QByteArray &inputStr, TrStatus *tstat) : QHttp(host) {
	this->tstat = tstat;
	tstat->setError(TrStatus::ERR_UNDEFINED);
	connect(this, SIGNAL(requestFinished(int, bool)), this, SLOT(finished(int, bool)));
	//f.setFileName("results.html");
	//f.open(QIODevice::WriteOnly | QIODevice::Truncate);
	f.open();
	QHttpRequestHeader header("POST", "/cgi-bin/gather-tr.cgi");
	header.setValue("Content-Type", "application/x-www-form-urlencoded");
	header.setValue("Host", host.toAscii());
	request(header,inputStr,&f);
}

#define PREFIX_TRACEROUTE_ID	"new traceroute ID="
#define PREFIX_ERROR		"ERROR("

/** Handle completion of the traceroute submission.  If there was no
  * local error, parse the contents of the temporary file which holds
  * the server response.  If the traceroute was successfully added to
  * the database, the traceroute_id is copied into the status object
  * tstat, otherwise the server error code is folded into the IXmaps
  * TrGen error code space.
  */ 
void
TrHttp::finished(int id, bool error) {
	(void)id;
	bool haveStatus = false;
	if (error) {
		tstat->setError(TrStatus::ERR_SERVER_POST_FAILED);
		qDebug("Failed with an error");
		return;
	}
	f.seek(0);
	while ( !f.atEnd() ) {
		QByteArray line = f.readLine();
		int index;
		if ( (index = line.indexOf(PREFIX_TRACEROUTE_ID)) >= 0 ) {
			qDebug() << line;
			tstat->finish(atoll(line.data()+index+strlen(PREFIX_TRACEROUTE_ID)));
			haveStatus = true;
			qDebug() << "got ID=" << tstat->traceroute_id;
		} else if ( (index = line.indexOf(PREFIX_ERROR)) >= 0 ) {
			// expecting  "ERROR(number): text\n"
			qDebug() << line;
			char* s = line.data()+index+strlen(PREFIX_ERROR);
			char *e;
			long serverErrCode = strtol(s, &e, 10);
			if ( serverErrCode < TrStatus::ERR_SERVER_MIN_CODE || TrStatus::ERR_SERVER_MAX_CODE < serverErrCode ) {
				tstat->setError(TrStatus::ERR_SERVER_RANGE_ERR);
			} else {
				tstat->setError(serverErrCode);
			}
			if ( s == e ) {
				// didn't find a digit
				tstat->setError(TrStatus::ERR_SERVER_ERR_BAD_FMT);
			}
			while ( *e && *e != ')' )
				e++;
			if ( *e == ')' )
				e++;
			if ( *e == ':' )
				e++;
			if ( *e == ' ' )
				e++;
			tstat->errorMsg = QString(e);
			tstat->errorMsg = tstat->errorMsg.trimmed();
			qDebug() << "got error " << tstat->errorMsg;
			haveStatus = true;
		}
	}
	f.close();
	if ( !haveStatus ) 
		tstat->setError(TrStatus::ERR_SERVER_FAIL);
}


