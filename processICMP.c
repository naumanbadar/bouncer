#include "states.h"
#include "linkedList.h"
#include "bouncer.h"
#include <unistd.h>
#include "myFunctions.h"



void processICMP(struct icmp *icmp_header, struct ip *ip_header) {
	if (icmp_header->icmp_code != 0) {
		printf("BAD ICMP CODE\n\n\n");
		return;
	}

	if (icmp_header->icmp_type == ICMP_ECHO) {

		struct icmp_state state;
		state.idNumber = icmp_header->icmp_hun.ih_idseq.icd_id;
		state.ip_src = ip_header->ip_src;

		if (containsNode(icmpStateList, &state, icmp_stateInList) == 0) {

			printf("New State ");
			struct icmp_state * newState;
			newState = (struct icmp_state *) malloc(sizeof(struct icmp_state));
			newState->idNumber = state.idNumber;
			newState->ip_src.s_addr = state.ip_src.s_addr;
			listAdd(icmpStateList, newState);

		}
		printf("Ping received from %s ", inet_ntoa(ip_header->ip_src));
		printf("to %s ID:%d icm_state_size %d\n", inet_ntoa(ip_header->ip_dst), icmp_header->icmp_hun.ih_idseq.icd_id, icmpStateList->size);

		ip_header->ip_src.s_addr = inet_addr(listenIP);
		ip_header->ip_dst.s_addr = inet_addr(serverIP);

		sendIp(ip_header);

	} else if (icmp_header->icmp_type == ICMP_ECHOREPLY) {

		printf("ECHOREPLY received from %s ", inet_ntoa(ip_header->ip_src));
		printf("to %s ID:%d icm_state_size %d\n\n\n", inet_ntoa(ip_header->ip_dst), icmp_header->icmp_hun.ih_idseq.icd_id, icmpStateList->size);

		struct icmp_state state;
		state.idNumber = icmp_header->icmp_hun.ih_idseq.icd_id;
		state.ip_src = ip_header->ip_src;
		struct icmp_state * savedState;
		struct node* fetchedNode;
		if ((fetchedNode = fetchNode(icmpStateList, &state, icmp_stateInList))
				== NULL) {
			printf("BAD ICMP REPLY ID\n\n\n");
			return;
		}
		savedState = fetchedNode->data;
		ip_header->ip_src.s_addr = inet_addr(listenIP);
		ip_header->ip_dst.s_addr = savedState->ip_src.s_addr;

		sendIp(ip_header);

	} else {
		printf("ICMP BAD TYPE received from %s ", inet_ntoa(ip_header->ip_src));
		printf("to %s ID:%d icm_state_size %d\n\n\n", inet_ntoa(ip_header->ip_dst), icmp_header->icmp_hun.ih_idseq.icd_id, icmpStateList->size);
	}
}

void sendIp(struct ip *ip_header) {

	int fd = socket(PF_INET, SOCK_RAW, IPPROTO_RAW);
	int headerIncluided = 1;
	if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &headerIncluided, sizeof(headerIncluided))
			!= 0) {
		printf("Error in OPTS set\n");
		return;
	}

	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = ip_header->ip_dst.s_addr;

	int errno;

	if (sendto(fd, (char*) ip_header, ntohs(ip_header->ip_len), 0, (struct sockaddr*) &serverAddress, sizeof(struct sockaddr))
			== -1) {
		printf("sending error %d %d\n", errno, ntohs(ip_header->ip_len));
		perror("error");
	}
	printf("Packet sent from %s ", inet_ntoa(ip_header->ip_src));
	printf("to %s \n\n\n", inet_ntoa(ip_header->ip_dst));
	close(fd);
}

