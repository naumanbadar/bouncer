#include "bouncer.h"

//u_short checksum(u_short *ptr, int length)
//{
//    register int sum = 0;
//    u_short answer = 0;
//    register u_short *w = ptr;
//    register int nleft = length;
//
//    while (nleft > 1) {
//        sum += *w++;
//        nleft -= 2;
//    }
//
//    sum = (sum >> 16) + (sum & 0xFFFF);
//    sum += (sum >> 16);
//    answer = ~sum;
//    return (answer);
//}

unsigned short checksum(unsigned short *ip, int len)
{
   long sum = 0;  /* assume 32 bit long, 16 bit short */
   while(len > 1)
   {
       sum += *ip;
       ip++;

       if(sum & 0x80000000)
       {
           /* if high order bit set, fold */
           sum = (sum & 0xFFFF) + (sum >> 16);
       }
       len -= 2;
   }

   if(len)
   {
       /* take care of left over byte */
       sum += (unsigned short) *(unsigned char *)ip;
   }

   while(sum>>16)
   {
       sum = (sum & 0xFFFF) + (sum >> 16);
   }
   return ~sum;
}
