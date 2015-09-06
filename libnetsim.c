#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> 
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <errno.h>

#include "netsim.h"

/**
 * Network simulation using a pcap file.
 */

/* Wait packet time */
void ns_pkt_timer(struct timeval t, int reset) 
{
	static struct timeval si;
	struct timeval sd;
	struct timeval s;

	static struct timeval ti;
	struct timeval td;

	if (reset) {
		memcpy(&ti, &t, sizeof(struct timeval));
		gettimeofday(&si, NULL);
	}
	
	timersub(&t, &ti, &td);
	do {
		gettimeofday(&s, NULL);
		timersub(&s, &si, &sd);
	} while (timercmp(&sd, &td, <));
}

struct sockaddr_ll * ns_sockaddr_init(int ifindex) 
{
	struct sockaddr_ll *sa;
	
	sa = (struct sockaddr_ll *)malloc(sizeof(struct sockaddr_ll));
	memset(sa, 0, sizeof (struct sockaddr_ll));

	sa->sll_family    = AF_PACKET;
	sa->sll_ifindex   = ifindex;
	sa->sll_protocol  = htons(ETH_P_ALL);

	return sa;
}

/* Read packet callback */
void ns_pkt_read(u_char *user, const struct pcap_pkthdr *h, const u_char *pkt) 
{
	netsim_t *net = (netsim_t *)user;
	static struct sockaddr_ll *sa = NULL;
	int ret;

	ns_pkt_timer(h->ts, net->reset);
	if (net->reset) 
		net->reset = 0;

	if (!sa)
		sa = ns_sockaddr_init(net->ifindex);

	ret = sendto(net->fd, pkt, h->caplen, 0, (struct sockaddr *)sa, sizeof (struct sockaddr_ll));
	if (ret < 0)
		printf("Send error: %s\n", strerror(errno));
}

/**
 * opens a PCAP file and returs the result.
 * @param file name string.
 * @param opened pcap struct pointer.
 * @return a integer with function result.
 */
int netsim_init(char *name, char *ifname, netsim_t *net)
{
	pcap_t *pcap;
	int fd;
	struct ifreq ifr;
	char errbuf[PCAP_ERRBUF_SIZE];

	// Open PCAP file
	pcap = pcap_open_offline(name, errbuf);
	if (!pcap) {
		printf("PCAP open error: %s\n", errbuf);
		return NS_OPEN_ERR;
	}

	// Open transmission socket
	fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (fd < 0) {
		printf("Socket open error: %s\n", strerror(errno));
		return NS_SOCKET_ERR;
	}

	// Associate socket with interface name
	memset(&ifr, 0, sizeof(ifr));
	strncpy (ifr.ifr_name, ifname, sizeof(ifr.ifr_name) - 1);
	ifr.ifr_name[sizeof(ifr.ifr_name)-1] = '\0';

	if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1) {
		printf("Interface %s not found\n", ifname);
		close(fd);
		return NS_IF_ERR;
	}	

        ioctl(fd, SIOCGIFFLAGS, &ifr);
	if ( (ifr.ifr_flags & IFF_UP) == 0) {
		printf("Interface %s down\n", ifname);
                close(fd);
		return NS_IF_ERR;
        }

        ioctl(fd, SIOCGIFINDEX, &ifr);

	net->pcap = pcap;
	net->fd = fd;
	net->ifindex = ifr.ifr_ifindex;

	return NS_OK;
}

/**
 * start the simulation.
 * @param the opened file pcap struct pointer.
 * @return a integer with function result.
 */ 
int netsim_start(netsim_t *net)
{
	net->reset = 1;
	return pcap_dispatch(net->pcap, 0, ns_pkt_read, (u_char *)net);
}

/**
 * Reinit the simulation.
 * @param the opened file pcap struct pointer.
 * @return a integer with function result.
 */ 
int netsim_reinit(char *name, netsim_t *net)
{
	pcap_t *pcap;
	char errbuf[PCAP_ERRBUF_SIZE];

	pcap = net->pcap;
	pcap_close(pcap);

	pcap = pcap_open_offline(name, errbuf);
	if (!pcap) {
		printf("PCAP open error: %s\n", errbuf);
		return NS_OPEN_ERR;
	}
	pcap = net->pcap;

	return NS_OK;
}
