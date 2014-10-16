//
// File: TrWorkItem.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef TR_WORK_H
#define TR_WORK_H

#include <QString>
#include <QVector>
#include <QHostAddress>

#include "TrStatus.h"

/** A work item describing a single traceroute to be done, a 
 *  container for it's results, and to be submitted to the server.
 */
class TrWorkItem {

public:
	//! constructor
	//! \param host may be either a hostname or a dotted quad
	//! \param tstat is a pointer to a TrStatus traceroute status object
	//! \param nprobes is the number of probes per hop along the traceroute
	//! The hostname is resolved.
	TrWorkItem(const QString &host, TrStatus *tstat, int nprobes = 0);  // host is traceroute destination

	//! whether hostname to IP# resolution worked
	bool isResolved();

	//! parse traceroute output
	//! \param trData is the output in canonical format from a traceroute doer program
	//! \todo { document the format }
	void parseCanonical(QByteArray& trData);

	//! format a traceroute for submission to the server
	//! \param ba is an empty caller-supplied buffer for the result
	//! \param private_ip_cnt is the number of private (RFC 1918) addresses to leave off the submitted traceroute
	//! \param programVersion is the program version 
	//! \todo { move private_ip_cnt out of the caller to reduce degree of coupling }
	//! \todo { document the format }
	bool formatForServer(QByteArray& ba, int private_ip_cnt, const QString& programVersion);

	int nprobes;			//!< number of probes per hop along the traceroute

	// results of a traceroute
	//! \todo { encapsulate ::host_addrs with a method to apply privacy to it }
	QVector<QHostAddress> host_addrs;	//!< internal representation of IP addresses for each hop
private:

	// Check for a routing loop in this traceroute.
	// \param startIndex may exclude local non-public network hops at originator end
	// \param endIndex is one past the end of the ip_addrs array
	bool isRoutingLoop(int startIndex, int endIndex);

	QVector<QString> ip_addrs;	//!< one IP address for each hop as a dotted-quad or '*' if unknown
	QVector<int> rtts;		//!< flattened 2-dimensional array of Round Trip Times in microseconds


	QString trHost;			//!< host being trace-routed to as supplied by user/batch file
	QHostAddress trHostAddress;	//!< ::trHost resolved to an IP address

	TrStatus *tstat;		//!< saved copy of argument to ::TrWorkItem
	bool name_ok;			//!< whether host resolved or not.  Returned by isResolved().
};

#endif
