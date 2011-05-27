#define SIZE_ETHERNET 14

void process_pkt(u_char *args, const struct pcap_pkthdr *header, const u_char *packet){

		const struct ip *ip_header; /* The IP header */


		u_int size_ip;

			ip_header = (struct ip*)(packet + SIZE_ETHERNET);
			size_ip = ip_header->ip_hl*4;
			if (size_ip < 20) {
				printf("   * Invalid IP header length: %u bytes\n", size_ip);
				return;
			}
	
	/* Check IP header*/
		printf("Packet received from %s\n",inet_ntoa(ip_header->ip_src));
	/* Check type of packet and process*/
	


	/* Check ICMP header*/
	/* Check TCP header*/
	/* Check FTP header*/

	/* Send processed packet */
}

