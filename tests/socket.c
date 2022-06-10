#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "w5100s.h"
#include "socket.h"

// #define DEBUG 1

static struct socket sockets[NUMSOCKS];
/* Bitfield for socks 3,2,1,0 */
static uint8_t avlsock = 0; 
static uint16_t srcport = 0x5000;

int socket(af, type, protocol)
int af;
int type;
int protocol;
{
    struct socket *sockp;
    struct w51sock *skregs;
    uint8_t *skrgofs0;
    uint8_t buf[8];
    int sock;
    uint8_t b;

    /* Checks */
    if (af < AF_INET || af >= AF_MAX)
        return EAFNOSUPPORT;
    if (type < SOCK_STREAM || type >= SOCK_MAX)
        return ESOCKTNOSUPPORT;
    if (protocol < PROT_IP || protocol >= PROT_MAX)
        return EPROTNOSUPPORT;

    /* Allocate a socket */
    for(b=0x08,sock=NUMSOCKS-1; b>0;)
    {
#ifdef DEBUG
        printf("1: avlsock=%x b=%x avlsock&b=%x sock=%d\n", avlsock, b, avlsock&b, sock);
#endif
        if ((avlsock & b) == 0 )
            break;
        b = b >> 1;
        sock--;
    }
#ifdef DEBUG
    printf("2: avlsock=%x b=%x avlsock&b=%x sock=%d\n", avlsock, b, avlsock&b,             sock);
#endif
    /* Check if any socket found */
    if (b==0)
        return ENOBUFS;

    avlsock |= b;
#ifdef DEBUG
    printf("3: avlsock=%x b=%x avlsock&b=%x sock=%d\n", avlsock, b, avlsock&b,             sock);
#endif
    sockp = sockets + sock;
    sockp->socknum = sock;
    /* Socket Register Address */
    sockp->skrgaddr = SKREGADR(sock);
    /* Socket TX  Buffer Address */
    sockp->sktbstrt = SKTXBSTRT(sock);
    /* Socket RX  Buffer Address */
    sockp->skrbstrt = SKRXBSTRT(sock);
    sockp->af = af;
    sockp->type = type;
    sockp->protocol = protocol;

#ifdef DEBUG
    printf("socknum=(%d)\n", sockp->socknum);
    printf("skrgaddr=(%04x)\n", sockp->skrgaddr);
    printf("sktbstrt=(%04x)\n", sockp->sktbstrt);
    printf("skrbstrt=(%04x)\n", sockp->skrbstrt);
    printf("af=(%d)\n", sockp->af);
    printf("type=(%d)\n", sockp->type);
    printf("protocol=(%d)\n", sockp->protocol);
#endif

    /* Set the Socket Type */
    switch(sockp->type)
    {
        case SOCK_STREAM:
            buf[0] = SK_MR_TCP;
            break;

        case SOCK_DGRAM:
            buf[0] = SK_MR_UDP;
            break;
    }
#ifdef DEBUG
    printf("set: sock=(%d) SK_MR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_MR), buf[0]);
#endif
    rgblkset(buf, SKPTRREG(sockp, SK_MR), 1);

    /* Open the socket on the card side */
    // buf[0] = SK_CR_OPEN;
    // rgblkset(buf, SKPTRREG(sockp, SK_CR), 1);

    return sock;
}

/* Get next port number */
uint16_t _getport()
{
    return srcport++;
}

int setdstip(sock, ip, port)
int sock;
uint8_t ip[4];
uint16_t port;
{
    struct socket *sockp;

    sockp = sockets + sock;

    /* IP */
#ifdef DEBUG
    printf("set: sock=(%d) SK_DIPR=(%04x) v=(%s)\n", sock, SKPTRREG(sockp, SK_DIPR0), ip2str(ip));
#endif
    rgblkset(ip, SKPTRREG(sockp, SK_DIPR0), 4);

    /* Port */
#ifdef DEBUG
    printf("set: sock=(%d) SK_DPORTR0=(%04x) v=(%04x)\n", sock, SKPTRREG(sockp, SK_DPORTR0), port);
#endif
    rgblkset(&port, SKPTRREG(sockp, SK_DPORTR0), 2);
}

int connect(sock, ip, port)
int sock;
uint8_t ip[4];
uint16_t port;
{
    struct socket *sockp;
    uint8_t buf[2];
    uint16_t sport;

    sockp = sockets + sock;


//    if (sockp->type == SOCK_DGRAM)
//    {
        /* UDP: Set a Source Port */
        sport = _getport();
#ifdef DEBUG
        printf("set: sock=(%d) SK_PORTR0=(%04x) v=(%04x)\n", sock, SKPTRREG(sockp, SK_PORTR0), sport);
#endif
        rgblkset(&sport, SKPTRREG(sockp, SK_PORTR0), 2);
//    }

    /* Open the socket on the card side */
    buf[0] = SK_CR_OPEN;
#ifdef DEBUG
    printf("set: sock=(%d) SK_CR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_CR), buf[0]);
#endif
    rgblkset(buf, SKPTRREG(sockp, SK_CR), 1);


    if (sockp->type == SOCK_STREAM)
    {
        setdstip(sock, ip, port);

        /* Connect */
        buf[0] = SK_CR_CONN;
        rgblkset(buf, SKPTRREG(sockp, SK_CR), 1);
#ifdef DEBUG
        printf("set: sock=(%d) SK_CR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_CR), buf[0]);
#endif
        while (buf[0] != 0)
        {
            rgblkget(buf, SKPTRREG(sockp, SK_CR), 1);
#ifdef DEBUG
            printf("get: sock=(%d) SK_CR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_CR), buf[0]);
#endif
        }
    }

    if (sockp->type == SOCK_DGRAM)
    {
        /* Check Socket Type */
        rgblkget(buf, SKPTRREG(sockp, SK_SR), 1);
#ifdef DEBUG
        printf("sock=%d SK_SR=%x\n", sock, buf[0]);
#endif
        if(buf[0] != SK_SR_UDP)
            return -1;
        setdstip(sock, ip, port);
    }

    if (sockp->type == SOCK_STREAM)
    {
        for(
            buf[0] = SK_SR_INIT, buf[1] = 0;
            buf[0] != SK_SR_ESTB && buf[1] < 10;
            buf[1]++ )
        {
            rgblkget(buf, SKPTRREG(sockp, SK_SR), 1);
#ifdef DEBUG
            printf("sock=%d SK_SR=%x\n", sock, buf[0]);
#endif
        }
        if (buf[1] == 10)
            return ETIMEDOUT;
    }
    return sock;
}

int recv(s, buf, len, flags)
int s;
uint8_t *buf;
int len;
int flags;
{
    struct socket *sockp;
    uint16_t rsize, rptr, roffset;
    uint8_t cbuf;

    sockp = sockets + s;

    /* Get number of bytes received */
    rsize = 0;
    while(rsize == 0)
    {
        rgblkget(&rsize, SKPTRREG(sockp, SK_RX_RSR0), 2);
#ifdef DEBUG
    printf("get: s=(%d) SK_RX_RSR=(%04x) rsize=(%d)\n", s,
        SKPTRREG(sockp, SK_RX_RSR0), rsize);
#endif
    }
    /* Either requested or available */
    len = min(len, rsize);

    /* Get current pointer in receive buffer */
    rgblkget(&rptr, SKPTRREG(sockp, SK_RX_RD0), 2);
    /* Offset into receive buffer */
    roffset = rptr & SKBUFMASK;

    /* The receieve buffer is circular. Check if we need to read from it in two
    parts or one */
    if(roffset + len > SKBUFMASK)
    {
        /* 1) Read to end of buffer */
        rsize = SKBUFSIZE - roffset;
        rgblkget(buf, sockp->skrbstrt + roffset, rsize);
        /* 2) Read remainder from beginning of buffer */
        rgblkget(buf + rsize, sockp->skrbstrt, len - rsize);
    } else {
        rgblkget(buf, sockp->skrbstrt + roffset, len);
    }

    /* Advance pointer */
    rgblkget(&rptr, SKPTRREG(sockp, SK_RX_RD0), 2);
    rptr += len;
    rgblkset(&rptr, SKPTRREG(sockp, SK_RX_RD0), 2);

    /* Tell card we received some data */
    cbuf = SK_CR_RECV;
    rgblkset(&cbuf, SKPTRREG(sockp, SK_CR), 1);
    
    return len;
}


int send(s, buf, len, flags)
int s;
uint8_t *buf;
int len;
int flags;
{
    struct socket *sockp;
    uint16_t wsize, wptr, woffset, c16;
    uint8_t cbuf;

    sockp = sockets + s;

    /* Either requested or available */
    len = min(len, SKBUFSIZE);

    /* Loop until TX Buffer has space */
    wsize = 0;
    while (wsize < len)
        rgblkget(&wsize, SKPTRREG(sockp, SK_TX_FSR0), 2);
#ifdef DEBUG
    printf("get: s=(%d) SK_TX_FSR=(%04x) wsize=(%d)\n", s, SKPTRREG(sockp, SK_TX_FSR0), wsize);
#endif

    /* Get current pointer in TX buffer */
    rgblkget(&wptr, SKPTRREG(sockp, SK_TX_WR0), 2);
#ifdef DEBUG
    printf("get: s=(%d) SK_TX_WR=(%04x) v=(%04x)\n", s, SKPTRREG(sockp, SK_TX_WR0), wptr);
#endif
    /* Offset into receive buffer */
    woffset = wptr & SKBUFMASK;

    /* The TX buffer is circular. Check if we need to write to it in two
     parts or one */
    if(woffset + len > SKBUFMASK)
    {
        /* 1) Write to end of buffer */
        wsize = SKBUFSIZE - woffset;
#ifdef DEBUG
        printf("write1: s=(%d) len=(%d) addr=(%04x)\n", s, wsize, sockp->sktbstrt + woffset);
#endif
        rgblkset(buf, sockp->sktbstrt + woffset, wsize);
        /* 2) Write remainder from beginning of buffer */
#ifdef DEBUG
        printf("write2: s=(%d) len=(%d) addr=(%04x)\n", s, len-wsize, sockp->sktbstrt);
#endif
        rgblkset(buf + wsize, sockp->sktbstrt, len - wsize);
    } else {
#ifdef DEBUG
        printf("write: s=(%d) len=(%d) addr=(%04x)\n", s, len, sockp->sktbstrt + woffset);
#endif
        rgblkset(buf, sockp->sktbstrt + woffset, len);
    }

    /* Advance pointer */
    rgblkget(&wptr, SKPTRREG(sockp, SK_TX_WR0), 2);
#ifdef DEBUG
    printf("get: s=(%d) SK_TX_WR=(%04x) v=(%04x)\n", s, SKPTRREG(sockp, SK_TX_WR0), wptr);
#endif
    wptr += len;
#ifdef DEBUG
    printf("set: s=(%d) SK_TX_WR=(%04x) v=(%04x)\n", s, SKPTRREG(sockp, SK_TX_WR0), wptr);
#endif
    rgblkset(&wptr, SKPTRREG(sockp, SK_TX_WR0), 2);

    /* Send command */
    cbuf = SK_CR_SEND;
#ifdef DEBUG
    printf("set: s=(%d) SK_CR=(%04x) v=(%04x)\n", s, SKPTRREG(sockp, SK_CR), cbuf);
#endif
    rgblkset(&cbuf, SKPTRREG(sockp, SK_CR), 1);

    /* Wait for command acceptance */
    while(cbuf != 0)
    {
        rgblkget(&cbuf, SKPTRREG(sockp, SK_CR), 1);
#ifdef DEBUG
        printf("get: s=(%d) SK_CR=(%04x) v=(%04x)\n", s, SKPTRREG(sockp, SK_CR), cbuf);
#endif
    }

    /* Wait for data to be sent or timeout */
    while( (cbuf & (SK_IR_TXOK|SK_IR_TOUT))== 0)
    {
        rgblkget(&cbuf, SKPTRREG(sockp, SK_IR), 1);
#ifdef DEBUG
        printf("get: s=(%d) SK_IR=(%04x) v=(%04x)\n", s, SKPTRREG(sockp, SK_IR), cbuf);
#endif
    }
    
    if (cbuf & SK_IR_TOUT)
    {
        cbuf = SK_IR_TXOK;
        rgblkset(&cbuf, SKPTRREG(sockp, SK_IR), 1);
#ifdef DEBUG
        printf("set: s=(%d) SK_IR=(%04x) v=(%04x)\n", s, SKPTRREG(sockp, SK_IR), cbuf);
#endif
        return ETIMEDOUT;
    }
    cbuf = SK_IR_TXOK;
    rgblkset(&cbuf, SKPTRREG(sockp, SK_IR), 1);
#ifdef DEBUG
    printf("set: s=(%d) SK_IR=(%04x) v=(%04x)\n", s, SKPTRREG(sockp, SK_IR), cbuf);
#endif
    return len;
}

int shutdown(sock)
int sock;
{
    struct socket *sockp;
    uint8_t buf[2];

    sockp = sockets + sock;

    if (sockp->type == SOCK_STREAM)
    {
        /* TCP Active Close: Send FIN packet to peer */
        /* Send disconnect command */
        buf[0] = SK_CR_DISC;
        rgblkset(buf, SKPTRREG(sockp, SK_CR), 1);
#ifdef DEBUG
        printf("set: s=(%d) SK_CR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_CR), buf[0]);
#endif
    
        /* Wait for command acceptance */
        while(buf[0] != 0)
            rgblkget(buf, SKPTRREG(sockp, SK_CR), 1);
#ifdef DEBUG
        printf("get: s=(%d) SK_CR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_CR), buf[0]);
#endif
    
        /* Wait until FIN packet is received */
        while( (buf[0] & (SK_IR_DISC|SK_IR_TOUT))== 0)
            rgblkget(buf, SKPTRREG(sockp, SK_IR), 1);
#ifdef DEBUG
        printf("get: s=(%d) SK_IR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_IR), buf[0]);
#endif
        if ( buf[0] & SK_IR_DISC )
        {
            buf[0] = SK_IR_DISC;
            rgblkset(buf, SKPTRREG(sockp, SK_IR), 1);
#ifdef DEBUG
            printf("set: s=(%d) SK_IR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_IR), buf[0]);
#endif
        }
        else if ( buf[0] & SK_IR_TOUT )
        {
            buf[0] = SK_IR_TOUT;
            rgblkset(buf, SKPTRREG(sockp, SK_IR), 1);
#ifdef DEBUG
            printf("set: s=(%d) SK_IR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_IR), buf[0]);
#endif
        }
        
    } /* TCP */
    else if (sockp->type == SOCK_DGRAM)
    {
        /* UDP */
        /* Send Close command */
        buf[0] = SK_CR_CLOS;
        rgblkset(buf, SKPTRREG(sockp, SK_CR), 1);
#ifdef DEBUG
        printf("set: s=(%d) SK_CR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_CR), buf[0]);
#endif
    
        /* Wait for command acceptance */
        while(buf[0] != 0)
        {
            rgblkget(buf, SKPTRREG(sockp, SK_CR), 1);
#ifdef DEBUG
            printf("get: s=(%d) SK_CR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_CR), buf[0]);
#endif
        }
    }

    /* Wait until socket is closed */
    buf[0] = 1;
    while (buf[0] != SK_SR_CLOS)
    {
        rgblkget(buf, SKPTRREG(sockp, SK_SR), 1);
#ifdef DEBUG
        printf("get: s=(%d) SK_SR=(%04x) v=(%02x)\n", sock, SKPTRREG(sockp, SK_SR), buf[0]);
#endif
    }
}
