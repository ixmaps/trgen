//
// File: TrDo.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include <QtDebug>
#include <QSettings>
#include <QBuffer>
#include <QMessageBox>
#include <QApplication>
#include <iostream>

#include "TrDo.h"
#include "IPv4Privacy.h"

#ifdef Q_WS_X11
// get decl. for getenv()
#include <cstdlib>
#endif

// The traceroute submitter program has two version numbers differing
// in the last digit.  The "parse" version calls the native traceroute
// command via the "trparse" wrapper which produces traceroute output
// in canonical form.  The "fast" version calls a custom traceroute
// which returns canonical output, but may require administrator (root)
// privileges because it uses raw sockets.  Which version is being run
// is found from the settings which are determined by the installer.
// Otherwise, the two versions are identical.

#define PGM_PARSE_VERSION	"0.8.5"
#define PGM_FAST_VERSION	"0.8.6"
QString TrDo::programVersion(PGM_PARSE_VERSION);

/** Initialize the GUI-independent layer.  Select between available
  * low-level traceroute doer programs, determine the number of
  * traceroute probes per hop, and the default privacy settings.
  */
TrDo::TrDo(PStatus* pstat, QWidget* owner) : sc(owner) {
	this->owner = owner;
	this->pstat = pstat;

	// make sure tstat always points to something
	const QString dummy("dummy");
	//tstat = new TrStatus(const_cast<QString&>(dummy), false, 0);
	tstat = new TrStatus(dummy, false, 0);
	op_num = 0;

	QSettings settings(this);
	QString fast_doer("wmtrcmd");
	tr_program = settings.value("program/tr-doer", fast_doer).toString();
#ifdef Q_WS_X11
	// Linux/UNIX can override settings with environment variable
	char *env_wmtrcmd = getenv("WMTRCMD");
	if ( env_wmtrcmd )
		tr_program = QString(env_wmtrcmd);
#endif
	if ( tr_program.contains(fast_doer) ) {
		programVersion = PGM_FAST_VERSION;
	}
	settings.setValue("program/version", programVersion);  // save which one we are

	nprobes = (tr_program == "wmtrcmd") ? 0 : 3;

	block_traceroute = true;	// block originating GUI thread until completion

	connect(&process, SIGNAL(started()), this, SLOT(childStarted()));
	connect(&process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(childError(QProcess::ProcessError)));
	connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(childFinished(int, QProcess::ExitStatus)));

	qDebug() << "tr_program is " << tr_program;
		
	privacy = 8;
	wi = 0;
	cancelling = false;
}

/** Unmangle a .trset filename from the server.  As the web server
 *  directory listing is in sorted order, the filenames are preceeded
 *  by decimal digits and then a colon character.  This scheme allows
 *  the ordering as presented to the user to be determined by the
 *  actual filename used in deployment.   The user is then shown
 *  a list of virtual filenames in priority order.
 */
void TrDo::trsUnmangle(QString& unmangled, QString& mangled) {
	unmangled.clear();
	int max_count = mangled.count()-6;	// ignore ".trset" suffix
	int i;
	QChar c;

	// skip over the run of decimal digits
	for ( i=0; i < max_count; i++ ) {
		c = mangled.at(i);
		if ( c < '0' || '9' < c ) 
			break;
	}
	// have a non-digit.  If a colon, skip over
	if ( c == ':' ) {
		i++; 
		// skip leading whitespace
		for ( ; i < max_count; i++ ) {
			c = mangled.at(i);
			if ( c != ' ' && c != '_' )
				break;
		}
	}
	// copy the rest of the string, replacing underscores with spaces
	// leave off the ".trset" suffix
	for ( ; i < max_count; i++ ) {
		c = mangled.at(i);
		if ( c == '_' )
			c = ' ';
		unmangled.append(c);
	}
}

/** Get traceroute batch file names from the server if they already
  * have not been fetched.  The filenames are "unmangled" to be
  * easy for the user to view via the GUI. \sa trsUnmangle() 
  */
bool TrDo::trsetsReady() {
	if ( trsets.count() == 0 ) {
		QStringList trs;
		sc.getTrSets(trs);
		trsets.clear();
		for ( int i=0; i < trs.size(); i++ ) {
			QString mangled = trs[i];
			QString unmangled;
			trsUnmangle(unmangled, mangled);
			qDebug() << "from " << mangled << " to " << unmangled;
			trsets << unmangled;
			trs_map[unmangled] = mangled;
		}
	}
	return trsets.count() > 0;
}

void TrDo::childStarted() {
	qDebug() << "child started";
}

void TrDo::childError(QProcess::ProcessError error) {
	qDebug() << "child error " << error;
	msgChildError(error);
}

/** Handle child process failures.  These do not include the child exiting with
  * a non-zero exit code.  The Qt QProcess::ProcessError enum values are mapped
  * into the TrStatus::errCode enum range.  If the error is not because the user
  * issued a cancel request via the GUI, pop-up a critical MessageBox and emit
  * a criticalError() signal.
  */
void TrDo::msgChildError(QProcess::ProcessError err) {
	int ixErr;
	switch ( err ) {
	case QProcess::FailedToStart:       ixErr = TrStatus::ERR_PROCESS_START_FAIL; break;
	case QProcess::Crashed:             ixErr = TrStatus::ERR_PROCESS_CRASHED; break;
	case QProcess::Timedout:            ixErr = TrStatus::ERR_PROCESS_TIMEDOUT; break;
	case QProcess::WriteError:          ixErr = TrStatus::ERR_PROCESS_WRITE_ERR; break;
	case QProcess::ReadError:           ixErr = TrStatus::ERR_PROCESS_READ_ERR; break;
	case QProcess::UnknownError:
	default:                            ixErr = TrStatus::ERR_PROCESS_UNKNOWN_ERR; break;
	}
	tstat->setError(ixErr);

	if ( err == QProcess::Crashed  &&  cancelling )
		return;		// because we killed it!

	QString why = TrStatus::getErrorTextByCode(ixErr);
	QMessageBox::critical(owner, tr("Child process failure"),
	    tr("The traceroute child program (")+tr_program+tr(") is not working.")+" ("+why+")", QMessageBox::Ok);
	emit criticalError();
	if ( wi ) {
		delete wi;
		wi = 0;
	}
}

/** Slot called when the child process is done.  If the child exited
  * without any error, the standard output from the child is parsed,
  * the privacy setting applied to the traceroute which is then
  * formatted for submission to the server as an HTTP POST, then
  * then submitted.  If there was an error code from the child, it
  * is mapped into the TrStatus::errCode enum range.
  */
void TrDo::childFinished(int exitCode, QProcess::ExitStatus exitStatus) {
	if ( !wi )
		return;
	qDebug() << "child finished " << exitCode << " " << exitStatus;
	if ( exitStatus == QProcess::NormalExit ) {
		if ( exitCode == 0 ) {
			QByteArray trData = process.readAllStandardOutput();
			wi->parseCanonical(trData);
	
			IPv4Privacy prv(privacy);
			int private_ip_cnt = prv.apply(wi->host_addrs);
	
			QByteArray ba;
			if ( wi->formatForServer(ba, private_ip_cnt, programVersion) ) {
				const char *post_data = ba.data();
				if ( !sc.submitTraceroute(post_data, tstat) ) {
					qDebug() << "traceroute submission to server failed";
				}
			}
			tstat->consistent = true;
		} else {
			//FIXME: ensure that the exit code space on each O/S is
			// not contaminated by higher-order status bits from the O/S
			tstat->setError(TrStatus::ERR_PROCESS_RC_BASE+exitCode);
		}
	}
	delete wi;
	wi = 0;
	if ( tstat ) {
		tstat->debugShow();
	}
}

/** Run a traceroute.  Only one traceroute can be run at a time.
  * A temporary TrWorkItem work item is created for the prospective
  * traceroute.  If the hostname is resolvable to an IP address,
  * the low-level traceroute doer program is started in a separate
  * process.  The process completion is waited for in a loop that
  * wakes up every 100 milliseconds to allow the GUI to remain
  * responsive.
  */
void TrDo::runTraceroute(const QString& host) {
	if ( wi ) {
		qDebug() << "an existing work item is incomplete";
		return;
	}
	wi = new TrWorkItem(host, tstat, nprobes);
	if ( !wi ) {
		qDebug() << "failed to initiate TrWorkItem";
		return;
	}
	if ( !wi->isResolved() ) {
		if ( pstat->op == PStatus::host_tr ) {
			QMessageBox::critical(owner, tr("Name resolution failure"),
			    tr("Cannot resolve ")+host, QMessageBox::Ok);
		} else {
			qDebug() << "didn't resolve host " << host;
		}
		delete wi;
		wi = 0;
		return;
	}
	QStringList args;
	args << QString("-q%1").arg(wi->nprobes);
	args << host;
	process.start(tr_program, args);
	if ( block_traceroute ) {
		while ( !process.waitForFinished(100) ) { // wait 1/10 th of a second
			QApplication::processEvents();
			// The process finish may occur during the waitForFinished()
			// or the processEvents() or here.  Handle all possible cases.
			if ( !wi ) {
				std::cout << "break! ";
				break;
			}
			std::cout << '.' << std::flush;
		}
		std::cout << "done!" << std::endl;
	}
}

/** Create a new traceroute status object, adding it to the history.
  */
bool TrDo::newTrStatus(const QString& h_name, bool in_batch, int op_num) {
	TrStatus *trs = new TrStatus(h_name, in_batch, op_num);
	if ( trs ) {
		tstat = trs;
		history << tstat;
		return true;
	}
	return false;
}

void TrDo::debugShowHistory() {
	foreach (TrStatus *tstat, history) {
		tstat->debugShow();
	}
}

/** Run a single traceroute.  A new traceroute status object is created,
  * and a call to runTraceroute() is wrapped.  The GUI status bar is
  * updated.  Upon completion, the tracerouteFinished() signal is emitted.
  */
void TrDo::tracerouteHost(const QString& host) {
	if ( !newTrStatus(host, false, ++op_num) )
		return;
	qDebug() << "trHost gets " << host.toAscii().data() << " .";
	pstat->trHost = host;
	pstat->update(PStatus::host_tr);
	runTraceroute(host);
	pstat->update(PStatus::host_done);
	cancelling = false;
	emit tracerouteFinished();
}

/** Run a traceroute batch.  The batch filename is mapped to the true filename
  * on the server, then the batch file is fetched and parsed.
  * 
  * Lines starting with "host " denote hostnames to run traceroutes to.  All
  * other lines are treated as comments. \sa tracerouteHost()
  */
void TrDo::tracerouteBatch(const QString& batch, QProgressDialog *pdlg) {
	static bool in_progress = false;
	
	if ( in_progress )
		return;
	op_num++;
	pstat->trBatch = batch;
	pstat->update(PStatus::batch_fetch);
	//in theory, a race condition is here
	in_progress = true;

	QBuffer buf;
	QString batchFilename = trs_map[batch];
	if ( !sc.fetchBatch(batchFilename, buf) ) {
		pstat->update(PStatus::none);
		in_progress = false;
		return;
	}
	if ( buf.open(QBuffer::ReadOnly) ) {
		// read twice.  1st time gets the host count for progress indication
		pstat->batch_host_total = 0;
		while ( true ) {
			QByteArray ba = buf.readLine();
			if ( ba.count() <= 0 )
				break;
			if ( ba.startsWith("host ") ) {
				pstat->batch_host_total++;
			}
		}

		buf.reset();

		pstat->batch_host_count = 0;
		pdlg->reset();
		pdlg->setMinimum(0);
		pdlg->setMaximum(pstat->batch_host_total);
		pdlg->setMinimumDuration(0);		// dialog will not wait 4 seconds before appearing
#ifdef Q_WS_WIN
		pdlg->setWindowFlags(Qt::WindowMinimizeButtonHint);
#endif
		pdlg->setValue(pstat->batch_host_count);
		pdlg->show();
		while ( true ) {
			if ( cancelling ) {
				pdlg->cancel();
				break;
			}
			QByteArray ba = buf.readLine();
			if ( pstat->is_dying )
				break;
			if ( ba.count() <= 0 )
				break;
			ba.chop(1);
			qDebug() << "trBatch sees " << ba.data() << " .";
			if ( ba.startsWith("host ") ) {
				QString host(ba.mid(5));
				pstat->trHost = host;
				pdlg->setValue(pstat->batch_host_count);
				if ( pdlg->wasCanceled() )
					break;
				if ( !newTrStatus(host, true, op_num) )
					break;
				pstat->update(PStatus::batch_tr);
				QApplication::processEvents();
				runTraceroute(host);
				pstat->batch_host_count++;
			}
		}
		//pdlg->setValue(pstat->batch_host_total);
		pdlg->hide();
	}
	buf.close();
	pstat->update(PStatus::batch_done);
	in_progress = false;
	cancelling = false;
	emit tracerouteFinished();
}

void TrDo::cancel() {
	qDebug() << "TrDo::cancel()";
	cancel(0);
}

void TrDo::cancel(int result) {
	(void)result;
	qDebug() << "TrDo::cancel(int)";
	cancelling = true;
	process.kill();
}
