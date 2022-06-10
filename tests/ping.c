#include <stdio.h>
#include "ifparse.h"
#include "w5100s.h"

#define NPINGS 5
#define MAXSEQ NPINGS+1


int main(argc, argv)
int argc;
char **argv;
{
    uint8_t buf[2];
    struct sklsip sklsipd;
    int t, pingseq;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ping <ip>\n");
        exit(1);
    }

    /* Set up for W5100 SOCKET-less IP */
    parseip(sklsipd.peerip, argv[1]);
    sklsipd.retranst = 0x03e8;
    sklsipd.retransc = 0x05;
    sklsipd.sklipmsk = SLIMR_P|SLIMR_T;
    sklsipd.pingseqn = 1;
    sklsipd.pingid = getpid();
    /* Send the register block to the card. */
    rgblkset(&sklsipd, SLRTR0, sizeof(struct sklsip));

    printf("ping ip=(%s)\n", ip2str(sklsipd.peerip));

    /* Ping Loop */
    for(pingseq=1; pingseq<MAXSEQ; pingseq++)
    {
        /* Set Ping Sequence Num */
        rgblkset(&pingseq, PINGSEQR0, 2);
    
        /* Send the ping command */
        buf[0] = SLCR_P;
        rgblkset(buf, SLCR, 1);
    
        /*
            Check SLCR for ping command acceptance

            The SLCR register will keep whatever command you wrote to it
            and will be cleared fairly quickly.  We call this "command
            acceptance" but the manual doesn't use that terminology.  We
            did find that SLCR was cleared but there wasn't a ping response
            or timeout in SLIR yet.
        */
        for(t=0, buf[0]=0; t<75; t++)
        {
            rgblkget(buf, SLCR, 1);
            if (buf[0] == 0)
                break;
        }

        /*
            Check SLIR for ping command results

            The W5100S manual does not actually mention this step.
            Depending on your network or even if you are trying to 
            ping something over the Internet, it may take a while
            to get the response back.  The SLIR register will simply
            return 0 until either the ICMP Echo Reply comes back or
            nothing replies and the W5100S Chip sets the timeout flag.
            So we loop here until SLIR has a non-zero value and then
            check the result outside of the loop.
        */
        for(buf[0]=0; t<INT16_MAX; t++)
        {
            rgblkget(buf, SLIR, 1);
            if (buf[0])
                break;
        }

        if (buf[0] & SLIR_T)
        {
            printf("%s: icmp_seq=%d: t=%d: Ping timeout\n",
                ip2str(sklsipd.peerip),
                pingseq,
                t);
        }
        else if (buf[0] & SLIR_P)
        {
            printf("%s: icmp_seq=%d: t=%d: Ping successful\n",
                ip2str(sklsipd.peerip),
                pingseq,
                t);
        }
        else
        {
            printf("%s: icmp_seq=%d: t=%d: Unkown Ping Status: 0x%02x\n",
                ip2str(sklsipd.peerip),
                pingseq,
                t,
                buf[0]);
        }

        /* Clear SLIR Flags by setting them */
        buf[0] = SLIR_T|SLIR_P;
        rgblkset(buf, SLIR, 1);

        tsleep(60);
    }

    /* Ping Done - Clear SLIMR Flags */
    buf[0] = 0;
    rgblkset(buf, SLIMR, 1);

    return 0;
}

