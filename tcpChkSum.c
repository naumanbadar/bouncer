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

u_short tcp_sum_calc(u_short len_tcp, u_char src_addr[], u_char dest_addr[], int padding, u_char buff[])
{
    u_short prot_tcp=6;
    u_short padd=0;
    u_short word16;
    u_long sum;

            // Find out if the length of data is even or odd number. If odd,
            // add a padding byte = 0 at the end of packet
            if ((padding&1)==1){
                    padd=1;
                    buff[len_tcp]=0;
            }

            //initialize sum to zero
            sum=0;
            int i;
            // make 16 bit words out of every two adjacent 8 bit words and
            // calculate the sum of all 16 vit words
            for (i=0;i<len_tcp+padd;i=i+2){
                    word16 =((buff[i]<<8)&0xFF00)+(buff[i+1]&0xFF);
                    sum = sum + (unsigned long)word16;
            }
            // add the TCP pseudo header which contains:
            // the IP source and destinationn addresses,
            for (i=0;i<4;i=i+2){
                    word16 =((src_addr[i]<<8)&0xFF00)+(src_addr[i+1]&0xFF);
                    sum=sum+word16;
            }
            for (i=0;i<4;i=i+2){
                    word16 =((dest_addr[i]<<8)&0xFF00)+(dest_addr[i+1]&0xFF);
                    sum=sum+word16;
            }
            // the protocol number and the length of the TCP packet
            sum = sum + prot_tcp + len_tcp;

            // keep only the last 16 bits of the 32 bit calculated sum and add the carries
            while (sum>>16)
                    sum = (sum & 0xFFFF)+(sum >> 16);

            // Take the one's complement of sum
            sum = ~sum;

    return ((unsigned short) sum);
}
