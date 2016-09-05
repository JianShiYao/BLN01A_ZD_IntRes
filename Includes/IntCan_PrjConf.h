#ifndef INTCAN_STATICSET_H
#define INTCAN_STATICSET_H

#include "Ecu.h" 
#include "EcuConf.h"
#include "GeneralTypeDef.h"

// define for IntCan baudrate
#define INT_CAN_BAUDRATE CANIF_BAUDRATE_500K

typedef struct
{
    uByte CanBaudrate;
    
}sIntCan_PrjConfType;

extern const sIntCan_PrjConfType IntCan_PrjConf;

void IntCan_RecvMsgCbk(sCanIf_MsgType msg);
#endif