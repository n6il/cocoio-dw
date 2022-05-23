#!/bin/bash

VHD=/media/pi/MRFDEMO/NITROS9/EOUB6/CCIOdist.VHD

# CCIO
for i in ifparse.c ifparse.h ccio.c makefile; do
	os9 copy "${VHD},CCIO/${i}" "${i}" -l
done

# SYS
mkdir -p $SYS
for i in interfaces; do
	os9 copy "${VHD},SYS/${i}" "SYS/${i}" -l
done

# CMDS
mkdir -p $CMDS
for i in ifparse ccio; do
	os9 copy "${VHD},CMDS/${i}" "CMDS/${i}"
done
