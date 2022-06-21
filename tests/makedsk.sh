#!/bin/bash

set -x

DSK=cocoio-tools.dsk
# DSK=cocoio-tools-slow.dsk

rm -f "${DSK}"
os9 format -e "${DSK}"


#!/bin/bash -x
os9 makdir "${DSK},CMDS"
os9 makdir "${DSK},SRC"
os9 makdir "${DSK},SYS"

# CCIO
for i in bufftest.c  ccio.c  echou.c  ifparse.c  ntpdate.c  ping.c  socket.c  w5100s.c cocoio.h  ifparse.h  socket.h  w5100s.h makefile; do
	os9 copy "${i}" "${DSK},SRC/${i}" -l -r
done

# SYS
for i in interfaces; do
	os9 copy "SYS/${i}" "${DSK},SYS/${i}" -l -r
done

# CMDS
for i in ifparse ccio ping bufftest echou ntpdate; do
 	os9 copy "CMDS/${i}" "${DSK},CMDS/${i}"
	os9 attr "${DSK},CMDS/${i}" -e -pe
done

os9 copy README.md "${DSK},README.md" -l -r

echo "cocoio-tools $(date +%Y%m%d-%H%M%S)" >/tmp/version.txt
os9 copy /tmp/version.txt "${DSK},version.txt" -l -r
