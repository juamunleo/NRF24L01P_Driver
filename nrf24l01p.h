/* 
 * File:   nrf24l01p.h
 * Author: Juamunleo
 *
 * Created on September 19, 2022, 7:22 PM
 */

#ifndef NRF24L01P_H
#define	NRF24L01P_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"

#define SPI_ON CSN_SetLow
#define SPI_OFF CSN_SetHigh
#define CE_HIGH CE_SetHigh
#define CE_LOW CE_SetLow
#define SPI_EXCHANGE_BYTE SPI_ExchangeByte

    
//Register Map Address
#define NRF_CONFIG  0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define NRF_STATUS  0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17
#define DYNPD       0x1C
#define FEATURE     0x1D
    
//-- Mnemonics --
//Bit
#define MASK_RX_DR  0b01000000
#define MASK_TX_DS  0b00100000
#define MASK_MAX_RT 0b00010000
#define EN_CRC      0b00001000
#define CRCO        0b00000100
#define PWR_UP      0b00000010
#define PRIM_RX     0b00000001
#define ENAA_P5     0b00100000
#define ENAA_P4     0b00010000
#define ENAA_P3     0b00001000
#define ENAA_P2     0b00000100
#define ENAA_P1     0b00000010
#define ENAA_P0     0b00000001
#define ERX_P5      0b00100000
#define ERX_P4      0b00010000
#define ERX_P3      0b00001000
#define ERX_P2      0b00000100
#define ERX_P1      0b00000010
#define ERX_P0      0b00000001
#define AW          0b00000011
#define ARD         0b00010000
#define ARC         0b00000001
#define PLL_LOCK    0b00010000
#define CONT_WAVE   0b10000000
#define RF_DR       0b00001000
#define RF_PWR      0b00000100
#define RX_DR       0b00000100
#define TX_DS       0b00100000
#define MAX_RT      0b00010000
#define RX_P_NO     0b00000010
#define TX_FULL     0b00000001
#define PLOS_CNT    0b00010000
#define ARC_CNT     0b00000001
#define TX_REUSE    0b00000100
#define FIFO_FULL   0b00100000
#define TX_EMPTY    0b00010000
#define RX_FULL     0b00000010
#define RX_EMPTY    0b00000001
#define DPL_P5      0b00100000
#define DPL_P4      0b00010000
#define DPL_P3      0b00001000
#define DPL_P2      0b00000100
#define DPL_P1      0b00000010
#define DPL_P0      0b00000001
#define EN_DPL      0b00000100
#define EN_ACK_PAY  0b00000010
#define EN_DYN_ACK  0b00000001
    
//Instruction
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NRF_NOP      0xFF
    
typedef union {
    struct {
        unsigned b0:1;
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned b6:1;
        unsigned b7:1;
    };
    uint8_t byte;
}uint8_bits_t;

void set_config(bool rx_int_irq, bool tx_int_irq, bool max_retransmits_irq, bool enable_crc, bool crc_encoding, bool power_up, bool rx_state);

#ifdef	__cplusplus
}
#endif

#endif	/* NRF24L01P_H */

