#!/bin/bash -x

VHD=/media/pi/MRFDEMO/NITROS9/EOUB6/CCIOdist.VHD

# CCIO
for i in ifparse.c ifparse.h ccio.c w5100s.c w5100s.h cocoio.h makefile; do
	os9 copy "${i}" "${VHD},CCIO/${i}" -l -r
done

# SYS
mkdir -p $SYS
for i in interfaces; do
	os9 copy "SYS/${i}" "${VHD},SYS/${i}" -l -r
done

# CMDS
# mkdir -p $CMDS
# for i in ifparse ccio; do
# 	os9 copy "${VHD},CMDS/${i}" "CMDS/${i}"
# done
