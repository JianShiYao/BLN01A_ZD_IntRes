#ifndef INTCAN_STATICSET_H
#define INTCAN_STATICSET_H

#include "Ecu.h" 
#include "EcuConf.h"
#include "GeneralTypeDef.h"
#include "BatterySt.h"

// define for IntCan baudrate
#define INT_CAN_BAUDRATE CANIF_BAUDRATE_500K

#if((M_BCU_C == ECU_CATEGORY) || (M_BCU_D == ECU_CATEGORY)) 

// define for self define AH thrhd
#define AH_SELF_DEFINE_EN FLAG_DISABLE
#define AH_SELF_DEFINE 168

// define for sumv typed display on pc
#define SUMV_TYPE INT_SUMV

// define TestFrame cycle
#define TEST_FRAME1_CYCLE 1000 //ms
#define TEST_FRAME2_CYCLE 1000

// define for self config receive msg 
#define SELF_RECEIVE_MSG_EN  FLAG_DISABLE
#define SELF_RECV_MSG0_ID    0x401803e
#define SELF_RECV_MSG1_ID    0x402803e
#define SELF_RECV_MSG2_ID    0x403803e
#endif

#if(M_BMU == ECU_CATEGORY) 
// define for self config Bmu no
#define SELF_DEF_BMU_NO_EN FLAG_DISABLE
#define SELF_DEF_BMU_NO    255
#endif
typedef struct
{
    uByte CanBaudrate;      // config baudrate 
    
#if((M_BCU_C == ECU_CATEGORY) || (M_BCU_D == ECU_CATEGORY))    
    uByte AhThrhdSelfDefEn; // self config AH_Thrhd
    uWord AhThrhd;
    eBat_SumvType SumVType; 
    uWord TestFrame1Cycle;
    uWord TestFrame2Cycle;
    
    uByte SelfRecvMsgEn;
    uLWord SelfRecvMsg0Id;
    uLWord SelfRecvMsg1Id;
    uLWord SelfRecvMsg2Id;
#endif

#if(M_BMU == ECU_CATEGORY)    
    uByte SelfDefBumNoEn;   // self cofig BmuNoEn
    uByte SelfDefBumNo;
#endif     
    
}sIntCan_StaticSetType;

extern const sIntCan_StaticSetType IntCan_StaticSet;

#endif                               