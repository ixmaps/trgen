//
// File: BatchRunDialog.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include <QtGui>

#include "BatchRunDialog.h"
#include "SettingsDialog.h"
#include "MainWindow.h"

BatchRunDialog::BatchRunDialog(QStringList& trsets, QWidget *parent) : QDialog(parent) {
	setupUi(this);

	//perhaps this should be done in the MainWindow??
	connect(this, SIGNAL(tracerouteBatch(const QString&)), parent, SLOT(tracerouteBatch(const QString&)));

	trSetBox->addItems(trsets);

	trSetBox->setWhatsThis(tr("Select one of these batches to run."));
	trSetBox->setToolTip(tr("Select a batch to run."));

	const QString* name = SettingsDialog::getUserName();
	if ( name->size() == 0 ) {
		QMessageBox::critical(this, tr("No user name"),
		    tr("You have not defined a user name/handle to identify your traceroutes.  "
		       "This is done via Edit -> Settings"), QMessageBox::Ok);
	}
}

void BatchRunDialog::on_buttonBox_rejected() {
	reject();
}

void BatchRunDialog::on_buttonBox_accepted() {
	QString trset = trSetBox->currentText();
	
	qDebug() << "got " << trset << ", index=" << trSetBox->currentIndex();
	emit tracerouteBatch(trset);
}

