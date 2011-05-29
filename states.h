#ifndef STATESHEADERFILE
#define STATESHEADERFILE
#include "bouncer.h"

extern struct linkedList * icmpStateList;
extern struct linkedList * tcpStateList;

struct icmp_state
{
	u_int16_t idNumber;
	struct in_addr ip_src;
};

struct tcp_state
{
	u_int16_t senderSourcePort;
	u_int16_t bouncerSourcePort;
	struct in_addr senderIp;
};


extern char * interface;
extern char * listenIP;
extern char * listenPort;
extern char * serverIP;
extern char * serverPort;



#endif
