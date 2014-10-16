//
// File: ServerComm.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef SERVER_COMM_H
#define SERVER_COMM_H


#include <QBuffer>
#include <QString>
#include <QStringList>
#include <QHttp>

#include "TrStatus.h"


/** Server Communication.
 */
class ServerComm : QObject {
	Q_OBJECT

public:
	//! constructor
	//! \param owner is the high-level widget to be the parent for pop-ups
	ServerComm(QWidget* owner);

	//! get list of the available trsets from the server
	//! \param trsets receives the list
	//! \param popupOnError determines whether an error generates a pop-up window
	//! \return true iff the operation succeeded
	bool getTrSets(QStringList& trsets, bool popupOnError=true);

	//! retrieve a file from the trsets directory on the server
	//! \param filename is the true filename on the server
	//! \param buf receives the file content
	//! \param popupOnError determines whether an error generates a pop-up window
	//! \return true iff the operation succeeded
	bool fetchBatch(const QString& filename, QBuffer& buf, bool popupOnError=true);

	//! submit traceroute data to the server
	//! \param post_data is the string of data to be sent
	//! \param tstat is the traceroute status object to be updated
	//! \param popupOnError determines whether an error generates a pop-up window
	//! \return true iff the operation succeeded
	bool submitTraceroute(const char *post_data, TrStatus *tstat, bool popupOnError=true);

private slots:
	//! slot receiving completion message for traceroute submission
	//! \param error is set if there was an error submitting the traceroute to the server
	void trResultsSubmitted(bool error);

private:
	//! map QHttp error codes into IXmaps TrGen error codes
	//! \param err is a Qt QHttp::Error code
	//! \param popupOnError allows pop-up critical error message box for server connection failures
	//! \return the IXmaps TrGen error code
	int msgConnFailure(QHttp::Error err, bool popupOnError);

	QWidget *owner;			//!< parent widget for the pop-up

	// traceroute result-set submission to server
	bool subm_waiting_completion;	//!< waiting for traceroute submission to complete
	bool subm_error_status;		//!< whether the traceroute submission had an error
	//!< \todo { remove subm_error_status as it isn't used }
};

#endif
