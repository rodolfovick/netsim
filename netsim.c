#include <stdio.h>
#include <stdlib.h>

#include "netsim.h"

int main(int argc, char *argv[]) 
{
	int ret = 0;
	netsim_t net;

	if (argc != 3) {
		printf("Wrong arguments\n");
		return -100;
	}

	ret = netsim_init(argv[1], argv[2], &net);
	printf("f() -> %d\n", ret);
	if (ret < 0) return ret;
	
	ret = netsim_start(&net, 0);
	printf("f() -> %d\n", ret);

	return ret;
}
