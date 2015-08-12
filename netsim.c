#include <stdio.h>
#include <stdlib.h>

#include "netsim.h"

int main(int argc, char *argv[]) 
{
	int ret = 0;
	netsim_t net;

	if (argc != 3) {
		printf("Usage:\n");
		printf("netsim FILE INTERFACE\n");
		printf("\nFILE      PCAP file name\n");
		printf("INTERFACE Sending interface name\n");
		return -100;
	}

	ret = netsim_init(argv[1], argv[2], &net);
	if (ret < 0) {
		printf("Init fail\n");
		return ret;
	}
	
	ret = netsim_start(&net, 0);
	if (ret < 0) {
		printf("Transmission fail\n");
		return ret;
	}

	return 0;
}
