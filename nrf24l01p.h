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
    
#define SPI_ON CSN_SetLow
#define SPI_OFF CSN_SetHigh
#define CE_HIGH CE_SetHigh
#define CE_LOW CE_SetLow
#define SPI_EXCHANGE_BYTE SPI_ExchangeByte

#include "program_types.h"
    
//Register Map Address
#define NRF_CONFIG_ADDR  0x00
#define EN_AA_ADDR       0x01
#define EN_RXADDR_ADDR   0x02
#define SETUP_AW_ADDR    0x03
#define SETUP_RETR_ADDR  0x04
#define RF_CH_ADDR       0x05
#define RF_SETUP_ADDR    0x06
#define NRF_STATUS_ADDR  0x07
#define OBSERVE_TX_ADDR  0x08
#define CD_ADDR          0x09
#define RX_ADDR_P0_ADDR  0x0A
#define RX_ADDR_P1_ADDR  0x0B
#define RX_ADDR_P2_ADDR  0x0C
#define RX_ADDR_P3_ADDR  0x0D
#define RX_ADDR_P4_ADDR  0x0E
#define RX_ADDR_P5_ADDR  0x0F
#define TX_ADDR_ADDR     0x10
#define RX_PW_P0_ADDR    0x11
#define RX_PW_P1_ADDR    0x12
#define RX_PW_P2_ADDR    0x13
#define RX_PW_P3_ADDR    0x14
#define RX_PW_P4_ADDR    0x15
#define RX_PW_P5_ADDR    0x16
#define FIFO_STATUS_ADDR 0x17
#define DYNPD_ADDR       0x1C
#define FEATURE_ADDR     0x1D
    
//Instruction
#define R_REGISTER          0x00
#define W_REGISTER          0x20
#define REGISTER_MASK       0x1F
#define ACTIVATE            0x50
#define R_RX_PL_WID         0x60
#define R_RX_PAYLOAD        0x61
#define W_TX_PAYLOAD        0xA0
#define W_ACK_PAYLOAD       0xA8
#define W_TX_PAYLOAD_NO_ACK 0xB0
#define FLUSH_TX            0xE1
#define FLUSH_RX            0xE2
#define REUSE_TX_PL         0xE3
#define NRF_NOP             0xFF

//AW (Address Width) Values
#define AW_3bytes 0b01
#define AW_4bytes 0b10
#define AW_5bytes 0b11

//RF_PWR (Output Power) Values
#define RF_PWR_n18dbm   0b00
#define RF_PWR_n12dbm   0b01
#define RF_PWR_n6dbm    0b10
#define RF_PWR_0dbm     0b11
    
    
    enum radioMode_t{TX,RX};
    
    void R_Register(uint8_t register_address, DataBytes_t * data_bytes);
    void W_Register(uint8_t register_address, DataBytes_t data_bytes);
    void R_RX_Payload(Payload_t * payload_info);
    void W_TX_Payload(Payload_t payload_info);
    void Flush_TX(void);
    void Flush_RX(void);
    void Reuse_TX_PL(void);
    uint8_t R_RX_PL_Wid(void);
    void W_ACK_Payload(uint8_t pipe, Payload_t payload_info);
    void W_TX_Payload_NO_ACK(Payload_t payload_info);
    void nRF_NOP(void);
    void Activate(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* NRF24L01P_H */

