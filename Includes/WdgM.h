// WdgM.h
#ifndef WDGM_H
#define WDGM_H 

#include "WdgIf.h"

void Wdgm_Init(void);
void Wdgm_MainTrig(void);

//#define Wdgm_Setmode WdgIf_Setmode 
//#define Wdgm_Test WdgIf_Test 
#define Wdgm_Single_trig WdgIf_Trig    

void Wdgm_CountCbk(void);     

#endif /* WDGIF_H */