// SOF.h
#ifndef SOF_H
#define SOF_H

#include "SOF_Macro.h" 
#include "Version_Type.h" 

extern void SOF_Init(void);
extern void SOF_MainCountCbk(void);
extern void SOF_MainCbk(void);
extern ModuleID_Type Sof_GetVesionModuleVer(sVersion_CodeType * VerPtr);

#endif /* SOF_H */