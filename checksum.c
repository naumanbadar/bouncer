#include "bouncer.h"

u_short checksum(u_short *ptr, int length)
{
    register int sum = 0;
    u_short answer = 0;
    register u_short *w = ptr;
    register int nleft = length;

    while (nleft > 1) {
        sum += *w++;
        nleft -= 2;
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    answer = ~sum;
    printf("%u\n",(u_short)answer);
    printf("////End/////\n");
    return (answer);
}
