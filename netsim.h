#ifndef NETSIM_H
#define NETSIM_H

// Return values
#define NS_OK		 	 0 ///< Success.
#define NS_NAME_ERR		-1 ///< File name error.
#define NS_FILE_NOT_FOUND	-2 ///< File not found.
#define NS_WRONG_FILE		-3 ///< Wrong file type.

// Macros
#define PCAP_FHDR sizeof(struct pcap_file_header)

/* Functions prototypes */
int ns_init(char *name);

#endif /* NETSIM_H */
