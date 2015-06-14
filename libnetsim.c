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
	FILE *ns_file = NULL; 			///< working pcap file.

	// Try to open file;
	if (!name)
		return NS_NAME_ERR;

	if (!(ns_file = fopen(name, "r")))
		return NS_FILE_NOT_FOUND;

	if (!(fread(&ns_fhdr, sizeof(struct pcap_file_header), 1, ns_file)))
		return NS_WRONG_FILE;

	printf("0x%08x\n", ns_fhdr.magic);

	return NS_OK;
}
