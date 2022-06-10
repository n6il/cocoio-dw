#include <stdio.h>
#include <stdint.h>
#include <utime.h>
#include <time.h>
#include <memory.h>
#include "socket.h"

// #define DEBUG 1

typedef unsigned long uint32_t;

struct sntp {
    uint8_t livnmd;
    uint8_t stratum;
    int8_t poll;
    int8_t prec;
    int32_t rtdelay;
    int32_t rtdisp;
    uint8_t refid[4];
    uint32_t refti;
    uint32_t reftf;
    uint32_t orgti;
    uint32_t orgtf;
    uint32_t rxti;
    uint32_t rxtf;
    uint32_t txti;
    uint32_t txtf;
};

/* SNTP Defines for LI, VN, MD byte */
#define SNTP_LI_NOWARN  0x00
#define SNTP_LI_LEAP    0x40
#define SNTP_LI_RLEAP   0x80
#define SNTP_LI_ALARM   0xC0
#define SNTP_VERSION(v) ((v&0x07)<<3)
#define SNTP_MD_RESERVD 0x00
#define SNTP_MD_SYMACT  0x01
#define SNTP_MD_SYMPAS  0x02
#define SNTP_MD_CLIENT  0x03
#define SNTP_MD_SERVER  0x04
#define SNTP_MD_BRCAST  0x05
#define SNTP_MD_RESERV2 0x06
#define SNTP_MD_RESERV3 0x07

/* Socket Handle */
int sock;

/*
UDP Packet Buffer for w5100s
    bytes 0-7:  struct udppktin
    bytes 8-55: struct sntp
*/
uint8_t buf[sizeof(struct udppktin)+sizeof(struct sntp)];


/* Error Exit - No socket shutdown */
int errxit(msg, val)
{
    printf(msg, val);
    exit(1);
}


/* Error Exit With Socket Shutdown */
int errxit2(msg, val)
{
    printf(msg, val);
    shutdown(sock);
    exit(1);
}

/* Program Usage */
int usage()
{
    printf("Usage: ntpdate [-hs] [-t TZ] <ip>\n\n");
    printf("        -h = help message\n");
    printf("        -s = Set Time\n");
    printf("        -t TZ = Time Zone Offset from UTC\n");
    printf("                TZ = Int: 0,1,2,... Neg Int: -8,-7,...\n\n");
    printf("   Ex: ntpdate -s -t -7 128.138.141.172\n");
    exit(1);
}

int main(argc, argv)
int argc;
char **argv;
{

    char *ips = "172.16.1.11";
    uint8_t ip[4], *p;
    uint16_t port;
    int rv, len, tz, set;
    struct udppktin *upi;
    struct sntp *sntpmsg;
    uint32_t t;
    struct tm *tm;
    struct sgtbuf sgtb;


    set = 0;
    tz = 0;
    port = 123; /* NTP */
    upi = buf;  /* struct udppktin ptr */
    sntpmsg = buf+sizeof(struct udppktin); /* struct sntp ptr */


    if (argc < 2)
        usage();
    argv++;
    while(**argv == '-')
    {
        if(strcmp(*argv, "-h") == 0)
            usage();
        else if(strcmp(*argv, "-s") == 0)
            set = 1;
        else if(strcmp(*argv, "-t") == 0)
            tz = atoi(*++argv);
        else
            usage();
        argv++;
    }
    ips = *argv;
#ifdef DEBUG
    printf("set=(%d) tz=(%d) ips=(%s)\n", set, tz, ips);
#endif

    /* Set up SNTP Request Packet */
    /* Zero everything out */
    memset(sntpmsg, 0, sizeof(struct sntp));
    /* Set Unsync Alarm, SNTP Version, Client Mode */
    sntpmsg->livnmd |= (SNTP_LI_ALARM | SNTP_VERSION(3) | SNTP_MD_CLIENT);

    /* Get a UDP Socket */
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        errxit("ERROR: sock=%d\n", sock);
#ifdef DEBUG
    printf("sock=(%d)\n", sock);
#endif

    printf("Connect ip=(%s) port=(%d)\n", ips, port);
    parseip(ip, ips);
    rv = connect(sock, ip, port);
    if (rv<0)
        errxit("ERROR: connect=%d\n", rv);

#ifdef DEBUG
    printf("send sock=(%d) len=(%d)\n", sock, sizeof(struct sntp));
#endif

    /* Send SNTP Request */
    rv = send(sock, sntpmsg, sizeof(struct sntp));
    if (rv != sizeof(struct sntp))
        errxit2("ERROR: send=%d\n", rv);

    /* Receive SNTP Reply from Server */
    /* w5100s: rx packet len header+data */
    len = sizeof(struct udppktin) + sizeof(struct sntp);
#ifdef DEBUG
    printf("recv sock=(%d) len=(%d)\n", sock, len);
#endif
    rv = recv(sock, buf, len);
    if (rv != len)
        errxit2("ERROR: recv=%d\n", rv);

#ifdef DEBUG
    p = &sntpmsg->txti;
    printf("txti=(%02x%02x%02x%02x)\n", p[0], p[1], p[2], p[3]);
    p = &sntpmsg->txtf;
    printf("txtf=(%02x%02x%02x%02x)\n", p[0], p[1], p[2], p[3]);
#endif

    /* Shut Down Socket */
    shutdown(sock);

    /* Convert from epoch-1900 to epoch-1970 */
    t = sntpmsg->txti - 2208988800;
    /* Time Zone Correction if Required */
    if (tz ==0)
    {
        p = ctime(&t);
        /* get rid of ctime() annoying \n */
        p[strlen(p)-1] = 0;
        printf("%s UTC\n", p);
    } else {
        t += (tz*3600);
        p = ctime(&t);
        /* get rid of ctime() annoying \n */
        p[strlen(p)-1] = 0;
        printf("%s %c%d\n", p, tz<0 ? 0 : '+', tz);
    }

    /* Set The Time */
    if (set)
    {
        printf("Setting time.\n");
        /* Convert from Unix epoch-1970 to OS-9 sgtbuf */
        u2otime(&sgtb, localtime(&t));
        /* Add 1 to the month - os9 is 1-based */
        sgtb.t_month++;
        /* Set the time */
        setime(&sgtb);
    }
    
    return 0;
}
    
