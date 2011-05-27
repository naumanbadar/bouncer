/* Port Bouncer
* To be called as nbouncer local_ip local_port remote_ip remote_port
*/

#include "bouncer.h"


void process_pkt(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

int main(int argc, char *argv[])
{
			pcap_t *handle;			/* Session handle */
			char *dev;			/* The device to sniff on */
			char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */
//			struct bpf_program fp;		/* The compiled filter */
//			char filter_exp[] = "ether host 00:22:43:9b:97:fa";	/* The filter expression */
//			bpf_u_int32 mask;		/* Our netmask */
//			bpf_u_int32 net;		/* Our IP */

			/* Define the device */
			dev = "wlan0";

			handle = pcap_open_live(dev, BUFSIZ, 0, 1000, errbuf);
			if (handle == NULL) {
				fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
				return(2);
			}

			pcap_loop(handle, -1, process_pkt, NULL);

			pcap_close(handle);

			return(0);
}//End of the bouncer
