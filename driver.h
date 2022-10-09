/* 
 * File:   controller.h
 * Author: Juan Manuel
 *
 * Created on 29 de septiembre de 2022, 20:04
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "nrf24l01p.h"
   
static NRF_CONFIG_R NRF_CONFIG;

static EN_AA_R EN_AA;

static EN_RXADDR_R EN_RXADDR;

static SETUP_AW_R SETUP_AW;

static SETUP_RETR_R SETUP_RETR;

static RF_CH_R RF_CH;

static RF_SETUP_R RF_SETUP;

static STATUS_R NRF_STATUS;

static OBSERVE_TX_R OBSERVE_TX;

static RPD_R RPD;

static RX_ADDR_P0_R RX_ADDR_P0;

static RX_ADDR_P1_R RX_ADDR_P1;

static uint8_t RX_ADDR_P2;

static uint8_t RX_ADDR_P3;

static uint8_t RX_ADDR_P4;

static uint8_t RX_ADDR_P5;

static TX_ADDR_R TX_ADDR;

static RX_PW_P0_R RX_PW_P0;

static RX_PW_P1_R RX_PW_P1;

static RX_PW_P2_R RX_PW_P2;

static RX_PW_P3_R RX_PW_P3;

static RX_PW_P4_R RX_PW_P4;

static RX_PW_P5_R RX_PW_P5;

static FIFO_STATUS_R FIFO_STATUS;

static DYNPD_R DYNPD;

static FEATURE_R FEATURE;

void radio_power_up(void);
void radio_init(enum radioMode_t mode);
Payload_t initPayload(void);
void sendBytes(Payload_t payloadInfo);
Payload_t receiveBytes(uint8_t size);
bool checkFIFO(void);
void checkAll(void);

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLLER_H */

