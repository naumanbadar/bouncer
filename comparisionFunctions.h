int icmp_stateInList(void* data, Node node) {
	struct icmp_state * associationInList = (struct icmp_state*) node->data;
	struct icmp_state * associationNew = (struct icmp_state*) data;

	if (associationInList->idNumber == associationNew->idNumber && associationInList->ip_src.s_addr==associationNew->ip_src.s_addr) {
		return 1;
	}
	else
		return 0;
}
