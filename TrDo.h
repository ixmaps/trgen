//
// File: TrDo.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef TR_DO_H
#define TR_DO_H

#include "TrWorkItem.h"
#include "ServerComm.h"
#include "TrStatus.h"
#include "PStatus.h"

#include <QProcess>
#include <QProgressDialog>

/** Traceroute Doer.  Handles the workflow for single or batch traceroute requests
  * from the GUI.  Typically, the application instantiates one of these for the
  * duration of the program.
  */
class TrDo : public QObject {
	Q_OBJECT

public:
	//! constructor
	//! \param pstat points to a program status
	//! \param owner points to the high-level owning widget
	TrDo(PStatus* pstat, QWidget* owner);
	//~TrDo();

	static QString programVersion;	//!< last digit odd=slow (trparse) version, even=fast (admin mode) version

	//! do a traceroute to a single host
	//! \param host is a hostname or IPv4 dotted-quad address
	void tracerouteHost(const QString& host);

	//! do a batch of traceroutes
	//! \param batch is the name of the batch as presented via GUI
	//! \param pdlg points to a progress dialog widget
	void tracerouteBatch(const QString& batch, QProgressDialog *pdlg);

	bool trsetsReady();		//!< traceroute batch sets are available for use
	QStringList trsets;		//!< traceroute batch sets - unmangled names

	QList<TrStatus *> history;	//!< status for each traceroute done since program startup
	TrStatus *tstat;		//!< current traceroute

	void debugShowHistory();	//!< dump history to debug

signals:
	void criticalError();		//!< emitted upon critical error
	void tracerouteFinished();	//!< traceroute request is done

private:
	TrDo();
	//! disable use of copy constructor
	TrDo(const TrDo&);
	QWidget *owner;			//!< parent widget for the pop-up
	PStatus *pstat;			//!< encapsulate various bits of status
	bool cancelling;		//!< cancellation in progress

	//! unmangle a traceroute-set filename from the server
	//! \param unmangled is the unmangled version to be shown via GUI
	//! \param mangled is the filename on the server
	//! \todo { make mangled const }
	void trsUnmangle(QString& unmangled, QString& mangled);

	//! create a new traceroute status object and add it to the history
	//! \param h_name is the hostname
	//! \param in_batch is true iff the traceroute is part of a batch
	//! \param op_num is sequential operation number for the process
	bool newTrStatus(const QString& h_name, bool in_batch, int op_num);

	// stuff for describing the work to be done and its progress
private:
	int privacy;			//!< number of bits to mask off src address

	QMap<QString, QString> trs_map;	//!< traceroute batch sets - lookup mangled (real) names

	TrWorkItem *wi;			//!< a single traceroute request from initiation through submission
	int op_num;			//!< each user request in a program run gets an operation number

	// stuff for actually running the traceroute
private slots:
	//! slot called when the child process (low-level traceroute doer program) is started
	void childStarted();

	//! slot called when the child process finishes
	//! \param exitCode is the child process exit code
	//! \param exitStatus is a Qt QProcess::ExitStatus enum
	void childFinished(int exitCode, QProcess::ExitStatus exitStatus);

	//! slot called if the child process could not be created
	//! \param error is the reason from Qt
	void childError(QProcess::ProcessError error);

	//! slot called to cancel current operation
	void cancel();
	//! slot called to cancel current operation
	//! \todo { is this method superfluous? }
	void cancel(int result);

private:
	//! run a traceroute
	//! \param host is the hostname or a dotted-quad
	void runTraceroute(const QString& host);

	//! Handle child process failures.
	//! \param err is a Qt QProcess::ProcessError enum
	void msgChildError(QProcess::ProcessError err);

	bool block_traceroute;		//!< whether GUI should block during a traceroute
	QString tr_program;		//!< name (with path if required) of traceroute program
	int nprobes;			//!< number of probes per hop
	QProcess process;		//!< Qt process object representing the O/S interface to the child

private:
	ServerComm sc;			//!< object that handles communications with the server
};

#endif
