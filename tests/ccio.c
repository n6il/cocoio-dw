#include <stdio.h>
#include "ifparse.h"
#include "w5100s.h"

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

