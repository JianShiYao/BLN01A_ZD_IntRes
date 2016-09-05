#include "IntCan.h"
#include "BatterySt.h"
#include "CarCan.h"
#include "CellvIf.h"
#define FLAG_ENABLE 1
#define FLAG_DISABLE 0
//extern uWord app_request_boot;
#if((M_BCU_D == ECU_CATEGORY) || (M_BCU_C == ECU_CATEGORY))
void IntCan_AddTestData(void)
{
    uByte msg_data1[8],msg1_send_en;
    uByte msg_data2[8],msg2_send_en;
    
    msg1_send_en = FLAG_DISABLE;
    msg2_send_en = FLAG_DISABLE;
    
    msg_data1[0] = 0;//(uByte)(app_request_boot >> 8);
    msg_data1[1] = 0;//(uByte)(app_request_boot);
    msg_data1[2] = 0;//(uByte)(glwd_Cnt1 >> 8);
    msg_data1[3] = 0;//(uByte)(glwd_Cnt1);
    msg_data1[4] = 0;//(uByte)(glwd_Cnt2 >> 8);
    msg_data1[5] = 0;//(uByte)(glwd_Cnt2);
    msg_data1[6] = 0;//(uByte)(glwd_Cnt3 >> 8);
    msg_data1[7] = 0;//(uByte)(glwd_Cnt3 );
    
    msg_data2[0] = 0;//(uByte)(glwd_Cnt4 >> 8);
    msg_data2[1] = 0;//(uByte)(glwd_Cnt4);
    msg_data2[2] = 0;//(uByte)(glwd_Cnt5 >> 24);
    msg_data2[3] = 0;//(uByte)(glwd_Cnt5 >> 16);
    msg_data2[4] = 0;//(uByte)(glwd_Cnt5 >> 8);
    msg_data2[5] = 0;//(uByte)(glwd_Cnt5);
    msg_data2[6] = 0;
    msg_data2[7] = 0; 
       
    IntCan_WrTestFrameToBuff(1, &msg_data1[0], msg1_send_en);
    IntCan_WrTestFrameToBuff(2, &msg_data2[0], msg2_send_en);
}
#endif