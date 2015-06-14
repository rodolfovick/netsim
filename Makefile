all: netsim

libnetsim.o: libnetsim.c netsim.h
	gcc -o libnetsim.o -c libnetsim.c -D_GNU_SOURCE -W -Wall -std=c99 -pedantic

netsim.o: netsim.c netsim.h
	gcc -o netsim.o -c netsim.c -D_GNU_SOURCE -W -Wall -std=c99 -pedantic

netsim: netsim.o libnetsim.o
	gcc -o netsim netsim.o libnetsim.o 

clean:
	rm libnetsim.o netsim.o netsim
