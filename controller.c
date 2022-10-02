#include "controller.h"

void radio_init(enum radioMode_t mode){
    //NRF_CONFIG
    //NRF_CONFIG.MASK_RX_DR = 0;
    //NRF_CONFIG.MASK_TX_DS = 0;
    //NRF_CONFIG.MASK_MAX_RT = 0;
    NRF_CONFIG.EN_CRC = 1;
    //NRF_CONFIG.CRCO = 0;
    //NRF_CONFIG.PWR_UP = 0;
    NRF_CONFIG.PRIM_RX = mode;
    
    //EN_AA
    EN_AA.ENAA_P0 = 1;
    EN_AA.ENAA_P1 = 1;
    EN_AA.ENAA_P2 = 1;
    EN_AA.ENAA_P3 = 1;
    EN_AA.ENAA_P4 = 1;
    EN_AA.ENAA_P5 = 1;
    
    //EN_RXADDR
    EN_RXADDR.ERX_P0 = 1;
    EN_RXADDR.ERX_P1 = 1;
    
    //SETUP_AW
    SETUP_AW.AW = AW_5bytes;
    
    //SETUP_RETR
    SETUP_RETR.ARC = 3;
    
    //RF_CH
    RF_CH.RF_CH = 2;
    
    //RF_SETUP
    RF_SETUP.RF_DR_HIGH = RF_DR_HIGH_2Mbps;
    RF_SETUP.RF_PWR = RF_PWR_0dbm;
    
    //RX_ADDR_P0
    RX_ADDR_P0.address_0 = 0xE7;
    RX_ADDR_P0.address_1 = 0xE7;
    RX_ADDR_P0.address_2 = 0xE7;
    RX_ADDR_P0.address_3 = 0xE7;
    RX_ADDR_P0.address_4 = 0xE7;
    
    //RX_ADDR_P1
    RX_ADDR_P1.address_0 = 0xC2;
    RX_ADDR_P1.address_1 = 0xC2;
    RX_ADDR_P1.address_2 = 0xC2;
    RX_ADDR_P1.address_3 = 0xC2;
    RX_ADDR_P1.address_4 = 0xC2;
    
    //RX_ADDR_P2
    RX_ADDR_P2 = 0xC3;
    
    //RX_ADDR_P3
    RX_ADDR_P3 = 0xC4;
    
    //RX_ADDR_P4
    RX_ADDR_P3 = 0xC5;
    
    //RX_ADDR_P5
    RX_ADDR_P3 = 0xC6;
    
    //TX_ADDR
    TX_ADDR.address_0 = 0xE7;
    TX_ADDR.address_1 = 0xE7;
    TX_ADDR.address_2 = 0xE7;
    TX_ADDR.address_3 = 0xE7;
    TX_ADDR.address_4 = 0xE7;
}

void radio_power_up(void){
    DataBytes_t data_bytes;
    
    NRF_CONFIG.PWR_UP = 1;
    data_bytes.bytes[0] = NRF_CONFIG.byte;
    data_bytes.data_size = 1;
    W_Register(NRF_CONFIG_ADDR, data_bytes);
}