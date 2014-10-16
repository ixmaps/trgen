//
// File: ixmaps-wizard.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef IXMAPS_WIZARD_H
#define IXMAPS_WIZARD_H

#include <QWizard>
#include <QtGui>
#include <QSettings>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>

#include "TrDo.h"
#include "TrStatus.h"
#include "PStatus.h"
#include "TrStatBrowser.h"

class IXmapsWizard;

/** State for the Intro Wizard page.
  */
class IntroWizardPage : public QWizardPage {
	Q_OBJECT

public:
	//! constructor
	//! \param parent is the parent widget
	IntroWizardPage(QWidget *parent = 0);

private:
	QTextEdit *edit;		//!< read-only text panel
	QVBoxLayout *layout;		//!< layout to hold the edit widget

};


/** State for the Description Wizard page.
  */
class DescriptWizardPage : public QWizardPage {
	Q_OBJECT

public:
	//! constructor
	//! \param parent is the parent widget
	DescriptWizardPage(QWidget *parent = 0);

private:
	QTextEdit *edit;		//!< read-only text panel
	QVBoxLayout *layout;		//!< layout to hold the edit widget

};



/** State for the User Settings Wizard page.
  */
class UserSettingsWizardPage : public QWizardPage {
	Q_OBJECT

public:
	//! constructor
	//! \param wiz is the controlling wizard
	//! \param parent is the parent widget
	UserSettingsWizardPage(IXmapsWizard *wiz, QWidget *parent = 0);

private:
	QLabel *label_name;		//!< prompt for user to put their name or handle
	QLabel *label_zip;		//!< prompt for user to put their zip/postal code
	QLineEdit *le_user;		//!< entry field for user name/handle
	QLineEdit *le_zip;		//!< entry field for zip/postal code
	QVBoxLayout *layout;		//!< layout to hold the other widgets

	bool eventFilter(QObject*, QEvent*);	//!< only permit certain keystrokes
};



/** State for the Traceroute Selection Wizard page.
  */
class TraceSelectWizardPage : public QWizardPage {
	Q_OBJECT

public:
	//! constructor
	//! \param parent is the parent widget
	TraceSelectWizardPage(QWidget *parent = 0);
	void initializePage();		//!< called just before display, so the ComboBox can get filled

	static const QString SAFE_DNS_CHARS;	//!< only allow these characters in a hostname

private:
	QTextEdit *edit;		//!< read-only text panel
	QLabel *label_batch;		//!< prompt for traceroute batch selection
	QLabel *label_single;		//!< prompt for traceroute single destination host entry
	QComboBox *cb_batch;		//!< user picks one of the available batch lists
	int  cb_lastValidIndex;		//!< make last selection sticky
	QLineEdit *le_single;		//!< user types a hostname here
	QVBoxLayout *layout;		//!< layout to hold the other widgets

	bool eventFilter(QObject*, QEvent*);	//!< only permit certain keystrokes

	friend class IXmapsWizard;
};


/** State for the Traceroute Run Wizard page.
  */
class TraceRunWizardPage : public QWizardPage {
	Q_OBJECT

public:
	//! constructor
	//! \param parent is the parent widget
	TraceRunWizardPage(QWidget *parent = 0);
	void initializePage();		//!< called just before display, so the "status bar" can be activated

private:
	int visitCount;			//!< times this page has been visited
	QTextEdit *edit;		//!< read-only text panel
	QProgressDialog *pdlg;		//!< a progress dialog with a cancel button
	QLabel *sbar;			//!< a "status bar"
	QVBoxLayout *layout;		//!< layout to hold the other widgets

	friend class IXmapsWizard;

private slots:
	void updateStatus(QString& text);   //!< receive status updates

};


/** State for the Traceroute Status Wizard page.
  */
class TraceStatusWizardPage : public QWizardPage {
	Q_OBJECT

public:
	//! constructor
	//! \param parent is the parent widget
	TraceStatusWizardPage(QWidget *parent = 0);

private:
	TrStatBrowser *edit;			//!< read-only text panel
	QVBoxLayout *layout;			//!< layout to hold the edit widget

	friend class IXmapsWizard;
};

/** State for the Finish Wizard page.
  */
class FinishWizardPage : public QWizardPage {
	Q_OBJECT

public:
	//! constructor
	//! \param parent is the parent widget
	FinishWizardPage(QWidget *parent = 0);

private:
	QTextEdit *edit;			//!< read-only text panel
	QVBoxLayout *layout;			//!< layout to hold the edit widget

};



/** IXmaps TrGen Wizard.
  */
class IXmapsWizard : public QWizard {
	Q_OBJECT

public:
	//! identifiers for each page to aid in navigation
	enum { Page_Intro, Page_Descript, Page_UserSet, Page_TraceSelect, 
	       Page_TraceRun, Page_TraceStatus, Page_Finish 
	};

	//! constructor
	//! \param parent is the parent widget
	IXmapsWizard(QWidget *parent = 0);
	void accept();

	//! specify the page for the Next button to go to
	int nextId() const;

	QSettings settings;			//!< maintains persistence of user handle and location

private:
	int pageNew;				//!< new page we are going into
	int pageCameFrom;			//!< keep track of where we were when going to new page

	void enableBackNext(bool enabled);	//!< allow disabling of Next/Back during traceroutes

	PStatus pstat;				//!< encapsulate various bits of status
	TrDo doer;				//!< actually runs the traceroutes
	//QPushButton myCancelButton;		//!< active when running traceroute(s)
	QList<QWizard::WizardButton> normalLayout;	//!< regular order of the buttons
	QList<QWizard::WizardButton> stopLayout;	//!< button order including "Stop"
	QList<QWizard::WizardButton> tryAgainLayout;	//!< button order including "Try Again"

	//! get look and feel wizard options as integer for debug display
	int get_options();

	friend class TraceSelectWizardPage;	//!< allowed access here
	friend class TraceRunWizardPage;	//!< allowed access here

signals:
	void cancelTraceroute();		//!< want to cancel the currently running traceroute

private slots:
	//! The pageChanged() slot is called when a new page is to be shown.
	void pageChanged(int id);
	void customClicked(int buttonId);	//!< a custom button was clicked, either TryAgain or Stop

	//! slot receiving message that a traceroute operation (single host or batch) is done
	void tracerouteFinished();
	
	void gotCriticalError();		//!< receive notification of serious problem

};


#endif
