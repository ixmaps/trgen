//
// File: SingleRunDialog.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef SINGLERUN_DIALOG_H
#define SINGLERUN_DIALOG_H

#include <QDialog>
#include <QVector>

#include "ui_singlerun.h"

/** Dialog to enter a hostname used by MainWindow TrGen
  */
class SingleRunDialog : public QDialog, public Ui_SingleRunDialog {
	Q_OBJECT

public:
	//! constructor
	SingleRunDialog(QWidget *parent = 0);

signals:
	//! signal emitted when user has entered a hostname or dotted-quad and clicked OK
	void tracerouteHost(const QString& hostname);

private slots:
	//! slot receiving message when user clicks OK
	void on_buttonBox_accepted();
	//! slot receiving message when user clicks Cancel
	void on_buttonBox_rejected();
};

#endif // SINGLERUN_DIALOG_H
