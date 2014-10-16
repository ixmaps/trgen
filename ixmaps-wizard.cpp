//
// File: ixmaps-wizard.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include "ixmaps-wizard.h"
#include "SettingsDialog.h"
#include <QDebug>
#include <QVariant>


IntroWizardPage::IntroWizardPage(QWidget* parent) : QWizardPage(parent) {
	setTitle("Introduction");

	edit = new QTextEdit(
		"This wizard will help you setup the IXmaps Traceroute Generator."
		"<br/>"
		"<br/>"
		"TraceGen is a program written by Steve Harvey as part of the "
		"IXmaps: Internet Exchange Mapping Project.  This project is funded by "
		"Canada's Social Science and Humanities Research Council (SSHRC), "
		"directed by David Phillips and Andrew Clement of the University of "
		"Toronto's Faculty of Information with collaboration from "
		"Nancy Paterson, PhD Communication & Culture, YorkU "
		"and Associate Professor, Ontario College of Art & Design."
		"<br/>"
		"<br/>"
		"Eventually, this project will map the routes of Internet traffic, "
		"highlighting network exchange points and displaying information "
		"about them. It is an attempt to demystify Internet operations, "
		"and to bring the \"cloud\" down to earth. More information on this "
		"project can be found at "
		"<a href=\"http://www.ixmaps.ca/\">http://www.ixmaps.ca/</a> "
	);
	edit->setReadOnly(true);

	layout = new QVBoxLayout;
	layout->addWidget(edit);
	setLayout(layout);
}


DescriptWizardPage::DescriptWizardPage(QWidget* parent) : QWizardPage(parent) {
	setTitle("Program Description");

	edit = new QTextEdit(
		"When you run this program, it will automatically generate traceroutes "
		"from your current location to a set of about 35 hosts. These traceroutes "
		"are automatically added to the project's data base at "
		"<a href=\"http://trgen.ixmaps.ca/TrGen/\">http://trgen.ixmaps.ca/TrGen/</a> . "
		"You may view or download that database for your own use at any time. You "
		"can also view the set of destination URLs there. " 
		"<br/>"
		"<br/>"
		"Each time you run the program, it will ask for your name and a postal or "
		"zip code.  Neither of these is mandatory, but either would be helpful. "
		"You can use a pseudonym if you like, or enter only the first three characters "
		"of your postal/zip code.  Before the traceroutes are added to the database, "
		"the low order digits of the source IP address will be masked to zero. "                                       
		"<br/>"
		"<br/>"
		"Please run this program as often as you wish, from as many locations as you wish. "
	);
	edit->setReadOnly(true);

	layout = new QVBoxLayout;
	layout->addWidget(edit);
	setLayout(layout);
}


UserSettingsWizardPage::UserSettingsWizardPage(IXmapsWizard *wiz, QWidget* parent) : QWizardPage(parent) {
	setTitle("User Settings");

	label_name = new QLabel("OPTIONAL: Your name (or pseudonym)?");
	label_zip = new QLabel("Your zip or postal code (or first three characters)?");
	le_user = new QLineEdit();
	le_zip = new QLineEdit();
	SettingsDialog::setupEntryFields(this, wiz->settings, le_user, le_zip);

	layout = new QVBoxLayout;
	layout->addWidget(label_name);
	layout->addWidget(le_user);
	layout->addWidget(label_zip);
	layout->addWidget(le_zip);

	setLayout(layout);

	registerField("userName", le_user);
	registerField("userLocation", le_zip);
}


bool UserSettingsWizardPage::eventFilter(QObject *target, QEvent *event) {
	if ( event->type() == QEvent::KeyPress ) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		QString txt = keyEvent->text();
		if ( txt.size() == 1 ) {
 			qDebug() << "key " << keyEvent->key() << ", text " << keyEvent->text();
			QChar c = txt.data()[0];
			if ( !SettingsDialog::SAFE_CHARS.contains(c) )
				return true;  // consume the event
		}
	}
	return QWizardPage::eventFilter(target, event);
}



TraceSelectWizardPage::TraceSelectWizardPage(QWidget* parent) : QWizardPage(parent) {
	setTitle("Traceroute destination selection");

	edit = new QTextEdit(
		"You may either select from one of the traceroute batches "
		"or enter a host name that you would like to try. "
	);
	edit->setReadOnly(true);
	label_batch = new QLabel("We have defined a few batches to select from. ");
	label_single = new QLabel("OR, you can type a host name or dotted quad here");
	cb_batch = new QComboBox();
	//FIXME: tooltips and whatThis texts should be defined in only one place
	//       see singlerun-dialog.cpp and batchrun-dialog.cpp
	cb_batch->setWhatsThis(tr("Select one of these batches to run."));
	cb_batch->setToolTip(tr("Select a batch to run."));
	cb_lastValidIndex = -1;
	le_single = new QLineEdit();
	le_single->installEventFilter(this);
	le_single->setWhatsThis(tr("Enter a host to traceroute to."
		"  Examples are <b>www.example.com</b> or <b>192.0.2.17</b>."));
	le_single->setToolTip(tr("host name or IP address"));

	layout = new QVBoxLayout;
	layout->addWidget(edit);
	layout->addWidget(label_batch);
	layout->addWidget(cb_batch);
	layout->addWidget(label_single);
	layout->addWidget(le_single);

	setLayout(layout);

	registerField("trBatch", cb_batch);
	registerField("trSingle", le_single);
}

// only allow these characters to be entered into line edit widgets for hostnames
// also allow backspace ("\010"), tab ("\011") and carriage return ("\015")
const QString TraceSelectWizardPage::SAFE_DNS_CHARS = "\010" "\011" "\015"
      "-.0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

bool TraceSelectWizardPage::eventFilter(QObject *target, QEvent *event) {
	if ( target == le_single ) {
		if ( event->type() == QEvent::KeyPress ) {
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
			QString txt = keyEvent->text();
			if ( txt.size() == 1 ) {
	 			qDebug() << "key " << keyEvent->key() << ", text " << keyEvent->text();
				QChar c = txt.data()[0];
				if ( !SAFE_DNS_CHARS.contains(c) )
					return true;  // consume the event
			}
		}
	}
	return QWizardPage::eventFilter(target, event);
}


void TraceSelectWizardPage::initializePage() {
	IXmapsWizard *w = static_cast<IXmapsWizard *>(wizard());
	qDebug() << w;
	if ( w->doer.trsetsReady() ) {
		if ( cb_batch->count() == 0 )
			cb_batch->addItems(w->doer.trsets);
	}
}
	

TraceRunWizardPage::TraceRunWizardPage(QWidget* parent) : QWizardPage(parent) {
	setTitle("Running Traceroutes");

	edit = new QTextEdit(
		"Running..."
	, parent);
	edit->setReadOnly(true);
	sbar = new QLabel();
	pdlg = new QProgressDialog("Running traceroute batch", QString("Stop after current traceroute"), 0, 0, parent);
	pdlg->cancel();			// prevent pop-up if first operation is single host
	layout = new QVBoxLayout;
	layout->addWidget(edit);
	layout->addWidget(pdlg);
	layout->addWidget(sbar);

	setLayout(layout);
	visitCount = 0;
}

void TraceRunWizardPage::initializePage() {
	IXmapsWizard *w = static_cast<IXmapsWizard *>(wizard());
	if ( visitCount++ == 0 ) {
		connect(&w->pstat, SIGNAL(updateDisplayText(QString&)), this, SLOT(updateStatus(QString&)));
	}
}

void TraceRunWizardPage::updateStatus(QString& text) {
	sbar->setText(text);
	sbar->update();
	QApplication::processEvents();
}

TraceStatusWizardPage::TraceStatusWizardPage(QWidget* parent) : QWizardPage(parent) {
	setTitle("Traceroute Status");

	edit = new TrStatBrowser(parent);
	// Do you want to run a batch of traceroutes again?
	edit->setReadOnly(true);

	layout = new QVBoxLayout;
	layout->addWidget(edit);

	setLayout(layout);
}

FinishWizardPage::FinishWizardPage(QWidget* parent) : QWizardPage(parent) {
	setTitle("Finish");

	edit = new QTextEdit(
		"You can see these traceroutes (and others) at "
		"<a href=\"http://trgen.ixmaps.ca/TrGen/\">http://trgen.ixmaps.ca/TrGen/</a> . "
		"Thanks for your help in this project. "
		"<br/>"
		"<br/>"
		"<b>David Phillips, Andrew Clement and Nancy Paterson</b>"
	);
	edit->setReadOnly(true);

	layout = new QVBoxLayout;
	layout->addWidget(edit);

	setLayout(layout);
}

IXmapsWizard::IXmapsWizard(QWidget* parent) : QWizard(parent), doer(&pstat, this) {
	setPage(Page_Intro, new IntroWizardPage());
	setPage(Page_Descript, new DescriptWizardPage());
	setPage(Page_UserSet, new UserSettingsWizardPage(this));
	setPage(Page_TraceSelect, new TraceSelectWizardPage());
	setPage(Page_TraceRun, new TraceRunWizardPage());
	setPage(Page_TraceStatus, new TraceStatusWizardPage());
	setPage(Page_Finish, new FinishWizardPage());

	setWindowTitle("IXmaps Traceroute Generator v"+doer.programVersion);

#ifdef Q_WS_WIN
	setWindowFlags(Qt::WindowMinimizeButtonHint);
#endif
#ifdef Q_WS_X11
	setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
#endif

	// recommended to re-implement sizeHint() and setSizePolicy()
	setFixedSize(700,500);
	pageCameFrom = -1;

	setOption(HaveCustomButton2, true);
	setOption(IndependentPages, true);
	qDebug("options=%08x", get_options());
	connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(pageChanged(int)));

	//connect(&pstat, SIGNAL(updateDisplayText(QString&)), this, SLOT(updateStatus(QString&)));
	connect(&doer, SIGNAL(criticalError()), this, SLOT(gotCriticalError()));
	setButtonText(CustomButton1, "<< Try again");
	setButtonText(CustomButton2, "Stop");
	normalLayout << Stretch << BackButton << NextButton << FinishButton << CancelButton;
	stopLayout << Stretch << BackButton << NextButton << FinishButton << CustomButton2 << CancelButton;
	tryAgainLayout << Stretch << CustomButton1 << BackButton << NextButton << FinishButton << CancelButton;
	setButtonLayout(normalLayout);

	qDebug("options=%08x", get_options());

	connect(this, SIGNAL(customButtonClicked(int)), this, SLOT(customClicked(int)));
	connect(&doer, SIGNAL(tracerouteFinished()), this, SLOT(tracerouteFinished()));
	connect(this, SIGNAL(cancelTraceroute()), &doer, SLOT(cancel()));
	connect(this, SIGNAL(finished(int)), &doer, SLOT(cancel()));
}

int IXmapsWizard::get_options() {
	WizardOptions o = options();
	return int(o);

}

void IXmapsWizard::customClicked(int buttonId) {
	qDebug() << "clicked " << buttonId << ", on page " << pageCameFrom << ", Page_TraceRun=" << Page_TraceRun;
	if ( buttonId == CustomButton1 ) {
		// "Try Again" was clicked
		setStartId(Page_TraceSelect);
		restart();
	} else if ( buttonId == CustomButton2 ) {
		emit cancelTraceroute();
	}
}

void IXmapsWizard::gotCriticalError() {
	;
}

void IXmapsWizard::tracerouteFinished() {
	TraceRunWizardPage *trwp = static_cast<TraceRunWizardPage *>(page(Page_TraceRun));
	if ( trwp ) {
		qDebug() << trwp;
		qDebug() << trwp->edit->toPlainText();
		trwp->edit->setText("Finished.");
		qDebug() << trwp->edit->toPlainText();
		trwp->edit->update();
		update();
		QApplication::processEvents();
	}
}

void IXmapsWizard::accept() {
	qDebug() << "accept.";
	QDialog::accept();
}

int IXmapsWizard::nextId() const {
	int cid = currentId();

	if ( cid == Page_Finish ) {
		return -1;
	} else {
		return cid+1;
	}
}

/** The pageChanged() slot is called when a new page is to be shown.  It does whatever
  * processing that is required.
  * If the completed page is the User Settings page, the settings are made to persist.
  * From the Traceroute selection page, make the batch selection sticky, if there is
  * anything entered into the hostname field, do a single traceroute to it, otherwise
  * run the batch referenced by the combo box.
  *
  *  Once the processing is complete, pageCameFrom will then be set to the value of pageNew.
  */
void IXmapsWizard::pageChanged(int id) {
	qDebug() << "pagechanged to " << id;
	pageNew = id;
	TraceSelectWizardPage *tswp = static_cast<TraceSelectWizardPage *>(page(Page_TraceSelect));
	TraceRunWizardPage *trwp = static_cast<TraceRunWizardPage *>(page(Page_TraceRun));
	TraceStatusWizardPage *ttwp = static_cast<TraceStatusWizardPage *>(page(Page_TraceStatus));
	if ( pageCameFrom == Page_UserSet ) {
		QString user = field("userName").toString();
		QString zip = field("userLocation").toString();
		SettingsDialog::storeEntryFields(settings, user, zip);
	} else if ( pageCameFrom == Page_TraceSelect ) {
		if ( tswp ) {
			int batchIndex = tswp->cb_batch->currentIndex();
			qDebug() << "tswp->batch " << batchIndex << ", count=" << tswp->cb_batch->count();
			if ( batchIndex >= 0 ) {
				tswp->cb_lastValidIndex = batchIndex;
			} else { 
				// make selection sticky
				batchIndex = tswp->cb_lastValidIndex;
				qDebug() << "using last batchIndex " << batchIndex;
			}
			if ( batchIndex >= 0 && id == Page_TraceRun ) {
				if ( trwp )
					trwp->edit->setText("Running...");
				setButtonLayout(stopLayout);
				enableBackNext(false);
				QApplication::processEvents();
				QString batch = doer.trsets[batchIndex];
				QString single = field("trSingle").toString();
				qDebug() << "batch=" << batch << ", single=" << single;
				if ( single.count() != 0 ) {
					trwp->pdlg->cancel();
					doer.tracerouteHost(single);
				} else {
					doer.tracerouteBatch(batch, trwp->pdlg);
				}
				enableBackNext(true);
			}
		}
	} else if ( pageCameFrom == Page_TraceRun ) {
		doer.debugShowHistory();
	}
	setOption(HaveCustomButton1, (id == Page_TraceStatus));
	setButtonLayout((id == Page_TraceStatus) ? tryAgainLayout : normalLayout);
	if ( id == Page_TraceSelect ) {
		if ( tswp->cb_lastValidIndex >= 0 ) {
			tswp->cb_batch->setCurrentIndex(tswp->cb_lastValidIndex);
		}
	} else if ( id == Page_TraceStatus ) {
		ttwp->edit->renderHistory(&doer.history);
	}
	pageCameFrom = id;
}

/** Enable/disable the Back and Next buttons.  During a traceroute, it is not
  * desirable for the user to wander to another page.
  */
void IXmapsWizard::enableBackNext(bool enabled) {
	QAbstractButton *back_button = button(BackButton);
	QAbstractButton *next_button = button(NextButton);
	back_button->setEnabled(enabled);
	next_button->setEnabled(enabled);
}

