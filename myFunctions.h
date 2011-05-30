#ifndef MYFUNCTIONS_H
#define  MYFUNCTIONS_H

void processICMP(struct icmp *icmp_header, struct ip *ip_header);
int icmp_stateInList(void* data, Node node);
u_short checksum(u_short *ptr, int length);
void processTCP(struct tcphdr *tcp_header, struct ip *ip_header);
int tcp_stateInList_wrt_sourceIpAndSourcePortAndDestinationPort(void* data, Node node);
int tcp_stateInList_wrt_bouncerPortAndIp(void* data, Node node);

long tcpChkSum(struct iphdr * myip, struct tcphdr * mytcp);
void sendIp(struct ip *ip_header);


u_short tcp_sum_calc(u_short len_tcp, u_char src_addr[], u_char dest_addr[], int padding, u_char buff[]);

#endif
