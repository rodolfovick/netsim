#include <stdio.h>
#include <stdlib.h>

#include "netsim.h"

int main(int argc, char *argv[]) 
{
	int ret = 0;
	int loop = 0;
	netsim_t net;

	if (argc < 3) {
		printf("Usage:\n");
		printf("netsim FILE INTERFACE\n");
		printf("\nFILE      PCAP file name\n");
		printf("INTERFACE Sending interface name\n");
		return -100;
	}

	if (argc == 4)
		loop = 1;

	ret = netsim_init(argv[1], argv[2], &net);
	if (ret < 0) {
		printf("Init fail\n");
		return ret;
	}
	
	do {
		ret = netsim_start(&net);
		if (ret < 0) {
			printf("Transmission fail\n");
			return ret;
		}
		if (loop) {
			ret = netsim_reinit(argv[1], &net);
			if (ret < 0) {
				printf("Reinit fail\n");
				return ret;
			}
		} 
	} while (loop);

	return 0;
}
