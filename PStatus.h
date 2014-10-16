//
// File: PStatus.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef P_STATUS_H
#define P_STATUS_H

#include <QObject>
#include <QString>

/** Program status.
  */
class PStatus : public QObject {
	Q_OBJECT

public:
	//! high-level operation
	enum mw_op {
		none, batch_fetch, host_tr, batch_tr, host_done, batch_done
	};

	//! constructor
	PStatus() { is_dying = false; op=none; batch_host_total = batch_host_count = 0; }
	// ~PStatus();

	//! format the status display message according to the given high-level operation
	//! \param op is the operation to assume
	void update(mw_op op);
	//! format the status display message according to the current high-level operation
	void update();


	// stuff for describing the work to be done and its progress
	mw_op op;			//!< high-level operation in progress

	QString trHost;			//!< host being trace-routed to as supplied by user/batch file
	QString trBatch;		//!< name of batch file being processed

	int batch_host_total;		//!< total hosts for current batch
	int batch_host_count;		//!< hosts done for current batch

	// program state
	bool is_dying;			//!< whether to abort any processing

private:
	QString text;			//!< status message text formatted here

signals:
	void updateDisplayText(QString& text);	//!< send status updates to whoever is interested

};

#endif
