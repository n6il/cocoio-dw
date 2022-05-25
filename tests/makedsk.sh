#!/bin/bash

set -x

DSK=cocoio-tools.dsk

rm -f "${DSK}"
os9 format -e "${DSK}"


#!/bin/bash -x
os9 makdir "${DSK},CMDS"
os9 makdir "${DSK},SRC"
os9 makdir "${DSK},SYS"

# CCIO
for i in ifparse.c ifparse.h ccio.c w5100s.c w5100s.h cocoio.h ping.c makefile; do
	os9 copy "${i}" "${DSK},SRC/${i}" -l -r
done

# SYS
mkdir -p $SYS
for i in interfaces; do
	os9 copy "SYS/${i}" "${DSK},SYS/${i}" -l -r
done

# CMDS
for i in ifparse ccio ping; do
 	os9 copy "CMDS/${i}" "${DSK},CMDS/${i}"
done

os9 copy README.md "${DSK},README.md"
