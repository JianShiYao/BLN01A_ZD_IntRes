#ifndef IOCIF_H
#define IOCIF_H

#include "Ioc_Lcfg.h"
#if ((ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BCU_D))

GeneralReturnType IocIf_Init(void);
GeneralReturnType IocIf_GetIocValue(uByte IocIf_Id,uWord *IocIf_PeriodValuePtr,uByte *IocIf_RatioValuePtr);
GeneralReturnType IocIf_Enable(uByte IocIf_Id);
GeneralReturnType IocIf_Disable(uByte IocIf_Id);
GeneralReturnType IocIf_EnableEvent(uByte IocIf_Id);
GeneralReturnType IocIf_DisableEvent(uByte IocIf_Id);
void IocIf_Task(uByte IocIf_Id);

#endif
#endif /* IOCIF_H */