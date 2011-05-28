#ifndef MYFUNCTIONS_H
#define  MYFUNCTIONS_H

void processICMP(struct icmp *icmp_header, struct ip *ip_header);
int icmp_stateInList(void* data, Node node);
u_short checksum(u_short *ptr, int length);


#endif
