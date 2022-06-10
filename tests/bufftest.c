#include <stdio.h>
#include <stdint.h>
#include <memory.h>
#include "w5100s.h"

#define SIZE 16384
#define ADDR 0x4000

uint8_t buf[SIZE];

int check(pat)
uint8_t pat;
{
    uint16_t i;
    uint8_t *c;
    uint16_t e;

    printf("Set %0x\n", pat);
    memset(buf, pat, SIZE);
    rgblkset(buf, ADDR, SIZE);
    memset(buf, 0x0, SIZE);
    printf("Get %0x\n", pat);
    rgblkget(buf, ADDR, SIZE);
    for(i=0, c=buf, e=0; i<SIZE; i++, c++)
        if(*c != pat) printf("%d: %04x: %02x != %02x\n",e++,i+ADDR,*c,pat);
    return e;
}

int main(argc, argv)
int argc;
char **argv;
{
    uint8_t pat;
    uint16_t e,t;

    e=0; t=0;
    pat = 0x00;
    printf("=== Clear 1: pat=%02x ===\n", pat);
    e = check(pat);
    t += e;
    printf("e=%u t=%u\n", e, t);
    
    pat = 0x00;
    printf("=== Clear 2: pat=%02x ===\n", pat);
    e = check(pat);
    t += e;
    printf("e=%u t=%u\n", e, t);

    pat = 0x00;
    printf("=== Clear 3: pat=%02x ===\n", pat);
    e = check(pat);
    t += e;
    printf("e=%u t=%u\n", e, t);

    pat = 0x55;
    printf("=== Set 1: pat=%02x ===\n", pat);
    e = check(pat);
    t += e;
    printf("e=%u t=%u\n", e, t);

    pat = 0xAA;
    printf("=== Set 2: pat=%02x ===\n", pat);
    e = check(pat);
    t += e;
    printf("e=%u t=%u\n", e, t);

    return 0;
}


