#ifndef AIIF_H
#define AIIF_H

#include "AiIf_Lcfg.h"

#define  CPU_ADC_ACCURACY 4096//1024 //change for yt24   4096

#define  ADC_VOLT_CRITERION  5000

GeneralReturnType AiIf_MeasureChannel(uByte AiIf_ChannelId,uWord *AiIf_AdValuePtr); 

#endif /* AIIF_H */