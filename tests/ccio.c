#include <stdio.h>
#include "ifparse.h"

#define CIO_MR (0xff68)
#define MR_IND 0x01
#define MR_AINC 0x02
#define MR_RST 0x80
#define CIO_AR (0xff69)
#define CIO_DR (0xff6b)


#define REGSET 1
#define REGCLR 0


/* rgstvfy - 
    W5100 Register Set & Verify

    Input:
        p - Address
        v - value
        s - either REGSET or REGCLR

    Output:
        if s==REGSET: 0 if value==v else 1 if other value
        if s==REGCLR: 0 if value&v is clear else 1 if set
*/

int rgstvfy(p, v, s)
char *p;
char v;
int s;
{
    int i;
    char r;
    *p |= v;
    for ( i=0; i<3; i++ ) {
        r = s ? (*p)!=v : (*p) & v;
#ifdef DEBUG
        printf("p=%04x v=%d s=%d *p=%d r=%d\n", p,v,s,*p,r);
#endif
        if (!r)
            break;
        tsleep(1);
    }
    return r;
}

/* 
   w5100_reset()
   Reset the W5100 Card
   Return: 0 - OK
*/
int w51reset()
{
    return rgstvfy(CIO_MR, MR_RST, REGCLR);
}

/* w5100_regdump()
   Dump a set of registers to the card
   Return: 0 - OK
*/
int w51regdmp(src, reg, cnt)
uint8_t *src;
uint16_t reg;
int cnt;
{
    *(uint16_t *)CIO_AR = reg;
    for ( ;cnt; cnt--,src++)
    {
#ifdef DEBUG
        printf("cnt=(%d) d=(%02x)\n", cnt, *src);
#endif
        *(uint8_t *)CIO_DR = *src;
    }
}

/* w5100_init()
   Setup the W5100 Card
   Return: 0 - OK
*/
int w51init(iface)
struct w51info *iface;
{
    if ( w51reset() )
        return 1;
    if ( rgstvfy(CIO_MR, MR_IND|MR_AINC, REGSET) )
        return 1;
    /* Write the interface IP config to the card */
    w51regdmp(iface, 0x0001, 18);
    return 0;
}


int main(argc, argv)
int argc;
char **argv;
{
    int r;
    struct w51info *iface;


    if (strcmp(argv[1], "-r") == 0)
    {
        fprintf(stderr, "w5100_reset\n");
        w51reset();
    }
    else if (strcmp(argv[1], "-i") == 0)
    {
        iface = ifparse();
        r = w51init(iface);
        if (r)
        {
            fprintf(stderr, "w5100_init failed\n");
            return 1;
        } else {
            prnifnfo(iface);
            fprintf(stderr, "w5100_init succeeded\n");
        }
    } else {
        fprintf(stderr, "Usage: -r (Reset) -i (Init)\n");
        return 1;
    }

    return 0;
}

