/* Port Bouncer
 * To be called as nbouncer local_ip local_port remote_ip remote_port
 */

#include "bouncer.h"

char * interface;
char * listenIP;
char * listenPort;
char * serverIP;
char * serverPort;

void
		process_pkt(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

int main(int argc, char *argv[]) {

	interface = argv[1];
	listenIP = argv[2];
	listenPort = argv[3];
	serverIP = argv[4];
	serverPort = argv[5];

	printf("\nInterface %s listenIP %s listenPort %s serverIP %s serverPort %s\n", interface, listenIP, listenPort, serverIP, serverPort);

	pcap_t *handle; /* Session handle */
	char *dev; /* The device to sniff on */
	char errbuf[PCAP_ERRBUF_SIZE]; /* Error string */
	//			struct bpf_program fp;		/* The compiled filter */
	//			char filter_exp[] = "ether host 00:22:43:9b:97:fa";	/* The filter expression */
	//			bpf_u_int32 mask;		/* Our netmask */
	//			bpf_u_int32 net;		/* Our IP */

	/* Define the device */
	//			dev = "wlan0";
	dev = interface;

	handle = pcap_open_live(dev, BUFSIZ, 0, 1000, errbuf);
	if (handle == NULL) {
		fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
		return (2);
	}

	char filter[50];
	char * fileter1 = "dst host ";
	strcpy(filter, fileter1);
	strcat(filter, listenIP);
	struct bpf_program fp; /* The compiled filter */
	bpf_u_int32 mask;
	bpf_u_int32 net;
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
		fprintf(stderr, "Couldn't get netmask for device %s: %s\n", dev, errbuf);
		net = 0;
		mask = 0;
	}

	if (pcap_compile(handle, &fp, filter, 0, net) == -1) {
		fprintf(stderr, "Couldn't parse filter %s: %s\n", filter, pcap_geterr(handle));
		return (2);
	}
	if (pcap_setfilter(handle, &fp) == -1) {
		fprintf(stderr, "Couldn't install filter %s: %s\n", filter, pcap_geterr(handle));
		return (2);
	}
	//			const u_char *packet;
	//			struct pcap_pkthdr header;
	//			packet = pcap_next(handle, &header);
	//			struct ip *ip_header;
	//			ip_header = (struct ip*) (packet + 14);
	//			printf("%s %s\n",inet_ntoa(ip_header->ip_src), inet_ntoa(ip_header->ip_dst));


	pcap_loop(handle, -1, process_pkt, NULL);
	//
	pcap_close(handle);

	return (0);
}//End of the bouncer
