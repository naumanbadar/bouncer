#include "bouncer.h"

#include "linkedList.h"
#include "states.h"
#include "myFunctions.h"



struct linkedList * icmpStateList;



//int icmp_stateInList(void* data, Node node);

void process_pkt(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
	if (icmpStateList == NULL) {
		icmpStateList = newList();
	}

	struct ip *ip_header; /* The IP header */
	struct icmp *icmp_header;

	u_int size_ip;

	ip_header = (struct ip*) (packet + SIZE_ETHERNET);
	size_ip = ip_header->ip_hl * 4;
	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return;
	}

	unsigned short calculatedCheckSum = checksum((unsigned short*)ip_header,size_ip);
	if(calculatedCheckSum!=0){
		printf("BAD IP Packet\n");
		return;
	}

	/* Check IP header*/
	/* Check type of packet and process*/

	if (ip_header->ip_p == P_ICMP) {
//printf("**************************************************************");
		icmp_header = (struct icmp*) (packet + SIZE_ETHERNET + size_ip);

		calculatedCheckSum = checksum((unsigned short*)icmp_header,ip_header->ip_len-size_ip);
		if(calculatedCheckSum!=0){
				printf("BAD ICMP Packet\n");
				return;
			}


    processICMP(icmp_header,ip_header);
}

	/* Check ICMP header*/
	/* Check TCP header*/
	/* Check FTP header*/

	/* Send processed packet */
}

