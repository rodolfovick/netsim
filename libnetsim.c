#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "netsim.h"

/**
 * Network simulation using a pcap file.
 */

/**
 * opens a PCAP file and returs the result.
 * @param file name string.
 * @param opened pcap struct pointer.
 * @return a integer with function result.
 */
int netsim_init(char *name, pcap_t **pcap)
{
	char errbuf[PCAP_ERRBUF_SIZE];

	(*pcap) = pcap_open_offline(name, errbuf);
	if (!(*pcap)) {
		printf("PCAP open error: %s\n", errbuf);
		return NS_OPEN_ERR;
	}

	return NS_OK;
}

/* Read packet callback */
void ns_pkt_read(u_char *user, const struct pcap_pkthdr *h, const u_char *pkt) 
{
	unsigned int i;

	for (i = 0; i < h->caplen; i++)
		printf("%02x ", pkt[i]);
	printf("\n\n");
}

/**
 * start the simulation.
 * @param the opened file pcap struct pointer.
 * @param a flag to indicate if the test should stop on the end of file or continue forever.
 * @return a integer with function result.
 */ 
int netsim_start(pcap_t *pcap, unsigned char loop)
{
	return pcap_dispatch(pcap, 0, ns_pkt_read, NULL);
}
