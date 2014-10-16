//
// File: traceroute.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <QString>
#include <QHostAddress>

/** Describes a single probe in a traceroute.
  */
class TRItem {

public:

	//! traceroute item status
	enum tri_status {
		replied='r',			//!< destination host replied, or TTL exceeded ICMP 11/0
		timed_out='t',			//!< no reply whatsoever
		host_unreach='h',		//!< not used - Host Unreachable ICMP 3/1
		netw_unreach='n',		//!< not used - Network Unreachable ICMP 3/0
		proto_unavail='p',		//!< not used - Protocol Unreachable ICMP 3/2
		frag_needed='f'			//!< not used - Fragmentation Required ICMP 3/4
						// there are possible ICMP codes 3/0 to 3/15 
	};

	tri_status		status;		//!< status for this probe
	QHostAddress		*ip_addr;	//!< IPv4 address for this probe
	int			rtt_ms;		//!< Round Trip Time in milliseconds this probe

	//! constructor
	//! \param status is the probe status
	//! \param ip_addr is the IPv4 address
	//! \param rtt_ms is the Round Trip Time in milliseconds if known
	TRItem(tri_status status, QHostAddress *ip_addr, int rtt_ms);

	//! destructor
	~TRItem();
};

	
/** Describe a traceroute.
  */
class Traceroute {

public:

	//! protocol used by probes in this traceroute
	enum tr_proto {
		icmp='i',
		udp='u',
		tcp='t'
	};

	//! completion status for this traceroute
	enum tr_status {
		complete='c',
		incomplete='i'
	};

	//! maximum number of probes per hop. \sa items
	const static unsigned int	MAX_ATTEMPTS = 10;
	QString			dest;		//!< user-specified destination
	QHostAddress		dest_ip;	//!< resolved IP address
	QString			submitter;	//!< user name or handle
	QString			zip_code;	//!< user ZIP/Postal code
	int			privacy;	//!< number of source bits to mask
	int			timeout;	//!< max. wait time for a reply in seconds
	tr_proto		protocol;	//!< ICMP or UDP or TCP
	tr_status		status;		//!< whether a reply was gotten from the destination
	QString			client;		//!< client program
	QString			cl_ver;		//!< version of client program

	//! constructor
	//! \param dest is the traceroute destination as a hostname or dotted-quad
	//! \param dest_ip is the destination resolved as an IP address
	//! \param submitter is the submitter's name or handle
	Traceroute(QString& dest, QHostAddress& dest_ip, const QString& submitter);

	//! setter for maxhops
	inline void 		set_maxhops(int mh) { maxhops = mh; }
	//! getter for maxhops
	inline int 		get_maxhops() { return maxhops; }

	//! setter for attempts
	inline void 		set_attempts(int att) { attempts = att; }
	//! getter for attempts
	inline int  		get_attempts() { return attempts; }

	//! setter for privacy
	inline void 		set_privacy(int pr) { privacy = pr; }
	//! getter for privacy
	inline int  		get_privacy() { return privacy; }

	//! setter for timeout
	inline void 		set_timeout(int to) { timeout = to; }
	//! getter for timeout
	inline int  		get_timeout() { return timeout; }

	//! setter for protocol
	inline void 		set_protocol(tr_proto pr) { protocol = pr; }
	//! getter for protocol
	inline tr_proto		get_protocol() { return protocol; }

	//! setter for status
	inline void 		set_status(tr_status st) { status = st; }
	//! getter for status
	inline tr_status 	get_status() { return status; }

	//! setter for zip_code
	inline void 		set_zip(QString& z) { zip_code = z; }
	//! getter for zip_code
	inline QString& 	get_zip() { return zip_code; }

	//! set the client program name and version
	inline void		set_client(QString& cli, QString& cli_ver) { client = cli; cl_ver = cli_ver; }

	//! add a traceroute item (probe result) to a traceroute
	//! \param hop_num is the hop number from the user to the computer being tracerouted to
	//! \param attempt is the attempt for this hop number
	//! \param tr_item is the traceroute item
	void			add_item(int hop_num, unsigned int attempt, TRItem *tr_item);

	//! marshall the traceroute for submission as HTTP POST data
	//! \return string of POST data
	QString&		format();

private:
	int			maxhops;	//!< maximum hops to attempt
	int			attempts;	//!< number of attempts per hop distance

	QVector<TRItem *> 	items[MAX_ATTEMPTS];	//!< each index contains all hops for an attempt
	QString			http_repr;	//!< representation for HTTP submission

};

#endif
