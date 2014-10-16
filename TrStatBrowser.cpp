//
// File: TrStatBrowser.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include "TrStatBrowser.h"
#include <QtGui>

/** Display status for all traceroutes done in this invocation of TrGen.
  * The row(s) for the most recent user-initiated operation, whether
  * a single traceroute to a user-specified host, or a batch, is rendered
  * as bold. \sa TrStatus::op_number
  */ 
void TrStatBrowser::renderHistory(QList<TrStatus *> *history, int fontSize) {
	int nrows = history->size();
	clear();
	QTextCursor cursor = textCursor();
	cursor.beginEditBlock();

	QTextTableFormat tableFormat;
	tableFormat.setAlignment(Qt::AlignHCenter);
	tableFormat.setBackground(QColor("#ffffff"));
	tableFormat.setCellPadding(0);
	tableFormat.setCellSpacing(2);

#if 0
	QVector<QTextLength> constraints;
	constraints << QTextLength(QTextLength::PercentageLength, 14)
	            << QTextLength(QTextLength::PercentageLength, 14)
	            << QTextLength(QTextLength::PercentageLength, 14)
	            << QTextLength(QTextLength::PercentageLength, 14)
	            << QTextLength(QTextLength::PercentageLength, 14)
	            << QTextLength(QTextLength::PercentageLength, 14)
	            << QTextLength(QTextLength::PercentageLength, 14);
	tableFormat.setColumnWidthConstraints(constraints);
#endif

	table = cursor.insertTable(nrows+1, colCount, tableFormat);

	QTextFrame *frame = cursor.currentFrame();
	QTextFrameFormat frameFormat = frame->frameFormat();
	frameFormat.setBorder(1);
	frame->setFrameFormat(frameFormat);

	QTextCharFormat regFormat = cursor.charFormat();
	regFormat.setFontPointSize(fontSize);

	QTextCharFormat boldFormat = regFormat;
	boldFormat.setFontWeight(QFont::Bold);

	QTextCharFormat errFormat = boldFormat;
	errFormat.setBackground(Qt::red);

	QTextCharFormat warnFormat = boldFormat;
	warnFormat.setBackground(Qt::yellow);

	setTableCell(0, colHost, QString("host"), boldFormat);
	setTableCell(0, colResponseCount, QString("resp/total"), boldFormat);
	setTableCell(0, colElapsed, QString("time"), boldFormat);
	setTableCell(0, colIDError, QString("ID or error"), boldFormat);

	if ( nrows < 1 ) {
		table->insertRows(table->rows(), 1);
		setTableCell(1, 0, QString("no traceroutes attempted"), errFormat);
	} else {
		int last_op = (*history)[nrows-1]->op_number;
		for ( int row=1; row <= nrows; row++ ) {
			// show most recently performed traceroutes first
			TrStatus *tstat = (*history)[nrows-row];
			QTextCharFormat currFormat = (tstat->op_number==last_op) ? boldFormat : regFormat;
			setTableCell(row, colHost, tstat->hostname, currFormat);
			setTableCell(row, colResponseCount,
			    QString("%1/%2").arg(tstat->hosts_responding).arg(tstat->nhops), currFormat);
			setTableCell(row, colElapsed, QString("%1").arg(((double)tstat->elapsed_time)/1000.0), currFormat);
			if ( tstat->traceroute_id > 0 ) {
				setTableCell(row, colIDError, QString("%1").arg(tstat->traceroute_id),
				   (tstat->host_responded) ? currFormat : warnFormat);
			} else if ( tstat->errorMsg.size() > 0 ) {
				setTableCell(row, colIDError, tstat->errorMsg, errFormat);
			} else {
				//setTableCell(row, colIDError, QString("%1").arg(tstat->traceroute_id), errFormat);
				setTableCell(row, colIDError, tstat->getErrorText(), errFormat);
			}
		}
	}

	cursor.endEditBlock();
}

void TrStatBrowser::setTableCell(int row, int col, const QString& text, const QTextCharFormat& fmt) {
	QTextTableCell cell = table->cellAt(row, col);
	QTextCursor cellCursor = cell.firstCursorPosition();
	cellCursor.insertText(text, fmt);
}

