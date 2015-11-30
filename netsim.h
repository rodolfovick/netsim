#ifndef NETSIM_H
#define NETSIM_H

// PCAP lib
#include <pcap/pcap.h>
#include <linux/if_packet.h>

// Return values
#define NS_OK		0
#define NS_OPEN_ERR	-1
#define NS_SOCKET_ERR	-2
#define NS_IF_ERR	-3

// Macros
#define NS_PKT_MAX	1522

// Netsim data holding structure
typedef struct netsim_s {
	pcap_t *pcap;		//< PCAP structure
	int fd;			//< Socket file descriptor
	int ifindex;		//< Packet information
	int reset;		//< Timer reset
} netsim_t;

// Open a pcap file for reading
int netsim_init(char *name, char *ifname, netsim_t *net);

// Start tranmission
int netsim_start(netsim_t *net);

// Finish the software
int netsim_end(netsim_t *net);

// Restart the PCAP file 
int netsim_reinit(char *name, netsim_t *net);

#endif /* NETSIM_H */
