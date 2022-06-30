#ifndef SOCKET_H
#define SOCKET_H

#ifdef _CMOC_VERSION_
#include <coco.h>
#else
#include <stdint.h>
#endif
#include "commondefs.h"

#define NUMSOCKS 4

struct socket {
    uint8_t socknum;
    uint8_t *skrgaddr;
    uint8_t *skrbstrt;
    uint8_t *sktbstrt;
    int af;
    int type;
    int protocol;
};

struct udppktin {
    uint8_t dstip[4];
    uint16_t dstport;
    uint16_t len;
};

#define AF_INET 1
#define AF_MAX 2

#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOCK_MAX 3

#define PROT_IP 0
#define PROT_MAX 1

/* ERRORS - From OSK */
#define EPROTNOSUPPORT  -0x708
#define ESOCKTNOSUPPORT -0x709
#define EAFNOSUPPORT    -0x70c
#define ENOBUFS         -0x714
#define ETIMEDOUT       -0x719

int socket(ARGS3(int af, int type, int protocol));
int bind();
int listen();
int accept();
int connect(ARGS3(int sock, uint8_t ip[4], uint16_t port));
int recv(ARGS4(int s, uint8_t *buf, int len, int flags));
int send(ARGS4(int s, uint8_t *buf, int len, int flags));
int select();
int shutdown(ARGS1(int sock));

#endif
