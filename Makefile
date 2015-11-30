ifdef CROSS_COMPILE
	CC=$(CROSS_COMPILE)gcc
else
	CC=gcc
endif

all: netsim

libnetsim.o: libnetsim.c netsim.h
	$(CC) -o libnetsim.o -c libnetsim.c -D_GNU_SOURCE -W -Wall -std=c99 -pedantic -g

netsim.o: netsim.c netsim.h
	$(CC) -o netsim.o -c netsim.c -D_GNU_SOURCE -W -Wall -std=c99 -pedantic -g

netsim: netsim.o libnetsim.o
	$(CC) -o netsim netsim.o libnetsim.o -lpcap

clean:
	rm libnetsim.o netsim.o netsim
