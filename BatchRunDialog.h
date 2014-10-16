//
// File: BatchRunDialog.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef BATCHRUN_DIALOG_H
#define BATCHRUN_DIALOG_H

#include <QDialog>
#include <QVector>

#include "ui_batchrun.h"

/** Dialog to select between traceroute batches used by MainWindow TrGen
  */
class BatchRunDialog : public QDialog, public Ui_BatchRunDialog {
	Q_OBJECT

public:
	//! constructor
	//! \param trsets are the traceroute sets in user-viewable format
	//! \param parent is the parent widget
	BatchRunDialog(QStringList& trsets, QWidget *parent = 0);

signals:
	//! signal emitted when a selection has been made by the user
	//! \param batchFilename is the user-viewable (not true) filename
	void tracerouteBatch(const QString& batchFilename);

private slots:
	//! slot receiving OK-clicked message
	void on_buttonBox_accepted();

	//! slot receiving Cancel-clicked message
	void on_buttonBox_rejected();
};

#endif // BATCHRUN_DIALOG_H
