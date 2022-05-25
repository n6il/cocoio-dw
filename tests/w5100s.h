#ifndef W5100S_H
#define W5100S_H

/*********************************************************************
;* Title: W5100SEQU.asm
;*********************************************************************
;* Author: R. Allen Murphey
;*
;* License: Contributed 2021 by R. Allen Murphey to CoCoIO Development
;*
;* Description: WIZnet W5100S driver equates
;*
;* Documentation: https://www.wiznet.io/product-item/w5100s/
;*
;* Include Files: none
;*
;* Assembler: lwasm 1.4.2
;*
;* Revision History:
;* Rev #     Date      Who     Comments
;* -----  -----------  ------  ---------------------------------------
;* 01     2022/05/23   MRF     Convert from ASM to C
;* 00     2021         RAM     Initial equates from W5100S Data Sheet
;*********************************************************************/

/*
                              ; W5100S REGISTER / MEMORY MAP
                              ; 0x0000 - 0x002F Common Registers W5100 compatible
                              ; 0x0030 - 0x0088 Common Registers New W5100S
                              ; 0x0089 - 0x03FF -- Reserved --
                              ; 0x0400 - 0x04FF Socket 0 Registers
                              ; 0x0500 - 0x05FF Socket 1 Registers
                              ; 0x0600 - 0x06FF Socket 2 Registers
                              ; 0x0700 - 0x07FF Socket 3 Registers
                              ; 0x0800 - 0x3FFF -- Reserved --
                              ; 0x4000 - 0x5FFF TX Memory - default 2KB per socket
                              ; 0x6000 - 0x7FFF RX Memory - default 2KB per socket
*/

                                /* COMMON REGISTERS 0x0000-0x0088 */
#define MR         0x0000       /* Mode Register */
#define MR_IND     0x01         /* MR: Indirect */
#define MR_AINC    0x02         /* MR: Auto-Incrememt */
#define MR_RST     0x80         /* MR: Reset */ 
#define GAR0       0x0001       /* Gateway Address Register 0 */
#define GAR1       0x0002       /* Gateway Address Register 1 */
#define GAR2       0x0003       /* Gateway Address Register 2 */
#define GAR3       0x0004       /* Gateway Address Register 3 */
#define SUBR0      0x0005       /* Subnet Mask Address Register 0 */
#define SUBR1      0x0006       /* Subnet Mask Address Register 1 */
#define SUBR2      0x0007       /* Subnet Mask Address Register 2 */
#define SUBR3      0x0008       /* Subnet Mask Address Register 3 */
#define SHAR0      0x0009       /* Source Hardware Address Register 0 */
#define SHAR1      0x000A       /* Source Hardware Address Register 1 */
#define SHAR2      0x000B       /* Source Hardware Address Register 2 */
#define SHAR3      0x000C       /* Source Hardware Address Register 3 */
#define SHAR4      0x000D       /* Source Hardware Address Register 4 */
#define SHAR5      0x000E       /* Source Hardware Address Register 5 */
#define SIPR0      0x000F       /* Source IP Address Register 0 */
#define SIPR1      0x0010       /* Source IP Address Register 1 */
#define SIPR2      0x0011       /* Source IP Address Register 2 */
#define SIPR3      0x0012       /* Source IP Address Register 3 */
#define INTPTMR0   0x0013       /* Interrupt Pending Time Register 0 */
#define INTPTMR1   0x0014       /* Interrupt Pending Time Register 1 */
#define IR         0x0015       /* Interrupt Register */
#define IMR        0x0016       /* Interrupt Mask Register */
#define RTR0       0x0017       /* Retransmission Time Register 0 */
#define RTR1       0x0018       /* Retransmission Time Register 1 */
#define RCR        0x0019       /* Retransmission Count Register */
#define RMSR       0x001A       /* RX Memory Size Register */
#define TMSR       0x001B       /* TX Memory Size Register */
                                /* 0x001C-0x001F -- Reserved -- */
#define IR2        0x0020       /* Interrupt2 Register */
#define IMR2       0x0021       /* Interrupt2 Mask Register */
                                /* 0x0022-0x0027 -- Reserved -- */
#define PTIMER     0x0028       /* PPP LCP Request Timer */
#define PMAGIC     0x0029       /* PPP LCP Magic Number */
#define UIPR0      0x002A       /* Unreachable IP Address Register 0 */
#define UIPR1      0x002B       /* Unreachable IP Address Register 1 */
#define UIPR2      0x002C       /* Unreachable IP Address Register 2 */
#define UIPR3      0x002D       /* Unreachable IP Address Register 0 */
#define UPORTR0    0x002E       /* Unreachable Port Register 0 */
#define UPORTR1    0x002F       /* Unreachable Port Register 1 */
#define MR2        0x0030       /* Mode2 Register */
                                /* 0x0031 --  Reserved -- */
#define PHAR0      0x0032       /* Destination Hardware Address on PPPoE Register 0 */
#define PHAR1      0x0033       /* Destination Hardware Address on PPPoE Register 1 */
#define PHAR2      0x0034       /* Destination Hardware Address on PPPoE Register 2 */
#define PHAR3      0x0035       /* Destination Hardware Address on PPPoE Register 3 */
#define PHAR4      0x0036       /* Destination Hardware Address on PPPoE Register 4 */
#define PHAR5      0x0037       /* Destination Hardware Address on PPPoE Register 5 */
#define PSIDR0     0x0038       /* Session ID on PPPoE Register 0 */
#define PSIDR1     0x0039       /* Session ID on PPPoE Register 1 */
#define PMRUR0     0x003A       /* Maximum Receive Unit on PPPoE Register 0 */
#define PMRUR1     0x003B       /* Maximum Receive Unit on PPPoE Register 1 */
#define PHYSR0     0x003C       /* PHY Status Register 0 */
#define PHYSR1     0x003D       /* PHY Status Register 1 */
#define PHYAR      0x003E       /* PHY Address Value */
#define PHYRAR     0x003F       /* PHY Register Address */
#define PHYDIR0    0x0040       /* PHY Data Input Register 0 */
#define PHYDIR1    0x0041       /* PHY Data Input Register 1 */
#define PHYDOR0    0x0042       /* PHY Data Output Register 0 */
#define PHYDOR1    0x0043       /* PHY Data Output Register 1 */
#define PHYACR     0x0044       /* PHY Access Register */
#define PHYDIVR    0x0045       /* PHY Division Register */
#define PHYCR0     0x0046       /* PHY Control Register 0 */
#define PHYCR1     0x0047       /* PHY Control Register 1 */
                                /* 0x0048-0x004B -- Reserved -- */
#define SLCR       0x004C       /* SOCKET-less Command Register */
#define SLCR_P     0x01         /* Ping */
#define SLCR_A     0x02         /* ARP */
#define SLRTR0     0x004D       /* SOCKET-less Retransmission Time Register 0 */
#define SLRTR1     0x004E       /* SOCKET-less Retransmission Time Register 1 */
#define SLRCR      0x004F       /* SOCKET-less Retransmission Count Register */
#define SLPIPR0    0x0050       /* SOCKET-less Peer IP Address Register 0 */
#define SLPIPR1    0x0051       /* SOCKET-less Peer IP Address Register 1 */
#define SLPIPR2    0x0052       /* SOCKET-less Peer IP Address Register 2 */
#define SLPIPR3    0x0053       /* SOCKET-less Peer IP Address Register 3 */
#define SLPHAR0    0x0054       /* SOCKET-less Peer Hardware Address Register 0 */
#define SLPHAR1    0x0055       /* SOCKET-less Peer Hardware Address Register 1 */
#define SLPHAR2    0x0056       /* SOCKET-less Peer Hardware Address Register 2 */
#define SLPHAR3    0x0057       /* SOCKET-less Peer Hardware Address Register 3 */
#define SLPHAR4    0x0058       /* SOCKET-less Peer Hardware Address Register 4 */
#define SLPHAR5    0x0059       /* SOCKET-less Peer Hardware Address Register 5 */
#define PINGSEQR0  0x005A       /* PING Sequence Number Register 0 */
#define PINGSEQR1  0x005B       /* PING Sequence Number Register 1 */
#define PINGIDR0   0x005C       /* PING ID Register 0 */
#define PINGIDR1   0x005D       /* PING ID Register 1 */
#define SLIMR      0x005E       /* SOCKET-less Interrupt Mask Register */
#define SLIMR_P    0x01         /* Ping */
#define SLIMR_A    0x02         /* ARP */
#define SLIMR_T    0x04         /* Timeout */
#define SLIR       0x005F       /* SOCKET-less Interrupt Register */
#define SLIR_P     0x01         /* Ping */
#define SLIR_A     0x02         /* ARP */
#define SLIR_T     0x04         /* Timeout */
                                /* 0x0060-0x006A -- Reserved -- */
#define CLKLCKR    0x0070       /* Clock Lock Register */
#define NETLCKR    0x0071       /* Network Lock Register */
#define PHYLCKR    0x0072       /* PHY Lock Register */
                                /* 0x0073-0x007F -- Reserved -- */
#define VERR       0x0080       /* Chip Version */
                                /* 0x0081 -- Reserved -- */
#define TCNTR0     0x0082       /* 100us Ticker Counter Register 0 */
#define TCNTR1     0x0083       /* 100us Ticker Counter Register 1 */
                                /* 0x0084-0x0087 -- Reserved -- */
#define TCNTCLR    0x0088       /* 100us Ticker Counter Clear Register */

                                /* SOCKET 0 REGISTERS 0x0400-0x04FF 45 bytes per socket */
#define S0_MR      0x0400       /* Socket 0 Mode Register */
#define S0_CR      0x0401       /* Socket 0 Command Register */
#define S0_IR      0x0402       /* Socket 0 Interrupt Register */
#define S0_SR      0x0403       /* Socket 0 Status Register */
#define S0_PORTR0  0x0404       /* Socket 0 Source Port Register 0 */
#define S0_PORTR1  0x0405       /* Socket 0 Source Port Register 1 */
#define S0_DHAR0   0x0406       /* Socket 0 Destination Hardware Address Register 0 */
#define S0_DHAR1   0x0407       /* Socket 0 Destination Hardware Address Register 1 */
#define S0_DHAR2   0x0408       /* Socket 0 Destination Hardware Address Register 2 */
#define S0_DHAR3   0x0409       /* Socket 0 Destination Hardware Address Register 3 */
#define S0_DHAR4   0x040A       /* Socket 0 Destination Hardware Address Register 4 */
#define S0_DHAR5   0x040B       /* Socket 0 Destination Hardware Address Register 5 */
#define S0_DIPR0   0x040C       /* Socket 0 Destination IP Address Register 0 */
#define S0_DIPR1   0x040D       /* Socket 0 Destination IP Address Register 1 */
#define S0_DIPR2   0x040E       /* Socket 0 Destination IP Address Register 2 */
#define S0_DIPR3   0x040F       /* Socket 0 Destination IP Address Register 3 */
#define S0_DPORTR0 0x0410       /* Socket 0 Destination Port Register 0 */
#define S0_DPORTR1 0x0411       /* Socket 0 Destination Port Register 1 */
#define S0_MSS0    0x0412       /* Socket 0 Maximum Segment Size Register 0 */
#define S0_MSS1    0x0413       /* Socket 0 Maximum Segment Size Register 1 */
#define S0_PROTOR  0x0414       /* Socket 0 IP Protocol Register */
#define S0_TOS     0x0415       /* Socket 0 IP Type Of Service */
#define S0_TTL     0x0416       /* Socket 0 IP Time To Live */
                                /* 0x0417-0x041D -- Reserved -- */
#define S0_RXBUF_SIZE  equ  $041E    /* Socket 0 RX Buffer Size */
#define S0_TXBUF_SIZE  equ  $041F    /* Socket 0 TX Buffer Size */
#define S0_TX_FSR0 0x0420       /* Socket 0 TX Free Size Register 0 */
#define S0_TX_FSR1 0x0421       /* Socket 0 TX Free Size Register 1 */
#define S0_TX_RD0  0x0422       /* Socket 0 TX Read Pointer 0 */
#define S0_TX_RD1  0x0423       /* Socket 0 TX Read Pointer 1 */
#define S0_TX_WR0  0x0424       /* Socket 0 TX Write Pointer 0 */
#define S0_TX_WR1  0x0425       /* Socket 0 TX Write Pointer 1 */
#define S0_RX_RSR0 0x0426       /* Socket 0 RX Received Size Register 0 */
#define S0_RX_RSR1 0x0427       /* Socket 0 RX Received Size Register 1 */
#define S0_RX_RD0  0x0428       /* Socket 0 RX Read Pointer 0 */
#define S0_RX_RD1  0x0429       /* Socket 0 RX Read Pointer 1 */
#define S0_RX_WR0  0x042A       /* Socket 0 RX Write Pointer 0 */
#define S0_RX_WR1  0x042B       /* Socket 0 RX Write Pointer 1 */
#define S0_IMR     0x042C       /* Socket 0 Interrupt Mask Register */
#define S0_FRAGR0  0x042D       /* Socket 0 Fragment Offset in IP Header Register 0 */
#define S0_FRAGR1  0x042E       /* Socket 0 Fragment Offset in IP Header Register 1 */
#define S0_MR2     0x042F       /* Socket 0 Mode 2 Register */
#define S0_KPALVTR 0x0430       /* Socket 0 Keep-alive Timer Register */
                                /* 0x0431 -- Reserved -- */
#define S0_RTR0    0x0432       /* Socket 0 Retransmission Time Register 0 */
#define S0_RTR1    0x0433       /* Socket 0 Retransmission Time Register 1 */
#define S0_RCR     0x0434       /* Socket 0 Retransmission Count Register */

                                /* SOCKET 1 REGISTERS 0x0500-0x05FF 45 bytes per socket */
#define S1_MR      0x0500       /* Socket 1 Mode Register */
#define S1_CR      0x0501       /* Socket 1 Command Register */
#define S1_IR      0x0502       /* Socket 1 Interrupt Register */
#define S1_SR      0x0503       /* Socket 1 Status Register */
#define S1_PORTR0  0x0504       /* Socket 1 Source Port Register 0 */
#define S1_PORTR1  0x0505       /* Socket 1 Source Port Register 1 */
#define S1_DHAR0   0x0506       /* Socket 1 Destination Hardware Address Register 0 */
#define S1_DHAR1   0x0507       /* Socket 1 Destination Hardware Address Register 1 */
#define S1_DHAR2   0x0508       /* Socket 1 Destination Hardware Address Register 2 */
#define S1_DHAR3   0x0509       /* Socket 1 Destination Hardware Address Register 3 */
#define S1_DHAR4   0x050A       /* Socket 1 Destination Hardware Address Register 4 */
#define S1_DHAR5   0x050B       /* Socket 1 Destination Hardware Address Register 5 */
#define S1_DIPR0   0x050C       /* Socket 1 Destination IP Address Register 0 */
#define S1_DIPR1   0x050D       /* Socket 1 Destination IP Address Register 1 */
#define S1_DIPR2   0x050E       /* Socket 1 Destination IP Address Register 2 */
#define S1_DIPR3   0x050F       /* Socket 1 Destination IP Address Register 3 */
#define S1_DPORTR0 0x0510       /* Socket 1 Destination Port Register 0 */
#define S1_DPORTR1 0x0511       /* Socket 1 Destination Port Register 1 */
#define S1_MSS0    0x0512       /* Socket 1 Maximum Segment Size Register 0 */
#define S1_MSS1    0x0513       /* Socket 1 Maximum Segment Size Register 1 */
#define S1_PROTOR  0x0514       /* Socket 1 IP Protocol Register */
#define S1_TOS     0x0515       /* Socket 1 IP Type Of Service */
#define S1_TTL     0x0516       /* Socket 1 IP Time To Live */
                                /* 0x0517-0x051D -- Reserved -- */
#define S1_RXBUF_SIZE  equ  $051E    /* Socket 1 RX Buffer Size */
#define S1_TXBUF_SIZE  equ  $051F    /* Socket 1 TX Buffer Size */
#define S1_TX_FSR0 0x0520       /* Socket 1 TX Free Size Register 0 */
#define S1_TX_FSR1 0x0521       /* Socket 1 TX Free Size Register 1 */
#define S1_TX_RD0  0x0522       /* Socket 1 TX Read Pointer 0 */
#define S1_TX_RD1  0x0523       /* Socket 1 TX Read Pointer 1 */
#define S1_TX_WR0  0x0524       /* Socket 1 TX Write Pointer 0 */
#define S1_TX_WR1  0x0525       /* Socket 1 TX Write Pointer 1 */
#define S1_RX_RSR0 0x0526       /* Socket 1 RX Received Size Register 0 */
#define S1_RX_RSR1 0x0527       /* Socket 1 RX Received Size Register 1 */
#define S1_RX_RD0  0x0528       /* Socket 1 RX Read Pointer 0 */
#define S1_RX_RD1  0x0529       /* Socket 1 RX Read Pointer 1 */
#define S1_RX_WR0  0x052A       /* Socket 1 RX Write Pointer 0 */
#define S1_RX_WR1  0x052B       /* Socket 1 RX Write Pointer 1 */
#define S1_IMR     0x052C       /* Socket 1 Interrupt Mask Register */
#define S1_FRAGR0  0x052D       /* Socket 1 Fragment Offset in IP Header Register 0 */
#define S1_FRAGR1  0x052E       /* Socket 1 Fragment Offset in IP Header Register 1 */
#define S1_MR2     0x052F       /* Socket 1 Mode 2 Register */
#define S1_KPALVTR 0x0530       /* Socket 1 Keep-alive Timer Register */
                                /* 0x0531 -- Reserved -- */
#define S1_RTR0    0x0532       /* Socket 1 Retransmission Time Register 0 */
#define S1_RTR1    0x0533       /* Socket 1 Retransmission Time Register 1 */
#define S1_RCR     0x0534       /* Socket 1 Retransmission Count Register */

                                /* SOCKET 2 REGISTERS 0x0600-0x06FF 45 bytes per socket */
#define S2_MR      0x0600       /* Socket 2 Mode Register */
#define S2_CR      0x0601       /* Socket 2 Command Register */
#define S2_IR      0x0602       /* Socket 2 Interrupt Register */
#define S2_SR      0x0603       /* Socket 2 Status Register */
#define S2_PORTR0  0x0604       /* Socket 2 Source Port Register 0 */
#define S2_PORTR1  0x0605       /* Socket 2 Source Port Register 1 */
#define S2_DHAR0   0x0606       /* Socket 2 Destination Hardware Address Register 0 */
#define S2_DHAR1   0x0607       /* Socket 2 Destination Hardware Address Register 1 */
#define S2_DHAR2   0x0608       /* Socket 2 Destination Hardware Address Register 2 */
#define S2_DHAR3   0x0609       /* Socket 2 Destination Hardware Address Register 3 */
#define S2_DHAR4   0x060A       /* Socket 2 Destination Hardware Address Register 4 */
#define S2_DHAR5   0x060B       /* Socket 2 Destination Hardware Address Register 5 */
#define S2_DIPR0   0x060C       /* Socket 2 Destination IP Address Register 0 */
#define S2_DIPR1   0x060D       /* Socket 2 Destination IP Address Register 1 */
#define S2_DIPR2   0x060E       /* Socket 2 Destination IP Address Register 2 */
#define S2_DIPR3   0x060F       /* Socket 2 Destination IP Address Register 3 */
#define S2_DPORTR0 0x0610       /* Socket 2 Destination Port Register 0 */
#define S2_DPORTR1 0x0611       /* Socket 2 Destination Port Register 1 */
#define S2_MSS0    0x0612       /* Socket 2 Maximum Segment Size Register 0 */
#define S2_MSS1    0x0613       /* Socket 2 Maximum Segment Size Register 1 */
#define S2_PROTOR  0x0614       /* Socket 2 IP Protocol Register */
#define S2_TOS     0x0615       /* Socket 2 IP Type Of Service */
#define S2_TTL     0x0616       /* Socket 2 IP Time To Live */
                                /* 0x0617-0x061D -- Reserved -- */
#define S2_RXBUF_SIZE  equ  $061E    /* Socket 2 RX Buffer Size */
#define S2_TXBUF_SIZE  equ  $061F    /* Socket 2 TX Buffer Size */
#define S2_TX_FSR0 0x0620       /* Socket 2 TX Free Size Register 0 */
#define S2_TX_FSR1 0x0621       /* Socket 2 TX Free Size Register 1 */
#define S2_TX_RD0  0x0622       /* Socket 2 TX Read Pointer 0 */
#define S2_TX_RD1  0x0623       /* Socket 2 TX Read Pointer 1 */
#define S2_TX_WR0  0x0624       /* Socket 2 TX Write Pointer 0 */
#define S2_TX_WR1  0x0625       /* Socket 2 TX Write Pointer 1 */
#define S2_RX_RSR0 0x0626       /* Socket 2 RX Received Size Register 0 */
#define S2_RX_RSR1 0x0627       /* Socket 2 RX Received Size Register 1 */
#define S2_RX_RD0  0x0628       /* Socket 2 RX Read Pointer 0 */
#define S2_RX_RD1  0x0629       /* Socket 2 RX Read Pointer 1 */
#define S2_RX_WR0  0x062A       /* Socket 2 RX Write Pointer 0 */
#define S2_RX_WR1  0x062B       /* Socket 2 RX Write Pointer 1 */
#define S2_IMR     0x062C       /* Socket 2 Interrupt Mask Register */
#define S2_FRAGR0  0x062D       /* Socket 2 Fragment Offset in IP Header Register 0 */
#define S2_FRAGR1  0x062E       /* Socket 2 Fragment Offset in IP Header Register 1 */
#define S2_MR2     0x062F       /* Socket 2 Mode 2 Register */
#define S2_KPALVTR 0x0630       /* Socket 2 Keep-alive Timer Register */
                                /* 0x0631 -- Reserved -- */
#define S2_RTR0    0x0632       /* Socket 2 Retransmission Time Register 0 */
#define S2_RTR1    0x0633       /* Socket 2 Retransmission Time Register 1 */
#define S2_RCR     0x0634       /* Socket 2 Retransmission Count Register */

                                /* SOCKET 3 REGISTERS 0x0700-0x07FF 45 bytes per socket */
#define S3_MR      0x0700       /* Socket 3 Mode Register */
#define S3_CR      0x0701       /* Socket 3 Command Register */
#define S3_IR      0x0702       /* Socket 3 Interrupt Register */
#define S3_SR      0x0703       /* Socket 3 Status Register */
#define S3_PORTR0  0x0704       /* Socket 3 Source Port Register 0 */
#define S3_PORTR1  0x0705       /* Socket 3 Source Port Register 1 */
#define S3_DHAR0   0x0706       /* Socket 3 Destination Hardware Address Register 0 */
#define S3_DHAR1   0x0707       /* Socket 3 Destination Hardware Address Register 1 */
#define S3_DHAR2   0x0708       /* Socket 3 Destination Hardware Address Register 2 */
#define S3_DHAR3   0x0709       /* Socket 3 Destination Hardware Address Register 3 */
#define S3_DHAR4   0x070A       /* Socket 3 Destination Hardware Address Register 4 */
#define S3_DHAR5   0x070B       /* Socket 3 Destination Hardware Address Register 5 */
#define S3_DIPR0   0x070C       /* Socket 3 Destination IP Address Register 0 */
#define S3_DIPR1   0x070D       /* Socket 3 Destination IP Address Register 1 */
#define S3_DIPR2   0x070E       /* Socket 3 Destination IP Address Register 2 */
#define S3_DIPR3   0x070F       /* Socket 3 Destination IP Address Register 3 */
#define S3_DPORTR0 0x0710       /* Socket 3 Destination Port Register 0 */
#define S3_DPORTR1 0x0711       /* Socket 3 Destination Port Register 1 */
#define S3_MSS0    0x0712       /* Socket 3 Maximum Segment Size Register 0 */
#define S3_MSS1    0x0713       /* Socket 3 Maximum Segment Size Register 1 */
#define S3_PROTOR  0x0714       /* Socket 3 IP Protocol Register */
#define S3_TOS     0x0715       /* Socket 3 IP Type Of Service */
#define S3_TTL     0x0716       /* Socket 3 IP Time To Live */
                                /* 0x0717-0x071D -- Reserved -- */
#define S3_RXBUF_SIZE  0x071E    /* Socket 3 RX Buffer Size */
#define S3_TXBUF_SIZE  0x071F    /* Socket 3 TX Buffer Size */
#define S3_TX_FSR0 0x0720       /* Socket 3 TX Free Size Register 0 */
#define S3_TX_FSR1 0x0721       /* Socket 3 TX Free Size Register 1 */
#define S3_TX_RD0  0x0722       /* Socket 3 TX Read Pointer 0 */
#define S3_TX_RD1  0x0723       /* Socket 3 TX Read Pointer 1 */
#define S3_TX_WR0  0x0724       /* Socket 3 TX Write Pointer 0 */
#define S3_TX_WR1  0x0725       /* Socket 3 TX Write Pointer 1 */
#define S3_RX_RSR0 0x0726       /* Socket 3 RX Received Size Register 0 */
#define S3_RX_RSR1 0x0727       /* Socket 3 RX Received Size Register 1 */
#define S3_RX_RD0  0x0728       /* Socket 3 RX Read Pointer 0 */
#define S3_RX_RD1  0x0729       /* Socket 3 RX Read Pointer 1 */
#define S3_RX_WR0  0x072A       /* Socket 3 RX Write Pointer 0 */
#define S3_RX_WR1  0x072B       /* Socket 3 RX Write Pointer 1 */
#define S3_IMR     0x072C       /* Socket 3 Interrupt Mask Register */
#define S3_FRAGR0  0x072D       /* Socket 3 Fragment Offset in IP Header Register 0 */
#define S3_FRAGR1  0x072E       /* Socket 3 Fragment Offset in IP Header Register 1 */
#define S3_MR2     0x072F       /* Socket 3 Mode 2 Register */
#define S3_KPALVTR 0x0730       /* Socket 3 Keep-alive Timer Register */
                                /* 0x0731 -- Reserved -- */
#define S3_RTR0    0x0732       /* Socket 3 Retransmission Time Register 0 */
#define S3_RTR1    0x0733       /* Socket 3 Retransmission Time Register 1 */
#define S3_RCR     0x0734       /* Socket 3 Retransmission Count Register */

                                /* End of Equates */
/* Structures */

/* struct w5100_info

W5100S Card Basic Setup Info
   Length: 18
    Start: GAR0 (0x0001)
      End: SIPR3 (0x0012)

*** IMPORTANT NOTE ***
This structure has extra data at the end.  The reason why is this structure is
used to read in the contents of /DD/SYS/interfaces, which contains the extra
fields phyaddr and iface.  These fields should never be written to the card.
If you do you will be writing garbage values to the card.  You have been
warned.

   Example:
        #include "w5100s.h"
        struct w51info iface;
        regblkst(&iface, GAR0, W51INFO_LEN);
*/

#define W51INFO_LEN 18

struct w51info {
    uint8_t gateway[4];  /* Gateway  - GAR0 -  GAR3 */
    uint8_t netmask[4];  /* Subnet   - SUBR0 - SUBR3 */
    uint8_t macaddr[6];  /* MAC Addr - SHAR0 - SHAR5 */
    uint8_t address[4];  /* IP Addr  - SIPR0 - SIPR3 */
    /* End of Data */
    /* Extra - DO NOT WRITE TO DEVICE */
    uint8_t *phyaddr;
    uint8_t iface[8];
};

/* struct w5100_sklsip

SOCKET-less IP Setup Info

   Length: 22
    Start: SLRTR0 (0x004D)
      End: SLIMR (0x005E)

   Example:
        #include "w5100s.h"
        struct sklsip pingsetup;
        regblkst(&pingsetup, SLRTR0, sizeof(struct sklsip));
*/

struct sklsip {
    uint16_t retranst;      /* SLRTR0, SLRTR1 */
     uint8_t retransc;      /* SLRCR */
     uint8_t peerip[4];     /* SLPIPR0 - SLPIPR3 */
     uint8_t peermac[6];    /* SLPHAR0 - SLPHAR5 */
    uint16_t pingseqn;      /* PINGSEQR0, PINGSEQR1 */
    uint16_t pingid;        /* PINGIDR0, PINGIDR1 */
     uint8_t sklipmsk;      /* SLIMR */
};


/* Function Declarations */
int rgstvfy();
int w51reset();
int rgblkset();
int rgblkget();
int w51init();

#endif