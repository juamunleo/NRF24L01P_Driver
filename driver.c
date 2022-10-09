#include "driver.h"
#include "mcc_generated_files/spi.h"

void radio_init(enum radioMode_t mode){
    DataBytes_t data_bytes;
    
    //CONFIG
    NRF_CONFIG.EN_CRC = 1;
    NRF_CONFIG.CRCO = 1;
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
    SETUP_RETR.ARC = 0xF;
    SETUP_RETR.ARD = 0x5;
    
    //RF_CH
    RF_CH.RF_CH = 5;
    
    //RF_SETUP
    RF_SETUP.RF_DR_HIGH = 1;
    RF_SETUP.RF_PWR = RF_PWR_0dbm;
    
    //RX_ADDR_P0
    RX_ADDR_P0.address_0 = 0xEF;
    RX_ADDR_P0.address_1 = 0xAB;
    RX_ADDR_P0.address_2 = 0xC8;
    RX_ADDR_P0.address_3 = 0xF3;
    RX_ADDR_P0.address_4 = 0xD7;
    
    //TX_ADDR
    TX_ADDR.address_0 = 0xEF;
    TX_ADDR.address_1 = 0xAB;
    TX_ADDR.address_2 = 0xC8;
    TX_ADDR.address_3 = 0xF3;
    TX_ADDR.address_4 = 0xD7;
    
    //Initialize config register
    data_bytes.bytes[0] = NRF_CONFIG.byte;
    data_bytes.data_size = 1;
    
    W_Register(NRF_CONFIG_ADDR, data_bytes);
    
    //Initialize RETR
    data_bytes.bytes[0] = SETUP_RETR.byte;
    data_bytes.data_size = 1;
    
    W_Register(SETUP_RETR_ADDR, data_bytes);
    
    //Initialize channel
    data_bytes.bytes[0] = RF_CH.byte;
    data_bytes.data_size = 1;
    
    W_Register(RF_CH_ADDR, data_bytes);
    
    
    //Initialize RX pipe 0
    data_bytes.bytes[0] = RX_ADDR_P0.address_0;
    data_bytes.bytes[1] = RX_ADDR_P0.address_1;
    data_bytes.bytes[2] = RX_ADDR_P0.address_2;
    data_bytes.bytes[3] = RX_ADDR_P0.address_3;
    data_bytes.bytes[4] = RX_ADDR_P0.address_4;
    data_bytes.data_size = 5;
    
    W_Register(RX_ADDR_P0_ADDR, data_bytes);
    
    //Initialize TX pipe
    data_bytes.bytes[0] = TX_ADDR.address_0;
    data_bytes.bytes[1] = TX_ADDR.address_1;
    data_bytes.bytes[2] = TX_ADDR.address_2;
    data_bytes.bytes[3] = TX_ADDR.address_3;
    data_bytes.bytes[4] = TX_ADDR.address_4;
    data_bytes.data_size = 5;
    
    W_Register(TX_ADDR_ADDR, data_bytes);

    Activate();
    
    RX_PW_P0.RX_PW_P0 = 2;
    
    data_bytes.bytes[0] = RX_PW_P0.byte;
    data_bytes.data_size = 1;
    
    W_Register(RX_PW_P0_ADDR, data_bytes);
    
    Flush_RX();
    
    Flush_TX();
}

void radio_power_up(void){
    DataBytes_t data_bytes;
    
    NRF_CONFIG.PWR_UP = 1;
    data_bytes.bytes[0] = NRF_CONFIG.byte;
    data_bytes.data_size = 1;
    
    W_Register(NRF_CONFIG_ADDR, data_bytes);
}

Payload_t initPayload(void){
    Payload_t payload;
    for(uint8_t i = 0;i<32;i++){
        payload.bytes[i] = 0x00;
    }
    return payload;
}

void sendBytes(Payload_t payloadInfo){
    DataBytes_t dataBytes;
    
    //Send Data
    W_TX_Payload_NO_ACK(payloadInfo);
    
    CE_SetHigh();
    __delay_us(100);
    CE_SetLow();    
    
    //Clear interrupts
    dataBytes.bytes[0] = 0x70;
    dataBytes.data_size = 1;
    W_Register(NRF_STATUS_ADDR, dataBytes);
    
    Flush_TX();
}

Payload_t receiveBytes(uint8_t size){
    Payload_t payloadInfo;
    if(size > 0){
        payloadInfo.payload_size = size;
        R_RX_Payload(&payloadInfo);
    }
    
    return payloadInfo;
}

bool checkFIFO(void){
    bool data_exists = false;
    DataBytes_t data_bytes;
    
    data_bytes.data_size = 1;
    
    R_Register(FIFO_STATUS_ADDR, &data_bytes);
    
    FIFO_STATUS.byte = data_bytes.bytes[0];
    if(!FIFO_STATUS.RX_EMPTY){
        data_exists = true;
    }
    
    return data_exists;
}

void checkAll(void){
    DataBytes_t data_bytes = {{0x00,0x00,0x00,0x00,0x00}, 0x00};
    data_bytes.data_size = 1;
    R_Register(NRF_CONFIG_ADDR, &data_bytes);
    R_Register(EN_AA_ADDR, &data_bytes);
    R_Register(EN_RXADDR_ADDR, &data_bytes);
    R_Register(SETUP_AW_ADDR, &data_bytes);
    R_Register(SETUP_RETR_ADDR, &data_bytes);
    R_Register(RF_CH_ADDR, &data_bytes);
    R_Register(RF_SETUP_ADDR, &data_bytes);
    R_Register(NRF_STATUS_ADDR, &data_bytes);
    R_Register(OBSERVE_TX_ADDR, &data_bytes);
    R_Register(CD_ADDR, &data_bytes);
    data_bytes.data_size = 5;
    R_Register(RX_ADDR_P0_ADDR, &data_bytes);
    R_Register(RX_ADDR_P1_ADDR, &data_bytes);
    data_bytes.data_size = 1;
    R_Register(RX_ADDR_P2_ADDR, &data_bytes);
    R_Register(RX_ADDR_P3_ADDR, &data_bytes);
    R_Register(RX_ADDR_P4_ADDR, &data_bytes);
    R_Register(RX_ADDR_P5_ADDR, &data_bytes);
    data_bytes.data_size = 5;
    R_Register(TX_ADDR_ADDR, &data_bytes);
    data_bytes.data_size = 1;
    R_Register(RX_PW_P0_ADDR, &data_bytes);
    R_Register(RX_PW_P1_ADDR, &data_bytes);
    R_Register(RX_PW_P2_ADDR, &data_bytes);
    R_Register(RX_PW_P3_ADDR, &data_bytes);
    R_Register(RX_PW_P4_ADDR, &data_bytes);
    R_Register(RX_PW_P5_ADDR, &data_bytes);
    R_Register(FIFO_STATUS_ADDR, &data_bytes);
    R_Register(DYNPD_ADDR, &data_bytes);
    R_Register(FEATURE_ADDR, &data_bytes);
}

