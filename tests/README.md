Create a `/DD/SYS/interfaces` file. Build a test program with

    dcc -dDRIVER ifparse.c

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
