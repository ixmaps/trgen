//
// File: SettingsDialog.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <QSettings>

#include "ui_settings.h"

/** Settings dialog box to get user's handle and location.
  */
class SettingsDialog : public QDialog, public Ui_SettingsDialog {
	Q_OBJECT

public:
	//! constructor
	SettingsDialog(QWidget *parent = 0);
	//! get the user's handle from persistent settings storage
	static const QString* getUserName();
	//! get the user's location from persistent settings storage
	static const QString* getUserLocation();

	//! setup GUI entry fields for user handle and location, pre-loading them with their current persistent settings
	static void setupEntryFields(QObject *owner, QSettings& settings, QLineEdit *userNameEdit, QLineEdit *yourLocationEdit);

	//! make the entered values persistent
	static void storeEntryFields(QSettings& settings, QString& name, QString& location);

	//! only allow these characters to be entered into line edit widgets
	static const QString SAFE_CHARS;

private slots:
	//! slot receiving message triggered by clicking OK
	void on_buttonBox_accepted();
	//! slot receiving message triggered by clicking Cancel
	void on_buttonBox_rejected();

private:
	//! keystroke filter to dis-allow entry of problematic characters
	bool eventFilter(QObject*, QEvent*);
	//! local settings object to communicate with persistent storage
	QSettings settings;
};

#endif // SETTINGS_DIALOG_H
