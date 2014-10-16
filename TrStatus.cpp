//
// File: TrStatus.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include <QtDebug>
#include "TrStatus.h"

// Only one traceroute is ever done at a time, ergo only one (statically allocated) timer is used.
QTime TrStatus::timer;

QMap<int, QString> *TrStatus::errCodeMap = 0;
QString TrStatus::defaultErrText("generic error");

TrStatus::TrStatus(const QString& h_name, bool in_batch, int op_num) : hostname(h_name) {
	nhops = 0;			// number of hops in the traceroute
	hosts_responding = 0;		// number of hosts along the path that responded
	host_responded = false;		// destination host gave a response
	consistent = false;		// each hop got replies from at most one host
	part_batch = in_batch;		// traceroute was part of a batch
	op_number = op_num;		// increments each time a single trace or batch is requested
	elapsed_time = -1;		// time in ms to do the entire traceroute
	traceroute_id = -1;		// not yet successfully submitted to the database
	timer.start();
	if ( !errCodeMap )		// do this once only
		setupErrCodeMap();
}

void TrStatus::setupErrCodeMap() {
	if ( errCodeMap ) {
		return;
	} else {
		errCodeMap = new QMap<int, QString>();
	}
	if ( errCodeMap ) {
		(*errCodeMap)[ERR_UNDEFINED] = QString("Unspecified error");
		(*errCodeMap)[ERR_NAME_RESOLV_FAIL] = QString("Name resolution failure");
		(*errCodeMap)[ERR_PROCESS_START_FAIL] = QString("Process failed to start");
		(*errCodeMap)[ERR_PROCESS_CRASHED] = QString("Process crashed");
		(*errCodeMap)[ERR_PROCESS_TIMEDOUT] = QString("last waitFor function timed out");
		(*errCodeMap)[ERR_PROCESS_WRITE_ERR] = QString("Process write error");
		(*errCodeMap)[ERR_PROCESS_READ_ERR] = QString("Process read error");
		(*errCodeMap)[ERR_PROCESS_UNKNOWN_ERR] = QString("Unknown process error");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+1] = QString("Traceroute path inconsistent");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+2] = QString("Unable to initialize WinSock");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+3] = QString("Bad command line option");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+4] = QString("PreOpen can't get raw socket");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+5] = QString("Can't resolve hostname");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+6] = QString("Can't resolve localhost");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+7] = QString("Open can't get raw socket");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+8] = QString("Setsockopt failed");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+9] = QString("Missing or invalid hostname");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+10] = QString("Parse of tracert command o/p failed");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+11] = QString("Unspecified return code 11");
		(*errCodeMap)[ERR_PROCESS_RC_BASE+12] = QString("Unspecified return code 12");
		(*errCodeMap)[ERR_NO_PUBLIC_HOPS] = QString("No public IP addresses in traceroute path");
		(*errCodeMap)[ERR_LE_MISSING_DATA] = QString("Missing data in traceroute");
		(*errCodeMap)[ERR_ROUTING_LOOP] = QString("Routing loop in traceroute");
		(*errCodeMap)[ERR_HOST_NOT_FOUND] = QString("Server host name lookup failed");
		(*errCodeMap)[ERR_CONNECTION_REFUSED] = QString("Server connection refused");
		(*errCodeMap)[ERR_UNEXPECTED_CLOSE] = QString("Unexpected close by server");
		(*errCodeMap)[ERR_INVALID_RESPONSE_HEADER] = QString("Bad response header from server");   
		(*errCodeMap)[ERR_WRONG_CONTENT_LENGTH] = QString("Wrong content length from server");
		(*errCodeMap)[ERR_REQUEST_ABORTED] = QString("Server request aborted");
		(*errCodeMap)[ERR_PROXY_AUTH_REQ] = QString("Proxy server requires authentication");
		(*errCodeMap)[ERR_AUTH_REQ] = QString("Web server requires authentication");
		(*errCodeMap)[ERR_UNKNOWN_CONNECT_ERR] = QString("Unknown server connection error");
		(*errCodeMap)[ERR_SUBMIT_TIMEOUT] = QString("Traceroute submission timed out");
		(*errCodeMap)[ERR_SERVER_POST_FAILED] = QString("Traceroute POST failed");
		//(*errCodeMap)[ERR_SERVER_MIN_CODE] = QString("Unspec");
		//(*errCodeMap)[ERR_SERVER_MAX_CODE] = QString("Unspec");
		(*errCodeMap)[ERR_SERVER_FAIL] = QString("Invalid server response to POST");
		(*errCodeMap)[ERR_SERVER_RANGE_ERR] = QString("Server error code out of range");
		(*errCodeMap)[ERR_SERVER_ERR_BAD_FMT] = QString("Server error message format error");
	}
}

QString& TrStatus::getErrorTextByCode(int key) {
	if ( errCodeMap && errCodeMap->contains(key) ) {
		return (*errCodeMap)[key];
	} else
		return defaultErrText;
}

QString& TrStatus::getErrorText() {
	int key = -traceroute_id;
	return getErrorTextByCode(key);
}

void TrStatus::debugShow() {
	qDebug() << hostname << nhops << hosts_responding << host_responded << consistent <<
	            part_batch << op_number << elapsed_time << traceroute_id << errorMsg;

}

/** Set the traceroute_id learnt from the server.  The total elapsed
  * time for the operation is also determined. \sa setError()
  */
void TrStatus::finish(long long traceroute_id) {
	// if there has been no errors...
	if ( this->traceroute_id == -ERR_UNDEFINED )
		this->traceroute_id = traceroute_id;
	elapsed_time = timer.elapsed();
}

/** Set the error status code for this traceroute.  The negative
  * of the error code is stored into the traceroute_id field
  * which under normal circumstances should always be positive.
  * \sa finish()
  */
void TrStatus::setError(int errNum) {
	if ( errNum > 0 )
		errNum = -errNum;
	traceroute_id = errNum;
	if ( elapsed_time < 0 )
		elapsed_time = timer.elapsed();
}

