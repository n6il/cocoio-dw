#include <stdio.h>

#define DEBUG 1

#define CIO_MR (0xff68)
#define MR_IND 0x01
#define MR_AINC 0x02
#define MR_RST 0x80
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

/* w5100_init()
   Setup the W5100 Card
   Return: 0 - OK
*/
int w51init()
{
    if ( w51reset() )
        return 1;
    if ( rgstvfy(CIO_MR, MR_IND|MR_AINC, REGSET) )
        return 1;
    return 0;
}

struct w51info {
    char iface[8];
    char address[4];
    char gateway[4];
    char netmask[4];
    char macaddr[6];
    char *phyaddr;
};
struct w51info myw5100;


int ifparse()
{
    FILE *f;
    char buf[81],tok[9], data[73];
    if ( f = fopen("/DD/SYS/interfaces", "r") == NULL )
    {
        printf("w5100_ifparse: can't open interfaces file\n");
        exit(1);
    }
    while (!feof(f))
    {
        fgets(buf, 80, f);
        sscanf(buf, "%s %s", tok, data);
        printf("tok=(%s) data=(%s)\n", tok, data);
    }
    fclose(f);
}


int main(argc, argv)
int argc;
char **argv;
{
    int r;

    printf("Hello, world!\n");

    ifparse();
    r = w51init();
    if (r)
    {
        fprintf(stderr, "w5100_init failed\n");
        return 1;
    } else {
        fprintf(stderr, "w5100_init succeeded\n");
    }

    return 0;
}

