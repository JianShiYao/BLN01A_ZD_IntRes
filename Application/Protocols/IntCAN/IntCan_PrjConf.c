
#include "CanIf_Type.h"
#include "Ecu.h" 
#include "EcuConf.h"
#include "GeneralTypeDef.h"
#include "IntCan_PrjConf.h"
#include "GbChgCan.h"

#define FLAG_ENABLE 1
#define FLAG_DISABLE 0

const sIntCan_PrjConfType IntCan_PrjConf = 
{
   INT_CAN_BAUDRATE, 
};

void IntCan_RecvMsgCbk(sCanIf_MsgType msg)
{
    GbChg_RxDataFromCharger(msg);
}


