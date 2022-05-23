OBJS = ccio.r ifparse.r w5100s.r
BIN = /DD/CMDS/ccio /DD/CMDS/ifparse

# ifparse test program
ifparse: ifparse.c
    dcc -dDRIVER -f=$@ $?    

# ccio program
ccoio.r: ccio.c

ifparse.r: ifparse.c

w5100s.r: w5100s.c

ccio: $(OBJS)
    dcc -f=$@ $?

clean:
    del $(OBJS) $(BIN)

all: ifparse ccio
