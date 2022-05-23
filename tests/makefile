OBJS = ccio.r ifparse.r
BIN = /DD/CMDS/ccio /DD/CMDS/ifparse

# ifparse test program
ifparse: ifparse.c
    dcc -dDRIVER -f=$@ $?    

# ccio program
ccoio.r: ccio.c

ifparse.r: ifparse.c

ccio: $(OBJS)
    dcc -f=$@ $?

clean:
    del $(OBJS) $(BIN)

all: ifparse ccio
