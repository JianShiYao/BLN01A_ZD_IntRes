// ChgM.h
#ifndef CHGM_H
#define CHGM_H

#include "ChgM_Macro.h"
#include "Version_Type.h"


extern void ChgM_Init(void);
extern void ChgM_MainCountCbk(void);
extern void ChgM_MainCbk(void);
extern ModuleID_Type ChgM_GetVesionModuleVer(sVersion_CodeType * VerPtr);


#endif /* CHGM_H */
