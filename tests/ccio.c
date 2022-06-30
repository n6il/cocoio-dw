#ifdef _CMOC_VERSION_
#include <coco.h>
#include <cmoc.h>
#include "cmoclib/system.h"
#else
#include <stdio.h>
#endif
#include "ifparse.h"
#include "w5100s.h"


#ifdef _CMOC_VERSION_
int main()
#else
int main(argc, argv)
int argc;
char **argv;
#endif
{
    int r;
    struct w51info *iface;
    struct w51info iface2;

#ifdef _CMOC_VERSION_
    int argc;
    char **argv;
    getcmdln(&argc, &argv);
#endif
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
            printf("w5100_init failed\n");
            return 1;
        }
        iface2.phyaddr = iface->phyaddr;
        memcpy(iface2.iface, iface->iface, 8);
        rgblkget((uint8_t *)&iface2, GAR0, W51INFO_LEN);
        prnifnfo(&iface2);
        if ( memcmp(iface, &iface2, W51INFO_LEN) != 0 )
        {
            printf("w5100_init failed\n");
        } else {
            printf("w5100_init succeeded\n");
        }
    } else {
        printf("Usage: -r (Reset) -i (Init)\n");
        return 1;
    }

    return 0;
}

