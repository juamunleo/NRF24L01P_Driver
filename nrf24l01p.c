/*
 * File:   nrf24l01p.c
 * Author: Juamunleo
 *
 * Created on September 19, 2022, 7:21 PM
 */



#include "nrf24l01p.h"

void set_config(bool rx_int_irq, bool tx_int_irq, bool max_retransmits_irq, bool enable_crc, bool crc_encoding, bool power_up, bool rx_state){
    uint8_bits_t config_reg;
    config_reg.b7 = 0;
    config_reg.b6 = rx_int_irq;
    config_reg.b5 = tx_int_irq;
    config_reg.b4 = max_retransmits_irq;
    config_reg.b3 = enable_crc;
    config_reg.b2 = crc_encoding;
    config_reg.b1 = power_up;
    config_reg.b0 = rx_state;
    
    SPI_ON();
    SPI_EXCHANGE_BYTE(W_REGISTER | NRF_CONFIG);
    SPI_EXCHANGE_BYTE(config_reg.byte);
    SPI_OFF();
}