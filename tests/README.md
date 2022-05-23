This directory contains W5100 Test Code.  It is designed to be built 
under NitrOS-9 using the DCC compiler suite.

To build both programs:

    make all


## `ifparse` -- Test Program to parse `interfaces` file
Create a `/DD/SYS/interfaces` file.  There is an example here in the `SYS` directory.

Build a test program with

    make ifparse

Then run

    ifparse

This should show your interfaces file:

    iface=(eth0)
    address=(172.16.1.8)
    gateway=(172.16.1.1)
    netmask=(255.255.255.0)
    macaddr=(5c:26:0a:c0:ff:ee)
    phyaddr=(ff68)

To build this as a library (without the driver program main):

    dcc -r ifparse.c

## `ccio` CoCoIO Initialization Program

Build:

    make ccio

Reset Card:

    ccio -r

Initialize Card from `/DD/SYS/interfaces`:

    ccio -i
