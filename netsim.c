#include <stdio.h>
#include <stdlib.h>

#include "netsim.h"

int main(int argc, char *argv[]) 
{
	int ret = 0;
	pcap_t *pcap = NULL;

	if (argc != 2) {
		printf("Wrong arguments\n");
		return -100;
	}

	ret = netsim_init(argv[1], &pcap);
	printf("f() -> %d\n", ret);
	ret = netsim_start(pcap, 0);
	printf("f() -> %d\n", ret);
	return ret;
}
