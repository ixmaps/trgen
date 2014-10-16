//
// File: SingleRunDialog.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include <QtGui>
#include <cstdio>

#include "SingleRunDialog.h"
#include "SettingsDialog.h"
#include "MainWindow.h"

SingleRunDialog::SingleRunDialog(QWidget *parent) : QDialog(parent) {
	setupUi(this);

	//perhaps this should be done in the MainWindow??
	connect(this, SIGNAL(tracerouteHost(const QString&)), parent, SLOT(tracerouteHost(const QString&)));

	hostNameEdit->setWhatsThis(tr("Enter a host to traceroute to."
	       "  Examples are <b>www.example.com</b> or <b>192.0.2.17</b>."));
	hostNameEdit->setToolTip(tr("host name or IP address"));

	const QString* name = SettingsDialog::getUserName();
	if ( name->size() == 0 ) {
		QMessageBox::critical(this, tr("No user name"),
		    tr("You have not defined a user name/handle to identify your traceroutes.  "
		       "This is done via Edit -> Settings"), QMessageBox::Ok);
	}
}

void SingleRunDialog::on_buttonBox_rejected() {
	reject();
}

void SingleRunDialog::on_buttonBox_accepted() {
	QTextStream c_out(stdout);
	QString host = hostNameEdit->text();
	
	c_out << "got " << host << "\n";
	c_out.flush();
	if ( host.count() > 0 )
		emit tracerouteHost(host);
}

