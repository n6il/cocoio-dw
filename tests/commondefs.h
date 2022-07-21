#ifndef COMMONDEFS_H
#define COMMONDEFS_H

#ifdef _CMOC_VERSION_
#define ARGS1(a) a
#define ARGS2(a,b) a, b
#define ARGS3(a,b,c) a, b, c
#define ARGS4(a,b,c,d) a, b, c, d

#define min(A,B) ((A)<(B) ? (A) : (B))
#define max(A,B) ((A)>(B) ? (A) : (B))
#define fprintf(F, args...) printf(args)
#define INT16_MAX 0x0fff
#else
#define ARGS1(a)
#define ARGS2(a,b)
#define ARGS3(a,b,c)
#define ARGS4(a,b,c,d)
#endif

#endif
