#include <stdio.h>
#include <stdlib.h>

#include "netsim.h"

int main(int argc, char *argv[]) 
{
	int ret;

	if (argc != 2) {
		printf("Wrong arguments\n");
		return -100;
	}

	ret = ns_init(argv[1]);
	printf("f() -> %d\n", ret);
	return ret;
}
