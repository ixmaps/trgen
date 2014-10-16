//
// File: PStatus.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include <QtDebug>
#include "PStatus.h"

void PStatus::update(mw_op op) {
	text.clear();

	switch ( op ) {

	case host_tr:
		text += "Tracing host "+trHost+".";
		break;

	case host_done:
		text += "Host "+trHost+" done.";
		break;

	case batch_fetch:
		text = "Fetching "+trBatch+".";
		break;

	case batch_tr:
		text = QString("%1[%2/%3] - Tracing %4").arg(trBatch).arg(batch_host_count+1).arg(batch_host_total).arg(trHost);
		break;

	case batch_done:
		text = QString("%1: finished %2 hosts.").arg(trBatch).arg(batch_host_count);
		break;

	default:
		break;
	}
	emit updateDisplayText(text);
}

void PStatus::update() {
	update(op);
}
