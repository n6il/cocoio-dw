#include <stdio.h>
#include "ifparse.h"
#include "w5100s.h"
#include "cocoio.h"

#define REGSET 1
#define REGCLR 0

#ifdef SLOWPATCH
#asm

goslo
	sta $ffd8 slow down CPU (SAM doesn't care what we write)
	rts

noslo
	sta $ffd9 speed CPU back up
	pshs a
	lda #'Z special GIME-X "turbo" value
	sta $ffd9
	puls a,pc

#endasm
#endif

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

#ifdef SLOWPATCH
    goslo();
#endif

    *p |= v;

    for ( i=0; i<3; i++ ) {
        r = s ? (*p)!=v : (*p) & v;
#ifdef DEBUG
        printf("p=%04x v=%d s=%d *p=%d r=%d\n", p,v,s,*p,r);
#endif
        if (!r)
            break;

#ifdef SLOWPATCH
        noslo();
#endif
        tsleep(1);
#ifdef SLOWPATCH
        goslo();
#endif
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
    return rgstvfy(CIO0CMND, MR_RST, REGCLR);
}

/* w5100_regblkset()
   Set a block of registers to the card
   Return: 0 - OK
*/
int rgblkset(src, reg, cnt)
uint8_t *src;
uint16_t reg;
int cnt;
{

    // *(uint16_t *)CIO0ADDR = reg;
    uint8_t *c;
    c = &reg;

#ifdef SLOWPATCH
    goslo();
#endif

    *(uint8_t *)(CIO0ADDR) = *c++;
    *(uint8_t *)(CIO0ADDR+1) = *c;
    for ( ;cnt; cnt--,src++)
    {
#ifdef DEBUG
        printf("cnt=(%d) d=(%02x)\n", cnt, *src);
#endif
        *(uint8_t *)CIO0DATA = *src;

    }
#ifdef SLOWPATCH
    noslo();
#endif
}

/* w5100_regblkget()
   Get a block of registers from the card
   Return: 0 - OK
*/
int rgblkget(dst, reg, cnt)
uint8_t *dst;
uint16_t reg;
int cnt;
{
    // *(uint16_t *)CIO0ADDR = reg;
    uint8_t *c;
    c = &reg;

#ifdef SLOWPATCH
    goslo();
#endif
    *(uint8_t *)(CIO0ADDR) = *c++;
    *(uint8_t *)(CIO0ADDR+1) = *c;
    for ( ;cnt; cnt--,dst++)
    {
        *dst = *(uint8_t *)CIO0DATA;
#ifdef DEBUG
        printf("cnt=(%d) d=(%02x)\n", cnt, *dst);
#endif
    }
#ifdef SLOWPATCH
    noslo();
#endif
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
    if ( rgstvfy(CIO0CMND, MR_IND|MR_AINC, REGSET) )
        return 1;
    /* Write the interface IP config to the card */
    rgblkset(iface, GAR0, W51INFO_LEN);
    return 0;
}

