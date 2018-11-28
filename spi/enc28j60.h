/**
 *
 * File Name: enc28j60.h
 * Title    : SPI device Microchip ENC28J60 ethernet controller library header
 * Project  : lib-avr
 * Author   : Copyright (C) 2018 Johannes Krottmayer <krjdev@gmail.com>
 * Created  : 2018-09-22
 * Modified : 
 * Revised  : 
 * Version  : 0.1.0.0
 * License  : ISC (see file LICENSE.txt)
 * Target   : Atmel AVR Series
 *
 * NOTE: This code is currently below version 1.0, and therefore is considered
 * to be lacking in some functionality or documentation, or may not be fully
 * tested. Nonetheless, you can expect most functions to work.
 *
 */

#ifndef LIBAVR_SPI_ENC28J60_H
#define LIBAVR_SPI_ENC28J60_H

#include <stdint.h>
#include <avr/io.h>

#include "../net/ethernet.h"

/* ENC28J60 Chip select */
#define ENC28J60_CSCONFIG   (DDRJ = (1 << PJ0))
#define ENC28J60_ENABLE     (PORTJ &= ~(1 << PJ0))
#define ENC28J60_DISABLE    (PORTJ |= (1 << PJ0))

#define ENC28J60_BUFSZ      8192

/* SPI Instruction Set */
#define SPI_RCR     0x00 /* Read Control Register */
#define SPI_RBM     0x3A /* Read Buffer Memory */
#define SPI_WCR     0x40 /* Write Control Register */
#define SPI_WBM     0x7A /* Write Buffer Memory */
#define SPI_BFS     0x80 /* Bit Field Set */
#define SPI_BFC     0xA0 /* Bit Field Clear */
#define SPI_SRC     0xFF /* System Reset Command (Soft Reset) */

/* Register banks */
#define BANK0       0x00
#define BANK1       0x01
#define BANK2       0x02
#define BANK3       0x03

/* Common Register (8-bit) */
#define EIE         0x1B /* Ethernet Interrupt Enable Register */

    /* EIE flags */
    #define EIE_RXERIE      0 /* Receive Error Interrupt Enable bit */
    #define EIE_TXERIE      1 /* Transmit Error Interrupt Enable bit */
    #define EIE_TXIE        3 /* Transmit Enable bit */
    #define EIE_LINKIE      4 /* Link Status Change Interrupt Enable bit */
    #define EIE_DMAIE       5 /* DMA Interrupt Enable bit */
    #define EIE_PKTIE       6 /* Receive Packet Pending Interrupt Enable bit */
    #define EIE_INTIE       7 /* Global INT Interrupt Enable bit */

#define EIR         0x1C /* Ethernet Interrupt Request (Flag) Register */

    /* EIR flags */
    #define EIR_RXERIF      0 /* Receive Error Interrupt Flag bit */
    #define EIR_TXERIF      1 /* Transmit Error Interrupt Flag bit */
    #define EIR_TXIF        3 /* Transmit Interrupt Flag bit */
    #define EIR_LINKIF      4 /* Link Change Interrupt Flag bit */
    #define EIR_DMAIF       5 /* DMA Interrupt Flag bit */
    #define EIR_PKTIF       6 /* Receive Packet Pending Interrupt Flag bit */

#define ESTAT       0x1D /* Ethernet Status Register */

    /* ESTAT flags */
    #define ESTAT_CLKRDY    0 /* Clock Ready bit */
    #define ESTAT_TXABRT    1 /* Transmit Abort Error bit */
    #define ESTAT_RXBUSY    2 /* Receive Busy bit */
    #define ESTAT_LATECOL   4 /* Late Collision Error bit */
    #define ESTAT_BUFER     6 /* Ethernet Buffer Error Status bit */
    #define ESTAT_INT       7 /* INT Interrupt Flag bit */

#define ECON2       0x1E /* Ethernet Control Register 2 */

    /* ECON2 flags */
    #define ECON2_VRPS      3 /* Voltage Regulator Power Save Enable bit */
    #define ECON2_PWRSV     5 /* Power Save Enable bit */
    #define ECON2_PKTDEC    6 /* Packet Decrement bit */
    #define ECON2_AUTOINC   7 /* Automatic Buffer Pointer Increment Enable bit */

#define ECON1       0x1F /* Ethernet Control Register 1 */

    /* ECON1 flags */
    #define ECON1_BSEL0     0 /* Bank Select bit 0 */
    #define ECON1_BSEL1     1 /* Bank Select bit 1 */
    #define ECON1_RXEN      2 /* Receive Enable bit */
    #define ECON1_TXRTS     3 /* Transmit Request to Send bit */
    #define ECON1_CSUMEN    4 /* DMA Checksum Enable bit */
    #define ECON1_DMAST     5 /* DMA Start and Busy Status bit */
    #define ECON1_RXRST     6 /* Receive Logic Reset bit */
    #define ECON1_TXRST     7 /* Transmit Logic Reset bit */

/* Bank 0 Register (8-bit) */
#define ERDPTL      0x00 /* Read Pointer Low Byte (ERDPT<7:0>) */
#define ERDPTH      0x01 /* Read Pointer High Byte (ERDPT<12:8>) */
#define EWRPTL      0x02 /* Write Pointer Low Byte (EWRPT<7:0>) */
#define EWRPTH      0x03 /* Write Pointer High Byte (EWRPT<12:8>) */
#define ETXSTL      0x04 /* TX Start Low Byte (ETXST<7:0>) */
#define ETXSTH      0x05 /* TX Start High Byte (ETXST<12:8>) */
#define ETXNDL      0x06 /* TX End Low Byte (ETXND<7:0>) */
#define ETXNDH      0x07 /* TX End High Byte (ETXND<12:8>) */
#define ERXSTL      0x08 /* RX Start Low Byte (ERXST<7:0>) */
#define ERXSTH      0x09 /* RX Start High Byte (ERXST<12:8>) */
#define ERXNDL      0x0A /* RX End Low Byte (ERXND<7:0>) */
#define ERXNDH      0x0B /* RX End High Byte (ERXND<12:8>) */
#define ERXRDPTL    0x0C /* RX RD Pointer Low Byte (ERXRDPT<7:0>) */
#define ERXRDPTH    0x0D /* RX RD Pointer High Byte (ERXRDPT<12:8>) */
#define ERXWRPTL    0x0E /* RX WR Pointer Low Byte (ERXWRPT<7:0>) */
#define ERXWRPTH    0x0F /* RX WR Pointer High Byte (ERXWRPT<12:8>) */
#define EDMASTL     0x10 /* DMA Start Low Byte (EDMAST<7:0>) */
#define EDMASTH     0x11 /* DMA Start High Byte (EDMAST<12:8>) */
#define EDMANDL     0x12 /* DMA End Low Byte (EDMAND<7:0>) */
#define EDMANDH     0x13 /* DMA End High Byte (EDMAND<12:8>) */
#define EDMADSTL    0x14 /* DMA Destination Low Byte (EDMADST<7:0>) */
#define EDMADSTH    0x15 /* DMA Destination High Byte (EDMADST<12:8>) */
#define EDMACSL     0x16 /* DMA Checksum Low Byte (EDMACS<7:0>) */
#define EDMACSH     0x17 /* DMA Checksum High Byte (EDMACS<15:8>) */

/* Bank 1 Register (8-bit) */
#define EHT0        0x00 /* Hash Table Byte 0 (EHT<7:0>) */
#define EHT1        0x01 /* Hash Table Byte 1 (EHT<15:8>) */
#define EHT2        0x02 /* Hash Table Byte 2 (EHT<23:16>) */
#define EHT3        0x03 /* Hash Table Byte 3 (EHT<31:24>) */
#define EHT4        0x04 /* Hash Table Byte 4 (EHT<39:32>) */
#define EHT5        0x05 /* Hash Table Byte 5 (EHT<47:40>) */
#define EHT6        0x06 /* Hash Table Byte 6 (EHT<55:48>) */
#define EHT7        0x07 /* Hash Table Byte 7 (EHT<63:56>) */
#define EPMM0       0x08 /* Pattern Match Mask Byte 0 (EPMM<7:0>) */
#define EPMM1       0x09 /* Pattern Match Mask Byte 1 (EPMM<15:8>) */
#define EPMM2       0x0A /* Pattern Match Mask Byte 2 (EPMM<23:16>) */
#define EPMM3       0x0B /* Pattern Match Mask Byte 3 (EPMM<31:24>) */
#define EPMM4       0x0C /* Pattern Match Mask Byte 4 (EPMM<39:32>) */
#define EPMM5       0x0D /* Pattern Match Mask Byte 5 (EPMM<47:40>) */
#define EPMM6       0x0E /* Pattern Match Mask Byte 6 (EPMM<55:48>) */
#define EPMM7       0x0F /* Pattern Match Mask Byte 7 (EPMM<63:56>) */
#define EPMCSL      0x10 /* Pattern Match Checksum Low Byte (EPMCS<7:0>) */
#define EPMCSH      0x11 /* Pattern Match Checksum High Byte (EPMCS<15:0>) */
#define EPMOL       0x14 /* Pattern Match Offset Low Byte (EPMO<7:0>) */
#define EPMOH       0x15 /* Pattern Match Offset High Byte (EPMO<12:8>) */
#define ERXFCON     0x18 /* Ethernet Receive Filter Control Register */

    /* ERXFCON flags */
    #define ERXFCON_BCEN    0 /* Broadcast Filter Enable bit */
    #define ERXFCON_MCEN    1 /* Multicast Filter Enable bit */
    #define ERXFCON_HTEN    2 /* Hash Table Filter Enable bit */
    #define ERXFCON_MPEN    3 /* Magic Packet Filter Enable bit */
    #define ERXFCON_PMEN    4 /* Pattern Match Filter Enable bit */
    #define ERXFCON_CRCEN   5 /* Post-Filter CRC Check Enable bit */
    #define ERXFCON_ANDOR   6 /* AND/OR Filter Select bit */
    #define ERXFCON_UCEN    7 /* Unicast Filter Enable bit */

#define EPKTCNT     0x19 /* Ethernet Packet Count */

/* Bank 2 Register (8-bit) */
#define MACON1      0x00 /* MAC Control Register 1 */

    /* MACON1 flags */
    #define MACON1_MARXEN   0 /* MAC Receive Enable bit */
    #define MACON1_PASSALL  1 /* Pass All Received Frames Enable bit */
    #define MACON1_RXPAUS   2 /* Pause Control Frame Reception Enable bit */
    #define MACON1_TXPAUS   3 /* Pause Control Frame Transmission Enable bit */

#define MACON3      0x02 /* MAC Control Register 3 */

    /* MACON3 flags */
    #define MACON3_FULDPX   0 /* MAC Full-Duplex Enable bit */
    #define MACON3_FRMLNEN  1 /* Frame Length Checking Enable bit */
    #define MACON3_HFRMEN   2 /* Huge Frame Enable bit */
    #define MACON3_PHDREN   3 /* Proprietary Header Enable bit */
    #define MACON3_TXCRCEN  4 /* Transmit CRC Enable bit */
    #define MACON3_PADCFG0  5 /* Automatic Pad and CRC Configuration bit 0 */
    #define MACON3_PADCFG1  6 /* Automatic Pad and CRC Configuration bit 1 */
    #define MACON3_PADCFG2  7 /* Automatic Pad and CRC Configuration bit 2 */

#define MACON4      0x03 /* MAC Control Register 4 */

    /* MACON4 flags */
    #define MACON4_NOBKOFF  4 /* No Backoff Enable bit (applies to half duplex only) */
    #define MACON4_BPEN     5 /* No Backoff During Backpressure Enable bit (applies to half duplex only) */
    #define MACON4_DEFER    6 /* Defer Transmission Enable bit (applies to half duplex only) */

#define MABBIPG     0x04 /* MAC Back-To-Back Inter-Packet Gap Register */
#define MAIPGL      0x06 /* Non-Back-to-Back Inter-Packet Gap Low Byte (MAIPGL<6:0>) */
#define MAIPGH      0x07 /* Non-Back-to-Back Inter-Packet Gap High Byte (MAIPGH<6:0>) */
#define MACLCON1    0x08 /* Retransmission Maximum (RETMAX<3:0>) */
#define MACLCON2    0x09 /* Collision Window (COLWIN<5:0>) */
#define MAMXFLL     0x0A /* Maximum Frame Length Low Byte (MAMXFL<7:0>) */
#define MAMXFLH     0x0B /* Maximum Frame Length High Byte (MAMXFL<15:8>) */
#define MICMD       0x12 /* MII Command Register */

    /* MICMD flags */
    #define MICMD_MIIRD     0 /* MII Read Enable bit */
    #define MICMD_MIISCAN   1 /* MII Scan Enable bit */

#define MIREGADR    0x14 /* MII Register Address (MIREGADR<4:0>) */
#define MIWRL       0x16 /* MII Write Data Low Byte (MIWR<7:0>) */
#define MIWRH       0x17 /* MII Write Data High Byte (MIWR<15:8>) */
#define MIRDL       0x18 /* MII Read Data Low Byte (MIRD<7:0>) */
#define MIRDH       0x19 /* MII Read Data High Byte(MIRD<15:8>) */

/* Bank 3 Register (8-bit) */
#define MAADR5      0x00 /* MAC Address Byte 5 (MAADR<15:8>) */
#define MAADR6      0x01 /* MAC Address Byte 6 (MAADR<7:0>) */
#define MAADR3      0x02 /* MAC Address Byte 3 (MAADR<31:24>), OUI Byte 3 */
#define MAADR4      0x03 /* MAC Address Byte 4 (MAADR<23:16>) */
#define MAADR1      0x04 /* MAC Address Byte 1 (MAADR<47:40>), OUI Byte 1 */
#define MAADR2      0x05 /* MAC Address Byte 2 (MAADR<39:32>), OUI Byte 2 */
#define EBSTSD      0x06 /* Built-in Self-Test Fill Seed (EBSTSD<7:0>) */
#define EBSTCON     0x07 /* Ethernet Self-Test Control Register */

    /* EBSTCON flags */
    #define EBSTCON_BISTST  0 /* Built-in Self-Test Start/Busy bit */
    #define EBSTCON_TME     1 /* Test Mode Enable bit */
    #define EBSTCON_TMSEL0  2 /* Test Mode Select bit 0 */
    #define EBSTCON_TMSEL1  3 /* Test Mode Select bit 1 */
    #define EBSTCON_PSEL    4 /* Port Select bit */
    #define EBSTCON_PSV0    5 /* Pattern Shift Value bit 0 */
    #define EBSTCON_PSV1    6 /* Pattern Shift Value bit 0 */
    #define EBSTCON_PSV2    7 /* Pattern Shift Value bit 0 */

#define EBSTCSL     0x08 /* Built-in Self-Test Checksum Low Byte (EBSTCS<7:0>) */
#define EBSTCSH     0x09 /* Built-in Self-Test Checksum High Byte (EBSTCS<15:8>) */
#define MISTAT      0x0A /* MII Status Register */

    /* MISTAT flags */
    #define MISTAT_BUSY     0 /* MII Management Busy bit */
    #define MISTAT_SCAN     1 /* MII Management Scan Operation bit */
    #define MISTAT_NVALID   2 /* MII Management Read Data Not Valid bit */

#define EREVID      0x12 /* Ethernet Revision ID (EREVID<4:0>) */
#define ECOCON      0x15 /* Clock Output Control Register */

    /* ECOCON flags */
    #define ECOCON_COCON0   0 /* Clock Output Configuration bit 0 */
    #define ECOCON_COCON1   1 /* Clock Output Configuration bit 1 */
    #define ECOCON_COCON2   2 /* Clock Output Configuration bit 2 */

#define EFLOCON     0x17 /* Ethernet Flow Control Register */

    /* EFLOCON flags */
    #define EFLOCON_FCEN0   0 /* Flow Control Enable bit 0 */
    #define EFLOCON_FCEN1   1 /* Flow Control Enable bit 1 */
    #define EFLOCON_FULDPXS 2 /* Read-Only MAC Full-Duplex Shadow bit */

#define EPAUSL      0x18 /* Pause Timer Value Low Byte (EPAUS<7:0>) */
#define EPAUSH      0x19 /* Pause Timer Value High Byte (EPAUS<15:8>) */

/* PHY Register (16-bit) */
#define PHCON1      0x00 /* PHY Control Register 1 */

    /* PHCON1 flags */
    #define PHCON1_PDPXMD   8 /* PHY Duplex Mode bit */
    #define PHCON1_PPWRSV   11 /* PHY Power-Down bit */
    #define PHCON1_PLOOPBK  14 /* PHY Loopback bit */
    #define PHCON1_PRST     15 /* PHY Software Reset bit */

#define PHSTAT1     0x01 /* Physical Layer Status Register 1 */

    /* PHSTAT1 flags */
    #define PHSTAT1_JBSTAT  1 /* PHY Latching Jabber Status bit */
    #define PHSTAT1_LLSTAT  2 /* PHY Latching Link Status bit */
    #define PHSTAT1_PHDPX   11 /* PHY Half-Duplex Capable bit */
    #define PHSTAT1_PFDPX   12 /* PHY Full-Duplex Capable bit */

#define PHID1       0x02 /* PHY ID Register 1 */
#define PHID2       0x03 /*  PHY ID Register 2 */
#define PHCON2      0x10 /* PHY Control Register 2 */

    /* PHCON2 flags */
    #define PHCON2_HDLDIS   8 /* PHY Half-Duplex Loopback Disable bit */
    #define PHCON2_JABBER   10 /* Jabber Correction Disable bit */
    #define PHCON2_TXDIS    13 /* Twisted-Pair Transmitter Disable bit */
    #define PHCON2_FRCLNK   14 /* PHY Force Linkup bit */

#define PHSTAT2     0x11 /* Physical Layer Status Register 2 */

    /* PHSTAT2 flags */
    #define PHSTAT2_PLRITY  5 /* Polarity Status bit */
    #define PHSTAT2_DPXSTAT 9 /* PHY Duplex Status bit */
    #define PHSTAT2_LSTAT   10 /* PHY Link Status bit (non-latching) */
    #define PHSTAT2_COLSTAT 11 /* PHY Collision Status bit */
    #define PHSTAT2_RXSTAT  12 /* PHY Receive Status bit */
    #define PHSTAT2_TXSTAT  13 /* PHY Transmit Status bit */

#define PHIE        0x12 /* PHY Interrupt Enable Register */

    /* PHIE flags */
    #define PHIE_PGEIE      1 /* PHY Global Interrupt Enable bit */
    #define PHIE_PLNKIE     4 /* PHY Link Change Interrupt Enable bit */

#define PHIR        0x13 /* PHY Interrupt Request (Flag) Register */

    /* PHIR flags */
    #define PHIR_PGIF       2 /* PHY Global Interrupt Flag bit */
    #define PHIR_PLNKIF     4 /* PHY Link Change Interrupt Flag bit */

#define PHLCON      0x14 /* PHY LED Control Register */

    /* PHLCON flags */
    #define PHLCON_STRCH    1 /* LED Pulse Stretching Enable bit */
    #define PHLCON_LFRQ0    2 /* LED Pulse Stretch Time Configuration bit 0 */
    #define PHLCON_LFRQ1    3 /* LED Pulse Stretch Time Configuration bit 1 */
    #define PHLCON_LBCFG0   4 /* LEDB Configuration bit 0 */
    #define PHLCON_LBCFG1   5 /* LEDB Configuration bit 1 */
    #define PHLCON_LBCFG2   6 /* LEDB Configuration bit 2 */
    #define PHLCON_LBCFG3   7 /* LEDB Configuration bit 3 */
    #define PHLCON_LACFG0   8 /* LEDA Configuration bit 0 */
    #define PHLCON_LACFG1   9 /* LEDA Configuration bit 1 */
    #define PHLCON_LACFG2   10 /* LEDA Configuration bit 2 */
    #define PHLCON_LACFG3   11 /* LEDA Configuration bit 3 */

/* Transmit frame control bits */
#define POVERRIDE   0
#define PCRCEN      1
#define PPADEN      2
#define PHUGEEN     3

/* Duplex Mode */
#define MODE_FDPX   0
#define MODE_HDPX   1

extern void enc28j60_init(int mode, mac_addr_t *addr);
extern uint8_t enc28j60_get_revision(void);
extern void enc28j60_set_mac(mac_addr_t *addr);
extern void enc28j60_get_mac(mac_addr_t *addr);
extern int enc28j60_link_up(void);
extern int enc28j60_frame_count(void);
extern uint16_t enc28j60_free_space(void);
extern int enc28j60_send(eth_frame_t *frame);
#endif 
