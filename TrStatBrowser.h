//
// File: TrStatBrowser.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef TRSTAT_BROWSER_H
#define TRSTAT_BROWSER_H

#include <QTextBrowser>

#include "TrStatus.h"

/** Widget to render status history for the current TRGen process.
  */
class TrStatBrowser : public QTextBrowser {

public:
	//! constructor
	//! \param parent is the parent widget
	TrStatBrowser(QWidget *parent = 0) : QTextBrowser(parent) {}

	//! display the status of all traceroutes most recent first
	void renderHistory(QList<TrStatus *> *history, int fontSize=10);

private:

	//! identify the columns in the table
	enum {
		colHost=0,		//!< hostname or dotted-quad
		colResponseCount,	//!< hops responding/total hops
		colElapsed,		//!< elapsed time to do the traceroute
		colIDError,		//!< tracerouteID in database, or an error message
		colCount		//!< total column count, must be last
	};

	//! place text with specified format within a table cell
	void setTableCell(int row, int col, const QString& text, const QTextCharFormat& fmt);

	QTextTable *table;		//!< one row per traceroute whether single or part of a batch
};

#endif
