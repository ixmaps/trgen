//
// File: IPv4Privacy.h
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#ifndef PRIVACY_H
#define PRIVACY_H

#include <QHostAddress>
#include <QPair>
#include <QVector>

/** Enforce obfuscation of first hop address within public
  * IP address space.
  */
class IPv4Privacy {

public:
	//! constructor
	//! \param nbits is the number of low-order bits to mask off of the first hop in public IPv4 address space.
	IPv4Privacy(int nbits);

	//! apply the privacy policy to the traceroute
	//! \param hav is a vector of host addresses in the traceroute
	//! \return the number of host addresses that occur before the first public hop
	int apply(QVector<QHostAddress>& hav);

	//! tell if a host address is not in public IPv4 space
	//! \param ha is the host address 
	static bool is_private_ip(QHostAddress& ha);


private:
	quint32 mask;			//!< mask applied to host addresses
	int nbits;			//!< copy of argument to constructor

	//! singleton to be created by first invocation of ctor
	static QVector<QPair<QHostAddress, int> > *privs;

};

#endif
