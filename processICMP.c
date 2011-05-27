#include "states.h"
#include "linkedList.h"

void processICMP(const struct icmp *icmp_header, const struct ip *ip_header) {

	if (icmp_header->icmp_type == ICMP_ECHO) {
		printf("Ping received from %s ID:%d icm_state_size %d\n", inet_ntoa(ip_header->ip_src), icmp_header->icmp_hun.ih_idseq.icd_id, icmpStateList->size);
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

		//			state ->idNumber=;
		//			u_int16_t idOfIcmpPacket = icmp_header->icmp_hun->ih_idseq->icd_id;

	}
}

