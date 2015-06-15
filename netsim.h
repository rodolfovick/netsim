#ifndef NETSIM_H
#define NETSIM_H

// Return values
#define NS_OK		 	 0 ///< Success.
#define NS_NAME_ERR		-1 ///< File name error.
#define NS_FILE_NOT_FOUND	-2 ///< File not found.
#define NS_WRONG_FILE		-3 ///< Wrong file type.
#define NS_PHDR_READ_ERR	-4 ///< Wrong file type.
#define NS_PACKET_SIZE_ERR	-5 ///< Wrong file type.
#define NS_PACKET_READ_ERR	-6 ///< Wrong file type.

// Macros
#define PCAP_FHDR sizeof(struct pcap_file_header)
#define PCAP_PHDR sizeof(struct pcap_pkthdr)

#define PKT_MIN 		0
#define PKT_MAX			1527
#define PCAP_PKT_SIZE(p) ((p > PKT_MIN) && (p < PKT_MAX))

/* Functions prototypes */
int ns_init(char *name);

#endif /* NETSIM_H */
