//
// File: IPv4Privacy.cpp
//
// Copyright (c) 2009, 2010  University of Toronto and Steve Harvey
//

#include "IPv4Privacy.h"

QVector<QPair<QHostAddress, int> > *IPv4Privacy::privs = 0;

/** Set the number of privacy bits and associated mask.  Compile
  * a list of all networks deemed to be non-public.
  */
IPv4Privacy::IPv4Privacy(int nbits) : nbits(nbits) {
	mask = 0xffffffff << nbits;

	if ( !privs ) {
		privs = new QVector<QPair<QHostAddress, int> >();
		*privs << QHostAddress::parseSubnet(QString("0.0.0.0/8")); 		// RFC 1700
		*privs << QHostAddress::parseSubnet(QString("10.0.0.0/8")); 		// RFC 1918
		*privs << QHostAddress::parseSubnet(QString("127.0.0.0/8")); 		// RFC 1700
		*privs << QHostAddress::parseSubnet(QString("169.254.0.0/16")); 	// RFC 3330
		*privs << QHostAddress::parseSubnet(QString("172.16.0.0/12")); 		// RFC 1918
		*privs << QHostAddress::parseSubnet(QString("192.0.2.0/24")); 		// RFC 3330
		*privs << QHostAddress::parseSubnet(QString("192.88.99.0/24"));		// RFC 3068
		*privs << QHostAddress::parseSubnet(QString("192.168.0.0/16")); 	// RFC 1918
		*privs << QHostAddress::parseSubnet(QString("224.0.0.0/3")); 		// RFC 3171 and 1700
	}
}


bool
IPv4Privacy::is_private_ip(QHostAddress& ha) {
	if ( !privs ) {
		// ctor will create database
		IPv4Privacy p(8);
	}
	QVector<QPair<QHostAddress, int> > p = *privs;
	QVector<QPair<QHostAddress, int> >::iterator i = p.begin();
	while ( i != p.end() ) {
		if ( ha.isInSubnet(*i) )
			return true;
		i++;
	}
	return false;
}

/** Apply the privacy policy.  The first hop in public IPv4 address space
  * is identified.  All IP addresses in the same subnet defined by that hop
  * and the number of bits in the privacy mask have their low-order bits
  * set to zero.  The number of non-public IP addresses in the traceroute
  * that occur before the first public hop is returned, so that the caller
  * may omit them from the reported traceroute.
  */
int
IPv4Privacy::apply(QVector<QHostAddress>& hav) {
	int ctr = 0;
	bool found_public = false;
	QHostAddress pub_src;

	QVector<QHostAddress>::iterator i = hav.begin();
	while ( i != hav.end() ) {
		if ( !found_public ) {
			if ( is_private_ip(*i) ) {
				ctr++;
			} else {
				pub_src = *i;
				found_public = true;
			}
		}
		if ( found_public && i->isInSubnet(pub_src, 32-nbits) ) {
			quint32 addr = i->toIPv4Address();
			i->setAddress(addr&mask);
		}
		i++;
	}
	return ctr;
}


