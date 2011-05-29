#include "bouncer.h"
struct tcp_pseudo /*the tcp pseudo header*/
{
  __u32 src_addr;
  __u32 dst_addr;
  __u8 zero;
  __u8 proto;
  __u16 length;
} pseudohead;



long tcpChkSum(struct iphdr * myip, struct tcphdr * mytcp) {

        u_short total_len = ntohs(myip->tot_len);

        int tcpopt_len = mytcp->th_off*4 - 20;
        int tcpdatalen = total_len - (mytcp->th_off*4) - (myip->ihl*4);

        pseudohead.src_addr=myip->saddr;
        pseudohead.dst_addr=myip->daddr;
        pseudohead.zero=0;
        pseudohead.proto=IPPROTO_TCP;
        pseudohead.length=htons(sizeof(struct tcphdr) + tcpopt_len + tcpdatalen);

        int totaltcp_len = sizeof(struct tcp_pseudo) + sizeof(struct tcphdr) + tcpopt_len + tcpdatalen;
        unsigned short * tcp = (unsigned short *)malloc(totaltcp_len);


        memcpy((unsigned char *)tcp,&pseudohead,sizeof(struct tcp_pseudo));
        memcpy((unsigned char *)tcp+sizeof(struct tcp_pseudo),(unsigned char *)mytcp,sizeof(struct tcphdr));
        memcpy((unsigned char *)tcp+sizeof(struct tcp_pseudo)+sizeof(struct tcphdr), (unsigned char *)myip+(myip->ihl*4)+(sizeof(struct tcphdr)), tcpopt_len);
        memcpy((unsigned char *)tcp+sizeof(struct tcp_pseudo)+sizeof(struct tcphdr)+tcpopt_len, (unsigned char *)mytcp+(mytcp->th_off*4), tcpdatalen);


        return checksum(tcp,totaltcp_len);

}
