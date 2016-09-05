#ifndef ISO_LCFG_H
#define ISO_LCFG_H

#include "IsoIf_Type.h"
                                        
//extern const ISO_ControlType ISO_Control[];
//extern const ISO_ValueType  ISO_Value[]; 
extern const sIso_HandleType Iso_Handle;
   
#define GET_ISOPROPERTY(Iso_Id) \
 (Iso_Handle.Iso_PropertyPtr + Iso_Id)  //get the property pointer

#define GET_ISOOPERATION(Iso_Id) \
 (Iso_Handle.Iso_OperationPtr + Iso_Id)  //get the property pointer 

#endif /* ISO_LCFG_H */