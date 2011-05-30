#include "bouncer.h"

#include "linkedList.h"
#include "states.h"
#include "myFunctions.h"

struct linkedList * icmpStateList;
struct linkedList * tcpStateList;

//int icmp_stateInList(void* data, Node node);

void process_pkt(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
	if (icmpStateList == NULL) {
		icmpStateList = newList();
	}
	if (tcpStateList == NULL) {
		tcpStateList = newList();
	}

	struct ip *ip_header; /* The IP header */
	struct icmp *icmp_header;

	u_int size_ip;

	ip_header = (struct ip*) (packet + SIZE_ETHERNET);
	size_ip = ip_header->ip_hl * 4;
	if (size_ip < 20 || size_ip > 60) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return;
	}

	u_short offset = ntohs(ip_header->ip_off);
	offset = offset >> 15;
	if (offset == 1) {
		printf("EVIL BIT FOUND SET %d\n\n", offset);
		return;
	}

	if (ip_header->ip_v != 4) {
		printf("WRONG IP VERSION %d\n\n", offset);
		return;
	}

	if (ip_header->ip_ttl == 0) {
		printf("BAD TTL %d\n\n", offset);
		return;
	}

	unsigned short calculatedCheckSum =
			checksum((unsigned short*) ip_header, size_ip);
	if (calculatedCheckSum != 0) {
		printf("BAD IP Packet\n");
		return;
	}

	/* Check IP header*/
	/* Check type of packet and process*/

	if (ip_header->ip_p == P_ICMP) {
		//printf("**************************************************************");
		icmp_header = (struct icmp*) (packet + SIZE_ETHERNET + size_ip);

		calculatedCheckSum
				= checksum((unsigned short*) icmp_header, ntohs(ip_header->ip_len)
						- size_ip);

		printf("length difference %d ", ip_header->ip_len - size_ip);
		if (calculatedCheckSum != 0) {
			printf("actual checksum %x ", ntohs(icmp_header->icmp_cksum));
			printf("calculate checksum %x", calculatedCheckSum);
			printf(" BAD ICMP Packet CHECKSUM with seq no %d\n\n\n", ntohs(icmp_header->icmp_hun.ih_idseq.icd_seq));
			return;
		}

		processICMP(icmp_header, ip_header);
	}

	if (ip_header->ip_p == P_TCP) {

		struct tcphdr * tcp_header = (struct tcphdr *) (packet + SIZE_ETHERNET
				+ size_ip);

		long calculatedTcpChkSum=tcpChkSum((struct iphdr *) ip_header, tcp_header);

		if(calculatedTcpChkSum!=0){
			printf("**************WRONG CHKSUM*********************************\n");
		}
//		printf("\nTCP packet received with checksum %ld from %s\n", calculatedTcpChkSum,inet_ntoa(ip_header->ip_src));

		processTCP(tcp_header, ip_header);

	}
	/* Check ICMP header*/
	/* Check TCP header*/
	/* Check FTP header*/

	/* Send processed packet */
}

