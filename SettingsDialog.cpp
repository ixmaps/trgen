//
// File: SettingsDialog.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include <QtGui>
#include <cstdio>
#include <cstring>

#include "SettingsDialog.h"

//! Only allow these characters to be entered into line edit widgets.
//! Also allow backspace ("\010") and tab ("\011") and carriage-return ("\015").
//! Limiting safe characters are a first-line defence against server attacks.
//! Alternatively, we will have to quote them before sending and unquote
//! them on the server.
const QString SettingsDialog::SAFE_CHARS = "\010" "\011" "\015"
      " !$*+,-./0123456789:=?ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), settings(parent)  {
	setupUi(this);

	setupEntryFields(this, settings, userNameEdit, yourLocationEdit);
}

// FIXME:  use multiple inheritance
void SettingsDialog::setupEntryFields(
	QObject *owner,				// parent widget wanting to apply its event filter
	QSettings& settings,			// settings object maintained by parent
	QLineEdit *userNameEdit,		
	QLineEdit *yourLocationEdit)
{
	if ( owner ) {
		userNameEdit->installEventFilter(owner);
		yourLocationEdit->installEventFilter(owner);
	}

	settings.beginGroup("user");
	QVariant name(settings.value("name", ""));
	userNameEdit->setText(name.toString());
	QVariant location(settings.value("location", ""));
	yourLocationEdit->setText(location.toString());
	settings.endGroup();
	userNameEdit->setWhatsThis(tr("The User Name is used to identify your contributions "
	    "to the IXmaps database.  You may use a handle if you wish to remain anonymous."));
	userNameEdit->setToolTip(tr("Your name or handle"));
	yourLocationEdit->setWhatsThis(tr("Please enter your postal/ZIP code.<br>"
	    "This item is optional so you may leave it blank if you so desire."));
	yourLocationEdit->setToolTip(tr("Postal/ZIP code (optional)"));
	yourLocationEdit->setMaxLength(10);
}

// FIXME:  use multiple inheritance
void SettingsDialog::storeEntryFields(
	QSettings& settings,			// settings object maintained by parent
	QString& name,		
	QString& location)
{
	
	settings.beginGroup("user");
	settings.setValue("name", name);
	settings.setValue("location", location);
	settings.endGroup();
	qDebug() << "got " << name << " " << location << "\n";

}

const QString* SettingsDialog::getUserName() {
	QSettings settings;
	settings.beginGroup("user");
	QVariant name(settings.value("name", ""));
	const QString* qstr = new QString(name.toString());
	settings.endGroup();
	return qstr;
}

const QString* SettingsDialog::getUserLocation() {
	QSettings settings;
	settings.beginGroup("user");
	QVariant location(settings.value("location", ""));
	const QString* qstr = new QString(location.toString());
	settings.endGroup();
	return qstr;
}

void SettingsDialog::on_buttonBox_rejected() {
	reject();
}

void SettingsDialog::on_buttonBox_accepted() {
	QString name = userNameEdit->text();
	QString location = yourLocationEdit->text();
	storeEntryFields(settings, name, location);
}

bool SettingsDialog::eventFilter(QObject *target, QEvent *event) {
	if ( target == userNameEdit || target == yourLocationEdit ) {
		if ( event->type() == QEvent::KeyPress ) {
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
			QString txt = keyEvent->text();
			if ( txt.size() == 1 ) {
	 			qDebug() << "key " << keyEvent->key() << ", text " << keyEvent->text();
				QChar c = txt.data()[0];
				if ( !SAFE_CHARS.contains(c) )
					return true;  // consume the event
			}
		}
	}
	return QDialog::eventFilter(target, event);
}

