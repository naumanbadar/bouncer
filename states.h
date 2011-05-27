#ifndef STATESHEADERFILE
#define STATESHEADERFILE
#include "bouncer.h"

extern struct linkedList * icmpStateList;

struct icmp_state
{
	u_int16_t idNumber;
	struct in_addr ip_src;
};


#endif
