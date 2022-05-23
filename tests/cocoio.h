/*********************************************************************
;* Title: COCOIOEQU.asm
;*********************************************************************
;* Author: R. Allen Murphey
;*
;* License: Contributed 2021 by R. Allen Murphey to CoCoIO Development
;*
;* Description: CoCoIO for Color Computer Equates
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
;* 00     2021         RAM     Initial equates from Rick Ulland's Notes
;*********************************************************************/

                                /* CoCoIO with Jumper set to 0xFF6x Range */
#define CIO0CMND   0xFF68       /* CoCoIO Command Register  */
#define CIO0ADDR   0xFF69       /* CoCoIO Address Register MSB */
              /*   0xFF6A        ; CoCoIO Address Register LSB */
#define CIO0DATA   0xFF6B       /* CoCoIO Read/Write Data Register */

                                /* CoCoIO with Jumper set to 0xFF7x Range */
#define CIO1CMND   0xFF78       /* CoCoIO Command Register  */
#define CIO1ADDR   0xFF79       /* CoCoIO Address Register MSB */
              /*   0xFF7A        ; CoCoIO Address Register LSB */
#define CIO1DATA   0xFF7B       /* CoCoIO Read/Write Data Register */

                               /* End of CoCoIO equates */
