//
// File: HttpGet.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include <QtGui>
#include <QtNetwork>
#include "HttpGet.h"
#include <iostream>

HttpGet::HttpGet(const QUrl &url, QIODevice *to) : QHttp(), gotten(false), f(to) {
	connect(this, SIGNAL(requestFinished(int, bool)), this, SLOT(finished(int, bool)));
	connect(this, SIGNAL(requestStarted(int)), this, SLOT(started(int)));
	setHost(url.host(), url.port(80));
	qDebug() << url.host().toAscii().data();
	QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
	requestID = get(path, f);
	loop.exec();
	//done by caller to->setFileName("results.html");
	//done by caller to->open(QIODevice::WriteOnly | QIODevice::Truncate);
}

void
HttpGet::started(int id) {
	qDebug() << "httpget started";
}

void
HttpGet::finished(int id, bool error) {
	if ( id != requestID )
		return;
	status = !error;
	if (error) {
		qDebug("Failed with an error");
	}
	loop.exit();
	f->close();
	gotten = true;
}

