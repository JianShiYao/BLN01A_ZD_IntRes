// ThM.h
#ifndef THM_H
#define THM_H

#include "GeneralTypeDef.h"
#include "ThM_Macro.h" 
#include "Version_Type.h" 

extern void ThM_Init(void);
extern void ThM_MainCountCbk(void);
extern void ThM_MainCbk(void);
extern ModuleID_Type Thm_GetVesionModuleVer(sVersion_CodeType * VerPtr);

#endif /* THM_H */