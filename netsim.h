#ifndef NETSIM_H
#define NETSIM_H

// PCAP lib
#include <pcap/pcap.h>

// Return values
#define NS_OK		0
#define NS_OPEN_ERR	-1

// Macros
#define NS_PKT_MAX	1522

// Open a pcap file for reading
int netsim_init(char *name, pcap_t **pcap);

// Start tranmission (until the end or forever)
int netsim_start(pcap_t *pcap, unsigned char loop);

#endif /* NETSIM_H */
