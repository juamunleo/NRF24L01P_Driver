/* 
 * File:   includes.h
 * Author: Juan Manuel
 *
 * Created on October 2, 2022, 4:17 PM
 */

#ifndef INCLUDES_H
#define	INCLUDES_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"
    
    typedef struct {
        uint8_t bytes[5];
        uint8_t data_size;
    }DataBytes_t;
    
    typedef struct{
        uint8_t bytes[32];
        uint8_t payload_size;
    }Payload_t;
    
    typedef union {
        struct {
            unsigned PRIM_RX:1;
            unsigned PWR_UP:1;
            unsigned CRCO:1;
            unsigned EN_CRC:1;
            unsigned MASK_MAX_RT:1;
            unsigned MASK_TX_DS:1;
            unsigned MASK_RX_DR:1;
            unsigned Reserved:1;
        };
        uint8_t byte;
    }NRF_CONFIG_R;
    
    typedef union {
        struct {
            unsigned ENAA_P0:1;
            unsigned ENAA_P1:1;
            unsigned ENAA_P2:1;
            unsigned ENAA_P3:1;
            unsigned ENAA_P4:1;
            unsigned ENAA_P5:1;
            unsigned reserved:2;
        };
        uint8_t byte;
    }EN_AA_R;
    
    typedef union {
        struct {
            unsigned ERX_P0:1;
            unsigned ERX_P1:1;
            unsigned ERX_P2:1;
            unsigned ERX_P3:1;
            unsigned ERX_P4:1;
            unsigned ERX_P5:1;
            unsigned Reserved:2;
        };
        uint8_t byte;
    }EN_RXADDR_R;
    
    typedef union {
        struct {
            unsigned AW:2;
            unsigned Reserved:6;
        };
        uint8_t byte;
    }SETUP_AW_R;
    
    typedef union {
        struct {
            unsigned ARC:4;
            unsigned ARD:4;
        };
        uint8_t byte;
    }SETUP_RETR_R;
    
    typedef union {
        struct {
            unsigned RF_CH:7;
            unsigned Reserved:1;
        };
        uint8_t byte;
    }RF_CH_R;
    
    typedef union {
        struct {
            unsigned Obsolete:1;
            unsigned RF_PWR:2;
            unsigned RF_DR_HIGH:1;
            unsigned PLL_LOCK:1;
            unsigned RF_DR_LOW:1;
            unsigned Reserved:1;
            unsigned CONT_WAVE:1;
        };
        uint8_t byte;
    }RF_SETUP_R;
    
        
    typedef union {
        struct {
            unsigned TX_FULL:1;
            unsigned RX_P_NO:3;
            unsigned MAX_RT:1;
            unsigned TX_DS:1;
            unsigned RX_DR:1;
            unsigned Reserved:1;
        };
        uint8_t byte;
    }STATUS_R;
    
    typedef union {
        struct {
            unsigned ARC_CNT:4;
            unsigned PLOS_CNT:4;
        };
        uint8_t byte;
    }OBSERVE_TX_R;
    
    typedef union {
        struct {
            unsigned RPD:1;
            unsigned Reserved:7;
        };
        uint8_t byte;
    }RPD_R;
    
    typedef struct{
        uint8_t address_0;
        uint8_t address_1;
        uint8_t address_2;
        uint8_t address_3;
        uint8_t address_4;
    }RX_ADDR_P0_R;
    
    typedef struct{
        uint8_t address_0;
        uint8_t address_1;
        uint8_t address_2;
        uint8_t address_3;
        uint8_t address_4;
    }RX_ADDR_P1_R;
    
    uint8_t RX_ADDR_P2_R;
    
    uint8_t RX_ADDR_P3_R;
    
    uint8_t RX_ADDR_P4_R;
    
    uint8_t RX_ADDR_P5_R;
    
    typedef struct{
        uint8_t address_0;
        uint8_t address_1;
        uint8_t address_2;
        uint8_t address_3;
        uint8_t address_4;
    }TX_ADDR_R;
    
    typedef union {
        struct {
            unsigned RX_PW_P0:6;
            unsigned Reserved:2;
        };
        uint8_t byte;
    }RX_PW_P0_R;    

    typedef union {
        struct {
            unsigned RX_PW_P1:6;
            unsigned Reserved:2;
        };
        uint8_t byte;
    }RX_PW_P1_R;
    
    typedef union {
        struct {
            unsigned RX_PW_P2:6;
            unsigned Reserved:2;
        };
        uint8_t byte;
    }RX_PW_P2_R;
    
    typedef union {
        struct {
            unsigned RX_PW_P3:6;
            unsigned Reserved:2;
        };
        uint8_t byte;
    }RX_PW_P3_R;
    
    typedef union {
        struct {
            unsigned RX_PW_P4:6;
            unsigned Reserved:2;
        };
        uint8_t byte;
    }RX_PW_P4_R;
    
    typedef union {
        struct {
            unsigned RX_PW_P5:6;
            unsigned Reserved:2;
        };
        uint8_t byte;
    }RX_PW_P5_R;
       
    typedef union {
        struct {
            unsigned RX_EMPTY:1;
            unsigned RX_FULL:1;
            unsigned Reserved_0:2;
            unsigned TX_EMPTY:1;
            unsigned TX_FULL:1;
            unsigned TX_REUSE:1;
            unsigned Reserved_1:1;
        };
        uint8_t byte;
    }FIFO_STATUS_R;
    
    typedef union {
        struct {
            unsigned DPL_P0:1;
            unsigned DPL_P1:1;
            unsigned DPL_P2:1;
            unsigned DPL_P3:1;
            unsigned DPL_P4:1;
            unsigned DPL_P5:1;
            unsigned Reserved:2;
        };
        uint8_t byte;
    }DYNPD_R;
    
    typedef union {
        struct {
            unsigned EN_DYN_ACK:1;
            unsigned EN_ACK_PAY:1;
            unsigned EN_DPL:1;
            unsigned Reserved:5;
        };
        uint8_t byte;
    }FEATURE_R;

#ifdef	__cplusplus
}
#endif

#endif	/* INCLUDES_H */

