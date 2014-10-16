//
// File: TrStatus.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef TR_STATUS_H
#define TR_STATUS_H

#include <QMap>
#include <QObject>
#include <QString>
#include <QTime>

/** Status for a single traceroute.
  */
class TrStatus : public QObject {
	Q_OBJECT

public:
	//! map all error codes from different processing phases of a traceroute

	//! Per-traceroute error codes are between 1 and 499.
	//! General error codes start at 500.

	//! The ordering of the bunches of error numbers is roughly
	//! in order of the steps done to process a traceroute
	enum errCode {

		//! catch-all error code
		ERR_UNDEFINED = 1,

		ERR_NAME_RESOLV_FAIL = 2,

		//! child process control
		ERR_PROCESS_START_FAIL = 50,
		ERR_PROCESS_CRASHED,
		ERR_PROCESS_TIMEDOUT,
		ERR_PROCESS_WRITE_ERR,
		ERR_PROCESS_READ_ERR,
		ERR_PROCESS_UNKNOWN_ERR,

		ERR_PROCESS_RC_BASE = 100, //!< map exit codes from child process starting here


		//! no public hops can happen if traceroute entirely within local address space
		ERR_NO_PUBLIC_HOPS = 190,
		ERR_LE_MISSING_DATA = 191,  //!< logic error!
		ERR_ROUTING_LOOP = 192,

		//! traceroute submission to server via HTTP
		ERR_HOST_NOT_FOUND = 200,
		ERR_CONNECTION_REFUSED,
		ERR_UNEXPECTED_CLOSE,
		ERR_INVALID_RESPONSE_HEADER,   
		ERR_WRONG_CONTENT_LENGTH,
		ERR_REQUEST_ABORTED,
		ERR_PROXY_AUTH_REQ,
		ERR_AUTH_REQ,
		ERR_UNKNOWN_CONNECT_ERR,
		ERR_SUBMIT_TIMEOUT,


		//! TrHttp::finished() with error
		ERR_SERVER_POST_FAILED = 250,


		//! map CGI program error codes into this space
		ERR_SERVER_MIN_CODE = 300,
		ERR_SERVER_MAX_CODE = 345,

		//! CGI program emitting bad syntax
		ERR_SERVER_FAIL = 347,
		ERR_SERVER_RANGE_ERR = 348,
		ERR_SERVER_ERR_BAD_FMT = 349,
	};

	//! constructor
	//! \param h_name is the hostname for the traceroute
	//! \param in_batch is set iff the traceroute is part of a batch
	//! \param op_num is the sequential operation number
	TrStatus(const QString& h_name, bool in_batch, int op_num);

	QString hostname;		//!< either a Fully Qualified Domain Name or dotted quad
	int nhops;			//!< number of hops in the traceroute
	int hosts_responding;		//!< number of hosts along the path that responded
	bool host_responded;		//!< destination host gave a response
	bool consistent;		//!< each hop got replies from at most one host
	bool part_batch;		//!< traceroute was part of a batch
	int op_number;			//!< increments each time a single trace or batch is requested
	int elapsed_time;		//!< time in ms to do the entire traceroute
	long long traceroute_id;	//!< >0 is the ID in the database, <0 is an error code
	QString errorMsg;		//!< from database submission

	void debugShow();		//!< print on debug output
	void finish(long long traceroute_id);

	//! set the error code for this traceroute
	//! \param errNum is the error number
	void setError(int errNum);

	//! return a display-ready string for the error
	QString& getErrorText();

	//! return a display-ready string for an error code
	//! \param key is our error code
	static QString& getErrorTextByCode(int key);

private:
	static QTime timer;		//!< determines elapsed time for each operation
	static QMap<int, QString> *errCodeMap;	//!< from error code to text string
	static QString defaultErrText;	//!< if errCodeMap undefined, fall back to this
	void setupErrCodeMap();		//!< run only from first-time ctor.
};
	
#endif
