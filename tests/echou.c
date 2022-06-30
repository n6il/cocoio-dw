#ifdef _CMOC_VERSION_
#include <coco.h>
#include <cmoc.h>
#include "cmoclib/system.h"
#else
#include <stdio.h>
#include <memory.h>
#endif
#include "ifparse.h"
#include "socket.h"

int usage()
{
    fprintf(stderr, "Usage: echou <-u|-t> <ip>\n");
    exit(1);
}

#define BUFLEN 80
#ifdef _CMOC_VERSION_
int main()
#else
int main(argc, argv)
int argc;
char **argv;
#endif
{
    char *str, *ips, *buf2;
    char ip[4], buf[BUFLEN+1];
    int sock, rv, len, i, type;
    uint16_t port;
    struct udppktin *upi;

#ifdef _CMOC_VERSION_
    int argc;
    char **argv;
    getcmdln(&argc, &argv);
#endif
    if (argc < 3)
        usage();

    if (strcmp(argv[1], "-u") == 0)
        type = SOCK_DGRAM;
    else if (strcmp(argv[1], "-t") == 0)
        type = SOCK_STREAM;
    else
        usage();

    str = "Hello, Internet!\n";
    ips = argv[2];
    port=7; /* Echo */

    sock = socket(AF_INET, type, 0);
    if (sock < 0)
    {
        fprintf(stderr, "Socket Error: %x\n", sock);
        shutdown(sock);
        exit(sock);
    }
    fprintf(stderr, "Socket: %d\n", sock);

    printf("ip=(%s) port=(%u)\n", ips, port);
    parseip(ip, ips);
    printf("ip=(%s) port=(%u)\n", ip2str(ip), port);
    rv = connect(sock, ip, port);
    if (rv < 0)
    {
        fprintf(stderr, "Connect Error: %x\n", rv);
        shutdown(sock);
        exit(rv);
    }
    fprintf(stderr, "Connect: %d\n", rv);

    for(i=1; i<4; i++)
    {
        fprintf(stderr, "=== %d ===\n", i);
        memset(buf, 0, BUFLEN);
        sprintf(buf, "%d:%s", i, str);
        len = strlen(buf);
        rv = send(sock, buf, len, 0);
        if (rv != len)
        {
            fprintf(stderr, "Send Error: %x\n", rv);
            shutdown(sock);
            exit(rv);
        }
        fprintf(stderr, "Send: len=(%d) str=(%s)\n", rv, buf);
    
        if (type == SOCK_DGRAM)
            len += sizeof(struct udppktin);
        memset(buf, 0, BUFLEN);
        rv = recv(sock, buf, len, 0);
        if (rv != len)
        {
            fprintf(stderr, "Recv Error: %x\n", rv);
            shutdown(sock);
            exit(rv);
        }
        if (type == SOCK_DGRAM)
        {
            upi = (struct udppktin *)buf;
            buf2 = buf+sizeof(struct udppktin);
#ifdef DEBUG
            fprintf(stderr, "Recv: len=(%d) buf=(%04x) upi=(%04x) buf2=(%04x)\n"    ,
                len, buf, upi, buf2);
#endif
            fprintf(stderr, "Recv: ip=(%s) port=(%u)\n", ip2str(upi->dstip),
                upi->dstport);
            len = upi->len;
        } else {
            buf2 = buf;
        }
        fprintf(stderr, "Recv: len=(%d) str=(%s)\n", len, buf2);
    }
    shutdown(sock);
    return 0;
}

