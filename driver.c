#include "driver.h"
#include "mcc_generated_files/mcc.h"
#include <stdarg.h>

Radio_t radio_init(void){
    Radio_t radio;
    DataBytes_t data_bytes;
    
    //CONFIG
    radio.NRF_CONFIG.EN_CRC = 1;
    radio.NRF_CONFIG.CRCO = 1;
    
    //EN_AA
    radio.EN_AA.ENAA_P0 = 1;
    radio.EN_AA.ENAA_P1 = 1;
    radio.EN_AA.ENAA_P2 = 1;
    radio.EN_AA.ENAA_P3 = 1;
    radio.EN_AA.ENAA_P4 = 1;
    radio.EN_AA.ENAA_P5 = 1;
    
    //EN_RXADDR
    radio.EN_RXADDR.ERX_P0 = 1;
    radio.EN_RXADDR.ERX_P1 = 1;
    
    //SETUP_AW
    radio.SETUP_AW.AW = AW_5bytes;
    
    //SETUP_RETR
    radio.SETUP_RETR.ARC = 0xF;
    radio.SETUP_RETR.ARD = 0x5;
    
    //RF_SETUP
    radio.RF_SETUP.RF_DR_HIGH = 1;
    radio.RF_SETUP.RF_PWR = RF_PWR_0dbm;
    
    //Initialize config register
    data_bytes.bytes[0] = radio.NRF_CONFIG.byte;
    data_bytes.data_size = 1;
    
    W_Register(NRF_CONFIG_ADDR, data_bytes);
    
    //Initialize RETR
    data_bytes.bytes[0] = radio.SETUP_RETR.byte;
    data_bytes.data_size = 1;
    
    W_Register(SETUP_RETR_ADDR, data_bytes);
    
    radio_setChannel(&radio, 2);
    
    Activate();
    
    Flush_RX();
    
    Flush_TX();
    
    return radio;
}

void radio_openWritingPipe(Radio_t * radio, DataBytes_t address){
    if(address.data_size > 0){
        radio->TX_ADDR.address_0 = address.bytes[0];
        radio->TX_ADDR.address_1 = address.bytes[1];
        radio->TX_ADDR.address_2 = address.bytes[2];
        radio->TX_ADDR.address_3 = address.bytes[3];
        radio->TX_ADDR.address_4 = address.bytes[4];
        W_Register(TX_ADDR_ADDR, address);
    }
}

void radio_openReadingPipe(Radio_t * radio, uint8_t pipe, uint8_t bytesToReceive, DataBytes_t address){
    if(address.data_size > 0 && pipe < 6 && bytesToReceive < 33){
        switch(pipe){
            case 0:
                radio->RX_ADDR_P0.address_0 = address.bytes[0];
                radio->RX_ADDR_P0.address_1 = address.bytes[1];
                radio->RX_ADDR_P0.address_2 = address.bytes[2];
                radio->RX_ADDR_P0.address_3 = address.bytes[3];
                radio->RX_ADDR_P0.address_4 = address.bytes[4];
                radio->RX_PW_P0.RX_PW_P0 = bytesToReceive;
                break;
            case 1:
                radio->RX_ADDR_P1.address_0 = address.bytes[0];
                radio->RX_ADDR_P1.address_1 = address.bytes[1];
                radio->RX_ADDR_P1.address_2 = address.bytes[2];
                radio->RX_ADDR_P1.address_3 = address.bytes[3];
                radio->RX_ADDR_P1.address_4 = address.bytes[4];
                radio->RX_PW_P1.RX_PW_P1 = bytesToReceive;
                break;
                
            case 2:
                radio->RX_ADDR_P2 = address.bytes[0];
                radio->RX_PW_P2.RX_PW_P2 = bytesToReceive;
                break;
                
            case 3:
                radio->RX_ADDR_P3 = address.bytes[0];
                radio->RX_PW_P3.RX_PW_P3 = bytesToReceive;
                break;
            
            case 4: 
                radio->RX_ADDR_P4 = address.bytes[0];
                radio->RX_PW_P4.RX_PW_P4 = bytesToReceive;
                break;
            
            case 5:
                radio->RX_ADDR_P5 = address.bytes[0];
                radio->RX_PW_P5.RX_PW_P5 = bytesToReceive;
                break;
                
            default:
                break;
        }
        W_Register(RX_ADDR_P0_ADDR + pipe, address);
        W_Register(RX_PW_P0_ADDR + pipe, initDataBytes(1,bytesToReceive));
    }
}

void radio_setChannel(Radio_t * radio, uint8_t channel){
    if(channel < 128){
        radio->RF_CH.RF_CH = channel;
        W_Register(RF_CH_ADDR, initDataBytes(1, channel));
    }
}

void radio_startRx(Radio_t * radio){
    if(radio->NRF_CONFIG.PRIM_RX != RX){
        radio->NRF_CONFIG.PRIM_RX = RX;
        W_Register(NRF_CONFIG_ADDR, initDataBytes(1, radio->NRF_CONFIG.byte));
    }
    CE_HIGH();
}

static void radio_startTx(Radio_t * radio){
    if(radio->NRF_CONFIG.PRIM_RX != TX){
        radio->NRF_CONFIG.PRIM_RX = TX;
        W_Register(NRF_CONFIG_ADDR, initDataBytes(1, radio->NRF_CONFIG.byte));
    }
    CE_HIGH();
}

void radio_powerUp(Radio_t * radio){
    DataBytes_t data_bytes;
    
    radio->NRF_CONFIG.PWR_UP = 1;
    data_bytes.bytes[0] = radio->NRF_CONFIG.byte;
    data_bytes.data_size = 1;
    
    W_Register(NRF_CONFIG_ADDR, data_bytes);
}

void sendBytes(Radio_t * radio, Payload_t payloadInfo){
    DataBytes_t dataBytes = initDataBytes(1, 0x70);
    
    //Send Data
    W_TX_Payload_NO_ACK(payloadInfo);
    radio_startTx(radio);
    __delay_us(100);
    CE_LOW();
    
    //Clear interrupts
    W_Register(NRF_STATUS_ADDR, dataBytes);
    
    Flush_TX();
}

Payload_t receiveBytes(uint8_t size){
    Payload_t payloadInfo = initPayload(0);
    
    if(size > 0){
        payloadInfo.payload_size = size;
        R_RX_Payload(&payloadInfo);
    }
    
    Flush_RX();
    return payloadInfo;
}

bool checkFIFO(Radio_t * radio){
    bool data_exists = false;
    DataBytes_t data_bytes = initDataBytes(0);
    
    data_bytes.data_size = 1;
    
    R_Register(FIFO_STATUS_ADDR, &data_bytes);
    
    radio->FIFO_STATUS.byte = data_bytes.bytes[0];
    if(!radio->FIFO_STATUS.RX_EMPTY){
        data_exists = true;
    }
    
    return data_exists;
}

void 

Payload_t initPayload(uint8_t size, ...){
    Payload_t payload = {{0x00}, 0x00};
    payload.payload_size = size < 33?size:32;
    
    if(size > 0){
        va_list arguments;
        va_start(arguments, size);
        for(uint8_t i = 0;i<payload.payload_size;i++){
            payload.bytes[i] = va_arg(arguments, uint8_t);
        }
        va_end(arguments);
    }
    return payload;
}

DataBytes_t initDataBytes(uint8_t size, ...){
    DataBytes_t dataBytes = {{0x00}, 0x00};
    dataBytes.data_size = size < 6?size:5;
    
    if(size > 0){
        va_list arguments;
        va_start(arguments, size);
        for(uint8_t i = 0;i<dataBytes.data_size;i++){
            dataBytes.bytes[i] = va_arg(arguments, uint8_t);
        }
        va_end(arguments);
    }
    return dataBytes;
}