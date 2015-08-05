#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "netsim.h"

/**
 * Network simulation using a pcap file.
 */

/* Wait packet time */
void ns_pkt_timer(struct timeval t, int reset) 
{
	static struct timeval ti;
	struct timeval td;

	static struct timeval si;
	struct timeval sd;
	struct timeval s;


	if (reset) {
		memcpy(&ti, &t, sizeof(struct timeval));
		gettimeofday(&si, NULL);
	}
	
	timersub(&t, &ti, &td);
	do {
		gettimeofday(&s, NULL);
		timersub(&s, &si, &sd);
	} while (timercmp(&sd, &td, <));
	printf("%ld.%ld %ld.%ld ", td.tv_sec, td.tv_usec, sd.tv_sec, sd.tv_usec);
}

/* Read packet callback */
void ns_pkt_read(u_char *user, const struct pcap_pkthdr *h, const u_char *pkt) 
{
	unsigned int i;
	int *reset = (int *)user;

	ns_pkt_timer(h->ts, *reset);
	*reset = 0;
 
	for (i = 0; i < h->caplen; i++)
		printf("%02x ", pkt[i]);
	printf("\n\n");
}

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

/**
 * start the simulation.
 * @param the opened file pcap struct pointer.
 * @param a flag to indicate if the test should stop on the end of file or continue forever.
 * @return a integer with function result.
 */ 
int netsim_start(pcap_t *pcap, unsigned char loop)
{
	int reset = 1;
	return pcap_dispatch(pcap, 0, ns_pkt_read, (u_char *)&reset);
}
