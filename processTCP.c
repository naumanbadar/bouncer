#include "states.h"
#include "linkedList.h"
#include "bouncer.h"
#include <unistd.h>

u_int16_t bouncerPort = 6000;

void processTCP(struct tcphdr *tcp_header, struct ip *ip_header) {
	//	if (icmp_header->icmp_code != 0) {
	//		printf("BAD ICMP CODE\n\n\n");
	//		return;
	//	}
	//
	//	if (icmp_header->icmp_type == ICMP_ECHO) {
	//
	struct tcp_state state;
	state.senderSourceIp.s_addr = ip_header->ip_src.s_addr;
	state.senderDestinationIp.s_addr = ip_header->ip_dst.s_addr;
	state.senderSourcePort = tcp_header->th_sport;
	state.senderDestinationPort = tcp_header->th_dport;

	///CHECK FOR RETURN PATH FIRST

	if (containsNode(tcpStateList, &state, tcp_stateInList_wrt_sourceIpAndSourcePortAndDestinationPort)
			== 0) {

		struct tcp_state * newState;
		newState = (struct tcp_state *) malloc(sizeof(struct tcp_state));
		newState->senderSourceIp.s_addr = state.senderSourceIp.s_addr;
		newState->senderDestinationIp.s_addr = state.senderDestinationIp.s_addr;
		newState->senderSourcePort = state.senderSourcePort;
		newState->senderDestinationPort = state.senderDestinationPort;
		newState->bouncerSourcePort = ++bouncerPort;
		listAdd(tcpStateList, newState);
		printf("Forward Path New State list size %d\n",tcpStateList->size);

	}
	//		state.idNumber = icmp_header->icmp_hun.ih_idseq.icd_id;
	//		state.ip_src = ip_header->ip_src;
	//
	//		if (containsNode(icmpStateList, &state, icmp_stateInList) == 0) {
	//
	//			printf("New State ");
	//			struct icmp_state * newState;
	//			newState = (struct icmp_state *) malloc(sizeof(struct icmp_state));
	//			newState->idNumber = state.idNumber;
	//			newState->ip_src.s_addr = state.ip_src.s_addr;
	//			listAdd(icmpStateList, newState);
	//
	//		}
	//		printf("Ping received from %s ", inet_ntoa(ip_header->ip_src));
	//		printf("to %s ID:%d icm_state_size %d\n", inet_ntoa(ip_header->ip_dst), icmp_header->icmp_hun.ih_idseq.icd_id, icmpStateList->size);
	//
	//		ip_header->ip_src.s_addr = inet_addr(listenIP);
	//		ip_header->ip_dst.s_addr = inet_addr(serverIP);
	//
	//		sendIp(ip_header);
	//
	//	} else if (icmp_header->icmp_type == ICMP_ECHOREPLY) {
	//
	//		printf("ECHOREPLY received from %s ", inet_ntoa(ip_header->ip_src));
	//		printf("to %s ID:%d icm_state_size %d\n\n\n", inet_ntoa(ip_header->ip_dst), icmp_header->icmp_hun.ih_idseq.icd_id, icmpStateList->size);
	//
	//		struct icmp_state state;
	//		state.idNumber = icmp_header->icmp_hun.ih_idseq.icd_id;
	//		state.ip_src = ip_header->ip_src;
	//		struct icmp_state * savedState;
	//		struct node* fetchedNode;
	//		if ((fetchedNode = fetchNode(icmpStateList, &state, icmp_stateInList))
	//				== NULL) {
	//			printf("BAD ICMP REPLY ID\n\n\n");
	//			return;
	//		}
	//		savedState = fetchedNode->data;
	//		ip_header->ip_src.s_addr = inet_addr(listenIP);
	//		ip_header->ip_dst.s_addr = savedState->ip_src.s_addr;
	//
	//		sendIp(ip_header);
	//
	//	} else {
	//		printf("ICMP BAD TYPE received from %s ", inet_ntoa(ip_header->ip_src));
	//		printf("to %s ID:%d icm_state_size %d\n\n\n", inet_ntoa(ip_header->ip_dst), icmp_header->icmp_hun.ih_idseq.icd_id, icmpStateList->size);
	//	}
}

