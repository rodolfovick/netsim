#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pcap.h>

#include "netsim.h"

/**
 * Network simulation using a pcap file.
 */


/**
 * Read pcap file, initializing the simulation process.
 * @param a character pointer with the file name.
 * @return an integer with the initialization result.
 */ 
int ns_init(char *name) 
{
	struct pcap_file_header ns_fhdr; 	///< pcap file header.
	struct pcap_pkthdr ns_phdr; 		///< pcap packet header.
	FILE *ns_file = NULL; 			///< working pcap file.
	// FIXME: just for now
	char buffer[1526];
	unsigned int i;

	// Try to open file;
	if (!name)
		return NS_NAME_ERR;

	if (!(ns_file = fopen(name, "r")))
		return NS_FILE_NOT_FOUND;

	// Read file header
	if ((fread(&ns_fhdr, 1, PCAP_FHDR, ns_file)) < PCAP_FHDR)
		return NS_WRONG_FILE;

	printf("0x%08x\n\n", ns_fhdr.magic);

	// Read all pcap packets headers and packet content
	while (!feof(ns_file)) {
		if ((fread(&ns_phdr, 1, PCAP_PHDR, ns_file)) < PCAP_PHDR)
			return NS_PHDR_READ_ERR;

		if (!PCAP_PKT_SIZE(ns_phdr.caplen)) 
			return NS_PACKET_SIZE_ERR;

		if ((fread(buffer, 1, ns_phdr.caplen, ns_file)) < ns_phdr.caplen)
			return NS_PACKET_READ_ERR;


		// FIXME: just for now
		for (i = 0; i < ns_phdr.caplen; i++)
			printf("%02x", buffer[i]);
		printf("\n\n");
	}

	return NS_OK;
}
