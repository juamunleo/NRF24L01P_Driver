/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16LF1764
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

#include "main.h"
#include "driver.h"

#define RADIO_TX 0
#define RADIO_RX 1
#define RADIO_MODE RADIO_RX
/*
                         Main application
 */
void rx_function(void);
void tx_function(void);
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    SPI_Open(SPI_DEFAULT);    
   
    
#if RADIO_MODE == RADIO_RX
    rx_function();
#else
    tx_function();
#endif
}

#if RADIO_MODE == RADIO_RX
void rx_function(void){
    Payload_t payload;
    uint8_t data, ref = 0, lastRef;
    
    radio_init(RX);
    radio_power_up();
    LED_SetHigh();
    __delay_ms(500);
    LED_SetLow();
    CE_SetHigh();
    while(1){
        if(checkFIFO()){
            payload = receiveBytes(2);
            data = payload.bytes[0];
            ref = payload.bytes[1];
            if(ref != lastRef && data == 0xAA){
                if(RELE_GetValue()){
                    RELE_SetLow();
                }else{
                    RELE_SetHigh();
                }
                lastRef = ref;
            }
            Flush_RX();
        }
    }
}

#else
void tx_function(void){
    uint8_t ref = 1;
    Payload_t payloadInfo = initPayload();
    
    payloadInfo.payload_size = 2;
    payloadInfo.bytes[0] = 0xAA;
    
    radio_init(TX);
    radio_power_up();
    interrupted = false;
    LED_SetHigh();
    __delay_ms(300);
    LED_SetLow();
    
    while(1){
        if(interrupted){
            LED_SetHigh();
            ref++;
            payloadInfo.bytes[1] = ref;
            while(!BUTTON_GetValue()){ 
                sendBytes(payloadInfo);
            }
            interrupted = false;
            LED_SetLow();
            __delay_ms(500);
        }
    }
}
#endif
/**
 End of File
*/
