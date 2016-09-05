#ifndef ISODET_GAIN_H        /*prevent duplicated includes*/
#define ISODET_GAIN_H

#define ISO_ERR100  /*100次/V*/
//#define ISO_ERR200  /*200次/V*/

#define ISODET_GAIN_H

#include "GeneralTypeDef.h"

#define SUMV_PNTS       24
#define LEVEL_PNTS      2

#ifdef ISO_ERR200 
   
const uWord IsoDet_CnstSumvArray[SUMV_PNTS] = {250,300,350,370,400,420,440,460,480,500,530,550,
                                               570,600,630,660,700,760,820,900,1100,1330,1840,2500};//unit 0.1v
const uByte IsoDet_CnstErrLevel[LEVEL_PNTS] = {1,2};

const uWord IsoDet_CnstThrehTable[LEVEL_PNTS][SUMV_PNTS] =
{
    // LEVEL 500次/V
    {131,108,92,87,80,76,72,69,66,63,59,57,55,52,49,47,44,40,37,33,26,21,14,9}, 
    // LEVEL 200次/V
    {334,277,237,224,207,197,188,179,172,165,155,149,144,136,130,124,116,107,99,89,72,59,42,29}  
};

#endif            

#ifdef ISO_ERR100 

const uWord IsoDet_CnstSumvArray[SUMV_PNTS] = {270,310,380,460,530,570,640,680,720,800,830,
                                               870,910,980,1090,1200,1320,1480,1600,1770,1950,2150,2350,2500};//unit 0.1v
const uByte IsoDet_CnstErrLevel[LEVEL_PNTS] = {1,2};

const uWord IsoDet_CnstThrehTable[LEVEL_PNTS][SUMV_PNTS] =
{
     // LEVEL 500次/V
     {98,89,77,63,56,53,47,41,37,29,26,25,25,19,16,12,10,8,6,5,5,4,3,2},
     // LEVEL 100次/V
     {600,520,420,350,340,337,228,180,154,148,126,117,109,95,76,62,55,42,36,27,22,18,14,11}
};

#endif
#endif