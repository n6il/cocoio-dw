LOBJS = ifparse.r w5100s.r
SOBJS = socket.r
COBJ = ccio.r
POBJ = ping.r
EOBJ = echou.r
BINS = /DD/CMDS/ccio /DD/CMDS/ifparse /DD/CMDS/ping /DD/cmds/echou /dd/cmds/bufftest
BOBJ = bufftest.r
BLIBS = w5100s.r
NOBJ = ntpdate.r
NLIBS = socket.r w5100s.r ifparse.r
CC = dcc
CFLAGS = 
# CFLAGS = -dDEBUG
# CFLAGS = -dSLOWPATCH

all: ifparse ccio ping echou bufftest ntpdate

w5100s.r: w5100s.c
ifparse.r: ifparse.c
ccoio.r: ccio.c
ping.r: ping.c
socket.r: socket.c
echou.r: echou.c
bufftest.r: bufftest.c
ntpdate.r: ntpdate.c


# ifparse test program
ifparse: ifparse.c
    $(CC) -dDRIVER -f=$@ $?

# ccio program
ccio: $(COBJ) $(LOBJS)
    $(CC) -f=$@ $(COBJ) $(LOBJS)

# ping program
ping: $(POBJ) $(LOBJS)
    $(CC) -f=$@ $(POBJ) $(LOBJS)

# UDP Echo program
echou: $(EOBJ) $(SOBJS) $(LOBJS)
    $(CC) -f=$@ $(EOBJ) $(SOBJS) $(LOBJS)

bufftest: $(BOBJ) $(BLIBS)
    $(CC) -f=$@ $(BOBJ) $(BLIBS)

ntpdate: $(NOBJ) $(NLIBS)
    $(CC) -f=$@ $(NOBJ) $(NLIBS)

clean:
    del $(LOBJS) $(SOBJS) $(EOBJ) $(POBJ) $(COBJ) $(BOBJ) $(BINS)

copy:
    cp -vf *.c *.h makefile /x1/src
    cp -vf $(BINS) /x1/cmds

