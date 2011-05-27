#ifndef MYFUNCTIONS_H
#define  MYFUNCTIONS_H

void processICMP(const struct icmp *icmp_header, const struct ip *ip_header);
int icmp_stateInList(void* data, Node node);


#endif
