//
// File: TrHttp.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef TR_HTTP_H
#define TR_HTTP_H

#include <QtNetwork>
#include "TrStatus.h"

/** Subclass of QHttp used to submit traceroutes to the server.
  * \sa HttpGet
  */
class TrHttp : public QHttp {
	Q_OBJECT

public:
	//! constructor
	//! \param host is the server hostname
	//! \param inputStr is the traceroute formatted as HTTP POST data
	//! \param tstat is a pointer to a TrStatus traceroute status object
	TrHttp(const QString &host, const QByteArray &inputStr, TrStatus *tstat);

public slots:

	//! slot receiving request finished message
	//! \param id is a request id assigned by QHttp::request()
	//! \param error is set if there was an error in processing
	void finished(int id, bool error);

//not used...
//signals:
//	//! signal 
//	void updateContents(const QString &text);

private:
	//! private copy stored by constructor
	TrStatus *tstat;

	//! a unique temporary file
	QTemporaryFile f;
};

#endif
