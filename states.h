#ifndef STATESHEADERFILE
#define STATESHEADERFILE
#include "bouncer.h"

extern struct linkedList * icmpStateList;
extern struct linkedList * tcpStateList;
extern u_int16_t bouncerPort;

struct icmp_state
{
	u_int16_t idNumber;
	struct in_addr ip_src;
};

struct tcp_state
{
	u_int16_t senderSourcePort;
	u_int16_t senderDestinationPort;
	u_int16_t bouncerSourcePort;
	struct in_addr senderSourceIp;
	struct in_addr senderDestinationIp;
};


extern char * interface;
extern char * listenIP;
extern char * listenPort;
extern char * serverIP;
extern char * serverPort;



#endif
