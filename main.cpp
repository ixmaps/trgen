//
// File: main.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include <QApplication>
#include <QSettings>

#include <QWizard>

#include "MainWindow.h"
#include "ixmaps-wizard.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("IXmaps");
	QCoreApplication::setOrganizationDomain("ixmaps.ca");
	QCoreApplication::setApplicationName("tr-sub");

	QSettings settings;
	bool wizard_style = settings.value("program/wizard_style", true).toBool();
	if ( wizard_style ) {
		IXmapsWizard wizard;

		wizard.show();
		int rc =  app.exec();
		qDebug() << "Wizard rc=" << rc;
		return rc;
	} else {
		MainWindow mainWin;
		mainWin.show();
		return app.exec();
	}
}
