#ifndef IFPARSE_H
#define IFPARSE_H 1

#include <stdint.h>
#include "w5100s.h"

int parseip();
char *ip2str();
char *mac2str();
int parsemac();
int prnifnfo();
struct w51info *ifparse();

#endif
