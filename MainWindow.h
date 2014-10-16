//
// File: MainWindow.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui_mainwindow.h"
#include "TrWorkItem.h"
#include "TrDo.h"
#include "ServerComm.h"
#include "TrStatus.h"
#include "PStatus.h"

#include <QMainWindow>

class QLabel;

/** Widget for main-window (not wizard) style TrGen.
  */
class MainWindow : public QMainWindow, private Ui_MainWindow {
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

protected:
	//! invoked when request to close high-level window occurs
	void closeEvent(QCloseEvent *event);

private:
	PStatus pstat;				//!< encapsulate various bits of status
	TrDo doer;				//!< actually runs the traceroutes

private slots:
	//! user activated About from menus
	void on_action_About_triggered();
	//! user activated Quit from menus
	void on_action_Quit_triggered();
	//! user activated Traceroute Single host from menus
	void on_action_TracerouteSingle_triggered();
	//! user activated Traceroute Batch from menus
	void on_action_TracerouteBatch_triggered();
	//! user activated Settings from menus
	void on_action_Settings_triggered();

	//! slot receiving message to update the status bar contents
	void updateStatusBar(QString& text);

private:
	//! pop up the About message box
	void about();
	//void setMap(QString& name);
	//! setup the status bar
	void createStatusBarFields();
	//! teardown status bar
	void destroyStatusBarFields();
	//! retrieve main window position and size from last run
	void readSettings();
	//! persist main window position and size
	void writeSettings();

	//! prevent use of copy constructor
	MainWindow(const MainWindow& mw);
	//! prevent use of assignment operator
	MainWindow& operator=(const MainWindow& mw);

	QLabel *sbar_left;		//!< left field of the StatusBar
	QProgressDialog *pdlg;		//!< process dialog widget

	//QEventLoop loop;

private slots:

	//! slot receiving message from SingleRunDialog::on_buttonBox_accepted()
	void tracerouteHost(const QString& host);
	//! slot receiving message from BatchRunDialog::on_buttonBox_accepted()
	void tracerouteBatch(const QString& batch);

};

#endif
