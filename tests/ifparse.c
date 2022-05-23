#include <stdio.h>
#include <stdint.h>
#include "ifparse.h"

/*
#define DEBUG 1
#define DRIVER 1
*/

/* String Conversion Buffer */
static char sbuf[17];

/*
parseip - Parse IP Address string s into 4-byte array d
Return 1 if all parsed
*/
int parseip(d, s)
uint8_t *d;
char *s;
{
    int i;
    uint8_t j;
    char *s2, *s3;
    for( i=0, s2=s; i<4; i++, s2=NULL )
    {
        s3 = strtok(s2, ".");
        if (!s3)
            break;
        j = atoi(s3);
#ifdef DEBUG
        printf("s3=(%s) j=(%u)\n", s3, j);
#endif
        d[i] = j;
    }
    return (i==4);
}


/*
ip2str - convert 4-byte IP array to string
Return: pointer to string
*/
char *ip2str(ip)
uint8_t *ip;
{
    sprintf(sbuf, "%u.%u.%u.%u",
        ip[0],
        ip[1],
        ip[2],
        ip[3]);
    return sbuf;
}

/*
mac2str - convert 6-byte MAC array to string
Return: pointer to string
*/
char *mac2str(mac)
uint8_t *mac;
{
    sprintf(sbuf, "%02x:%02x:%02x:%02x:%02x:%02x",
        mac[0],
        mac[1],
        mac[2],
        mac[3],
        mac[4],
        mac[5] );
    return sbuf;
}

/*
parsemac - Parse MAC Address string s into 6-byte array d
Return 1 if all parsed
*/
int parsemac(d, s)
uint8_t *d;
char *s;
{
    int i;
    unsigned j;
    char *s2, *s3;
    for( i=0, s2=s; i<6; i++, s2=NULL )
    {
        s3 = strtok(s2, ":");
        if (!s3)
            break;
        sscanf(s3, "%02x", &j);
        d[i] = j;
    }
    return (i==6);
}

/* 
ifparse - Read and parse interfaces file
Return: pointer to w51info struct, NULL on error
*/
struct w51info *ifparse()
{
    FILE *f;
    char buf[81], *c, *tok, *data;
    int i;
    struct w51info *r;
    i=0;
    r=malloc(sizeof(struct w51info));;
    f=fopen("/DD/SYS/interfaces", "r");
    if (f==NULL)
    {
        printf("cant open file\n");
        exit(1);
    }
    while(fgets(buf,80,f))
    {
        c = index(buf, '\n');
        if (c)
            *c=0;
#ifdef DEBUG
        printf("buf=%04x(%s)\n",buf,buf);
#endif
        tok = strtok(buf, " ");
        if (tok==NULL)
            continue;
        data = strtok(NULL, " ");
        if (data==NULL)
            continue;

#ifdef DEBUG
        printf("3 buf=%04x(%s) c=%04x(%s)\n", buf, buf,c,c);
        printf("3 tok=%04x(%s) data=%04x(%s)\n", tok,tok,data, data);
#endif
  
       if( strcmp(tok, "iface") == 0 )
       {
           strcpy(r->iface, data);
           i++;
       }
       else if( strcmp(tok, "address") == 0 )
       {
           parseip(r->address, data);
           i++;
       }
       else if( strcmp(tok, "gateway") == 0 )
       {
           parseip(r->gateway, data);
           i++;
       }
       else if( strcmp(tok, "netmask") == 0 )
       {
           parseip(r->netmask, data);
           i++;
       }
       else if( strcmp(tok, "macaddr") == 0 )
       {
           parsemac(r->macaddr, data);
           i++;
       }
       else if( strcmp(tok, "phyaddr") == 0 )
       {
           sscanf(data, "$%04x", &r->phyaddr);
           i++;
       }
 
    }
    fclose(f);
    if (i != 6)
    {
        free(r);
        r = NULL;
    }
    return r;
}

int prnifnfo(iface)
struct w51info *iface;
{
    printf("iface=(%s)\n", iface->iface);
    printf("address=(%s)\n", ip2str(iface->address));
    printf("gateway=(%s)\n", ip2str(iface->gateway));
    printf("netmask=(%s)\n", ip2str(iface->netmask));
    printf("macaddr=(%s)\n", mac2str(iface->macaddr));
}

#ifdef DRIVER
int main(argc, argv)
int argc;
uint8_t *argv;
{
    struct w51info *iface;
    iface = ifparse();
    if (!iface)
    {
        printf("Unable to parse interfaces\n");
        exit(1);
    }
    prnifnfo(iface);
}
#endif