#include "bouncer.h"

#include "linkedList.h"
#include "states.h"
#include "comparisionFunctions.h"

#define SIZE_ETHERNET 14
#define P_ICMP 1

struct linkedList * icmpStateList;

//int icmp_stateInList(void* data, Node node);

void process_pkt(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {

	if (icmpStateList == NULL) {
		icmpStateList = newList();
	}

	const struct ip *ip_header; /* The IP header */
	const struct icmp *icmp_header;

	u_int size_ip;

	ip_header = (struct ip*) (packet + SIZE_ETHERNET);
	size_ip = ip_header->ip_hl * 4;
	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return;
	}

	/* Check IP header*/
	/* Check type of packet and process*/

	if (ip_header->ip_p == P_ICMP) {

		icmp_header = (struct icmp*) (packet + SIZE_ETHERNET + size_ip);
		printf("Ping received from %s ID:%d icm_state_size %d\n", inet_ntoa(ip_header->ip_src),icmp_header->icmp_hun.ih_idseq.icd_id, icmpStateList->size);

		if (icmp_header->icmp_type == ICMP_ECHO) {

			struct icmp_state state;
			state.idNumber = icmp_header->icmp_hun.ih_idseq.icd_id;
			state.ip_src = ip_header->ip_src;

			if (containsNode(icmpStateList, &state, icmp_stateInList) == 0) {

				printf("New State ");
				struct icmp_state * newState;
				newState
						= (struct icmp_state *) malloc(sizeof(struct icmp_state));
				newState->idNumber = state.idNumber;
				newState->ip_src.s_addr = state.ip_src.s_addr;
				listAdd(icmpStateList, newState);

			}

			//			state ->idNumber=;
			//			u_int16_t idOfIcmpPacket = icmp_header->icmp_hun->ih_idseq->icd_id;

		}

	}

	/* Check ICMP header*/
	/* Check TCP header*/
	/* Check FTP header*/

	/* Send processed packet */
}

