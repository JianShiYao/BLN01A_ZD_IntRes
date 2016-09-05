// HvM.h
#ifndef HVM_B_H
#define HVM_B_H

#include "GeneralTypeDef.h"
#include "Version_Type.h" 
#include "HvM_Macro.h" 

/*
 * Module Version Define 
 */
#define MODULE_HVM_ID               21
#define MODULE_HVM_NAME             "HVM-B"  //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define HVM_SW_MAJOR_VERSION        1      //  size is uByte,max number is 255                                            
#define HVM_SW_MINOR_VERSION        1      //  size is uWord,max number is 65535                                           
#define HVM_SW_REVISION_VERSION     0      //  size is uWord,max number is 65535                                               
#define HVM_DEVELOP_STATUS          "" /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */

typedef union
{
    uWord wd;

    struct
    {
        uByte SumVolt       : 1;
        uByte BmsCanErr     : 1;
        uByte MinVolt       : 1;
        uByte IsoBat        : 1;

        uByte IsoNeg        : 1;
        uByte IsoPos        : 1;
        uByte NegPaste      : 1;
        uByte NegInvalid    : 1;

        uByte PrePaste      : 1;
        uByte PreInvalid    : 1;
        uByte PosPaste      : 1;
        uByte PosInvalid    : 1;

        uByte PreCircuitOff : 1;
        uByte LoadShort     : 1;
        uByte LoadOff       : 1;
        uByte ChgLink       : 1;
    } bit;

}uHvM_ErrCodeType;

typedef struct
{
    uHvM_ErrCodeType code;
}
sHvM_ErrType;

typedef struct
{
    uByte Cmd;
    uByte Life;
    uWord VcuSumV;
    uByte KeySt;
    uByte KmLock;
    uWord Speed;
}sHvM_VcuInfoType;


//extern sHvM_VcuInfoType HvM_VcuInfo;
//extern sHvM_ErrType     HvM_Err;

extern void HvM_ModuleCbk(void);
extern void HvM_ModuleCountCbk(void);
extern void HvM_UpdateVcuInfo(sHvM_VcuInfoType *p_vcu);
extern ModuleID_Type HvM_B_GetVesionModuleVer(sVersion_CodeType * VerPtr);
         

#endif /* HVM_H */

