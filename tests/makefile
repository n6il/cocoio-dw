LOBJS = ifparse.r w5100s.r
COBJ = ccio.r
POBJ = ping.r
BIN = /DD/CMDS/ccio /DD/CMDS/ifparse /DD/CMDS/ping

all: ifparse ccio ping

w5100s.r: w5100s.c
ifparse.r: ifparse.c
ccoio.r: ccio.c
ping.r: ping.c

# ifparse test program
ifparse: ifparse.c
    dcc -dDRIVER -f=$@ $?

# ccio program
ccio: $(COBJ) $(LOBJS)
    dcc -f=$@ $(COBJ) $(LOBJS)

# ping program
ping: $(POBJ) $(LOBJS)
    dcc -f=$@ $(POBJ) $(LOBJS)

clean:
    del $(LOBJS) $(POBJ) $(COBJ) $(BIN)

