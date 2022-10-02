#include "nrf24l01p.h"

void R_Register(uint8_t register_address, DataBytes_t * data_bytes){
    uint8_t i;
    
    SPI_ON();
    SPI_EXCHANGE_BYTE(R_REGISTER | register_address);
    for(i = 0;i < data_bytes->data_size;i++){
        data_bytes->bytes[i] = SPI_EXCHANGE_BYTE(0xFF);
    }
    SPI_OFF();
}

void W_Register(uint8_t register_address, DataBytes_t data_bytes){
    uint8_t i;
    
    SPI_ON();
    SPI_EXCHANGE_BYTE(W_REGISTER | register_address);
    for(i=0;i<data_bytes.data_size;i++){
         SPI_EXCHANGE_BYTE(data_bytes.bytes[i]);
    }
    SPI_OFF();
}