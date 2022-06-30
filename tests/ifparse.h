#ifndef IFPARSE_H
#define IFPARSE_H 1

#ifdef _CMOC_VERSION_
#include <coco.h>
#else
#include <stdint.h>
#endif
#include "w5100s.h"
#include "commondefs.h"

int parseip(ARGS2(uint8_t *d, char *s));
char *ip2str(ARGS1(uint8_t *ip));
char *mac2str(ARGS1(uint8_t *mac));
int parsemac(ARGS2(uint8_t *d, char *s));
int prnifnfo(ARGS1(struct w51info *iface));
struct w51info *ifparse();

#endif
