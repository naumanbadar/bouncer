#include "linkedList.h"
#include "states.h"

int icmp_stateInList(void* data, Node node) {
	struct icmp_state * associationInList = (struct icmp_state*) node->data;
	struct icmp_state * associationNew = (struct icmp_state*) data;

	if (associationInList->idNumber == associationNew->idNumber) {
		return 1;
	}
	else
		return 0;
}

int tcp_stateInList_wrt_sourceIpAndSourcePortAndDestinationPort(void* data, Node node) {
	struct tcp_state * associationInList = (struct tcp_state *) node->data;
	struct tcp_state * associationNew = (struct tcp_state *) data;

	if (associationInList->senderSourcePort == associationNew->senderSourcePort &&associationInList->senderDestinationPort == associationNew->senderDestinationPort&& associationInList->senderSourceIp.s_addr==associationNew->senderSourceIp.s_addr) {
		return 1;
	}
	else
		return 0;
}
int tcp_stateInList_wrt_bouncerPortAndIp(void* data, Node node) {
	struct tcp_state * associationInList = (struct tcp_state *) node->data;
	struct tcp_state * associationNew = (struct tcp_state *) data;

//	if (associationNew->senderDestinationPort == associationInList->bouncerSourcePort&&associationNew->senderSourceIp.s_addr==associationInList->senderDestinationIp.s_addr) {
	if (associationNew->senderDestinationPort == associationInList->bouncerSourcePort) {
		printf("FROM COMPARISION FUNCTION %s ",inet_ntoa(associationNew->senderSourceIp));
		printf("%s\n",inet_ntoa(associationInList->senderDestinationIp));
		return 1;
	}
	else
		return 0;
}


