//
// File: MainWindow.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include <QtGui>
#include <QtDebug>
#include <QSettings>

#include "MainWindow.h"
#include "SettingsDialog.h"
#include "SingleRunDialog.h"
#include "BatchRunDialog.h"

#include <QMainWindow>
#include <QApplication>

MainWindow::MainWindow() : doer(&pstat, this) {
	qDebug() << "MainWindow::MainWindow() called";
	qDebug() << "MainWindow geometry is " << geometry();
	setupUi(this);

	pdlg = new QProgressDialog("Running traceroute batch", QString("Cancel"), 0, 0, this);
	//setCentralWidget(XXX);
	createStatusBarFields();
	connect(&pstat, SIGNAL(updateDisplayText(QString&)), this, SLOT(updateStatusBar(QString&)));

	connect(&doer, SIGNAL(criticalError()), this, SLOT(on_action_Quit_triggered()));

	readSettings();
}

MainWindow::~MainWindow() {
	writeSettings();
	delete pdlg;
	destroyStatusBarFields();
}


void MainWindow::tracerouteHost(const QString& host) {
	doer.tracerouteHost(host);
}


void MainWindow::tracerouteBatch(const QString& batch) {
	doer.tracerouteBatch(batch, pdlg);
}

void MainWindow::closeEvent(QCloseEvent *event) {
	event->accept();
}

void MainWindow::on_action_About_triggered() {
	pstat.update(PStatus::none);
	about();
}

void MainWindow::on_action_Quit_triggered() {
	pstat.is_dying = true;
	close();
}

void MainWindow::on_action_TracerouteSingle_triggered() {
	pstat.update(PStatus::none);
	qDebug() << "on_action_TracerouteSingle_triggered()";

	SingleRunDialog dialog(this);
	if (dialog.exec()) {
		qDebug() << "SingleRunDialog retd OK";
	}
}

void MainWindow::on_action_TracerouteBatch_triggered() {
	pstat.update(PStatus::none);
	qDebug() << "on_action_TracerouteBatch_triggered()";

	if ( doer.trsetsReady() ) {
		BatchRunDialog dialog(doer.trsets, this);
		if (dialog.exec()) {
			qDebug() << "BatchRunDialog retd OK";
		}
	}
}

void MainWindow::on_action_Settings_triggered() {
	pstat.update(PStatus::none);
	qDebug() << "on_action_Settings_triggered()";
	SettingsDialog dialog(this);
	if (dialog.exec()) {
		qDebug() << "SettingsDialog retd OK";
	}
}

void MainWindow::about() {
	QMessageBox::about(this, tr("About Traceroute Generator"),
	    tr("<h2>Traceroute Generator v")+doer.programVersion+tr("</h2>"
		"<p>Traceroute Generator performs traceroutes and submits"
		" them to a central database."
		"<p>The low order bits of the source address are"
		" masked off for privacy."));
}

void MainWindow::updateStatusBar(QString& text){
	sbar_left->setText(text);
	sbar_left->update();
	QApplication::processEvents();
}


void MainWindow::createStatusBarFields()
{
	sbar_left = new QLabel();
	sbar_left->setAlignment(Qt::AlignHCenter);
	sbar_left->setMinimumSize(sbar_left->sizeHint());

	statusBar()->addWidget(sbar_left);

	pstat.update();
}

void MainWindow::destroyStatusBarFields() {
	delete sbar_left;
}

void MainWindow::readSettings()
{
	QSettings settings(this);
	settings.beginGroup("MainWindow");
	resize(settings.value("size", QSize(400, 400)).toSize());
	move(settings.value("pos", QPoint(200, 200)).toPoint());
	settings.endGroup();
}

void MainWindow::writeSettings()
{
	QSettings settings(this);
	settings.beginGroup("MainWindow");
	settings.setValue("size", size());
	settings.setValue("pos", pos());
	settings.endGroup();
}

