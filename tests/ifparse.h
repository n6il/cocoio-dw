#ifndef IFPARSE_H
#define IFPARSE_H 1

#include <stdint.h>

struct w51info {
    uint8_t gateway[4];
    uint8_t netmask[4];
    uint8_t macaddr[6];
    uint8_t address[4];
    uint8_t *phyaddr;
    uint8_t iface[8];
};

int parseip();
char *ip2str();
char *mac2str();
int parsemac();
int prnifnfo();
struct w51info *ifparse();

#endif
