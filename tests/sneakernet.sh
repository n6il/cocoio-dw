#!/bin/bash -x

VHD=/home/pi/tmp/BUFFTEST/bufftest-work.dsk

# CCIO
for i in ifparse.c ifparse.h ccio.c w5100s.c w5100s.h cocoio.h ping.c socket.h socket.c echou.c ntpdate.c bufftest.c makefile; do
	os9 copy "${VHD},SRC/${i}" "${i}" -l -r
done

# SYS
mkdir -p $SYS
for i in interfaces; do
	os9 copy "${VHD},${i}" "SYS/${i}" -l -r
done

# CMDS
mkdir -p $CMDS
for i in ifparse ccio ping echou bufftest ntpdate; do
	os9 copy "${VHD},CMDS/${i}" "CMDS/${i}" -r
done
