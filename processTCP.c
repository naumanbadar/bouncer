#include "states.h"
#include "linkedList.h"
#include "bouncer.h"
#include <unistd.h>
#include "myFunctions.h"

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
	state.senderSourcePort = ntohs(tcp_header->th_sport);
	state.senderDestinationPort = ntohs(tcp_header->th_dport);

	///CHECK FOR RETURN PATH FIRST
	if (containsNode(tcpStateList, &state, tcp_stateInList_wrt_bouncerPortAndIp)== 1) {
		printf("############################################################FOUND IN RETURN PATH\n");

		printf("source PORT %d destination PORT %d  ",ntohs(tcp_header->th_sport),ntohs(tcp_header->th_dport));
		printf("*****************************************reply received from server %s ",inet_ntoa(ip_header->ip_src));
		printf("destined towards %s\n\n\n",inet_ntoa(ip_header->ip_dst));





		return;

	}


	//	if(tcp_header->th_flags==TH_SYN){
	if (containsNode(tcpStateList, &state, tcp_stateInList_wrt_sourceIpAndSourcePortAndDestinationPort)
			== 0) {

		struct tcp_state * newState;
		newState = (struct tcp_state *) malloc(sizeof(struct tcp_state));
		newState->senderSourceIp.s_addr = state.senderSourceIp.s_addr;
		newState->senderDestinationIp.s_addr = state.senderDestinationIp.s_addr;
		newState->senderSourcePort = state.senderSourcePort;
		newState->senderDestinationPort = state.senderDestinationPort;
		state.bouncerSourcePort = ++bouncerPort;
		newState->bouncerSourcePort = state.bouncerSourcePort;
		listAdd(tcpStateList, newState);
		printf("Forward Path New State list size %d\n", tcpStateList->size);

	} else {
		struct node* fetchedNode;
		struct tcp_state * savedState;
		fetchedNode
				= fetchNode(tcpStateList, &state, tcp_stateInList_wrt_sourceIpAndSourcePortAndDestinationPort);
		savedState = (struct tcp_state *) fetchedNode->data;
		state.bouncerSourcePort = savedState->bouncerSourcePort;
	}

	tcp_header->th_sport = htons(state.bouncerSourcePort);
	//	tcp_header->th_dport = htons(serverPort);
	tcp_header->th_sum = 0;
	ip_header->ip_src.s_addr = inet_addr(listenIP);
	ip_header->ip_dst.s_addr = inet_addr(serverIP);

	long calculatedTcpChkSum =
			tcpChkSum((struct iphdr *) ip_header, tcp_header);

	tcp_header->th_sum = htons(calculatedTcpChkSum);

	//	printf("Packet to be sent on port %d\n",tcp_header->th_dport);

	sendIp(ip_header);
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

