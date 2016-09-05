//EcuConf.h
#ifndef ECUCONF_H
#define ECUCONF_H

#include "EcuDef.h"
#include "GeneralTypeDef.h"
#include "EcuDebug.h"

#include "Version_Type.h"
/*
 * Module Version Define 
 */
#define MODULE_ECUCONF_ID               38 
#define MODULE_ECUCONF_NAME             "ECUCONF"    //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define ECUCONF_SW_MAJOR_VERSION         1     //  size is uByte,max number is 255                                            
#define ECUCONF_SW_MINOR_VERSION         1    //  size is uWord,max number is 65535                                           
#define ECUCONF_SW_REVISION_VERSION      0   //  size is uWord,max number is 65535                                               
#define ECUCONF_DEVELOP_STATUS           "" /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */  
/* Version Module Get Interface */
ModuleID_Type EcuConf_GetVesionModuleVer(sVersion_CodeType * VerPtr); 


/*
 * System topology Config
 */
 
/* typedef enum
 {
   BCU_D,
   BCU_C,
   BMU,
   BMU_R    
 }eEcu_CategoryType; */ //no use
 #define M_BCU_D 0
 #define M_BCU_C 1
 #define M_BMU   2
 #define M_BMU_R 3
 
 /* 0: BCU_D --- Battery Control Unit- Distributed
                          * 1: BCU_C --- Battery Control Unit- Centralized
                          * 2: BMU --- Battery Measurement Unit
                          * 3: BMU_R --- Battery Measurement Unit - Replace 
                          */ 
//#define ECU_CATEGORY 0 // This will be define in EcuDef.h

/*
 * 0: BCU_D --- Battery Control Unit- Distributed 
 */                            
#if (ECU_CATEGORY == 0)   
  /*
   * Module Enable swith define 
   */
  //#define ECU_M_ENABLE_CELLV   /* CellvIf and CellvM Enable switch*/ 
  //#define ECU_M_ENABLE_TEMPER  /* TemperIf and TemperM Enable switch*/ 
  #define ECU_M_ENABLE_SUMV    /* SumvIf and SumvM Enable switch*/ 
  #define ECU_M_ENABLE_CURRENT /* CurrentIf and CurrentM Enable switch*/ 
  #define ECU_M_ENABLE_ISO     /* IsoIf and IsoM Enable switch */
  //#define ECU_M_ENABLE_GBCHGIF   /* GB charge interface Eanble swithc */ //close temp
  
  #define ECU_M_ENABLE_CARCAN   /* car can enable switch*/
  #define ECU_M_ENABLE_CHGCAN   /* charge can enable switch*/
  
  #define ECU_M_ENABLE_SOC      /* soc enable switch */
  #define ECU_M_ENABLE_SOH      /* soh enable switch */
  #define ECU_M_ENABLE_SOF      /* sof enable switch */
  #define ECU_M_ENABLE_INTRES   /* internal resistance enable switch*/
  
  #define ECU_M_ENABLE_CHGM     /* charge manage enable switch */
  #define ECU_M_ENABLE_HVM     /* high-voltage manage enable switch */
  #define ECU_M_ENABLE_SAFTM   /* safe manage enable switch */
  #define ECU_M_ENABLE_GBCHGIF
  
  //#define ECU_M_ENABLE_NTC    /* ntc enable switch */
  
  //#define ECU_M_IOHWAB_PWMIF   /* pwm interface switch */
  /* Default module have no switch */
  /* End of Module Enable swith define */
  
  /*
   *  Configurate for CAN communication
   */ 
  #define CAN_CHANNEL_NUM 3  /* CAN channel number */
  #define MAX_BUFFER_LEN 20  /* CAN buffer length */
  #define CAR_CAN_EN  /* switch for enable car can channel */
  #define CHG_CAN_EN  /* switch for enable charger can channel */
  /* End of Configurate for CAN communication */
  
  /* 
   * Configurate for deal battery date  
   */        
  #define MAX_BMU_NUM 30      /* max bmu number */
    
  #define MAX_CELL_NUM 300     /* max cell number */       
  #define MAX_PACK_NUM  MAX_BMU_NUM /* max pack number,set equal current bmu number*/   
  
  #define MAX_PACK_CELL_NUM   36 /* max cell number in one pack */ 
  #if((MAX_BMU_NUM * MAX_PACK_CELL_NUM) > (30 * 36)) // max permit 1080 cell
  #error "All cell number RAM overflow!"
  #endif
  #if(MAX_BMU_NUM > 30)
  #error "Bmu number overflow!"
  #endif
  #if(MAX_CELL_NUM > 300)
  #error "Max cell num overflow!" 
  #endif
  
  #define MAX_TEMPER_NUM    MAX_CELL_NUM // support detect per cell`s temperature  
  #define MAX_PACK_TEMPER_NUM  MAX_PACK_CELL_NUM 
  /* End of Configurate for deal battery date */
  
#elif (ECU_CATEGORY == 1)
   /* 1: BCU_C --- Battery Control Unit- Centralized */ 
   /*
    * Module Enable swith define 
    */
  #define ECU_M_ENABLE_CELLV   /* CellvIf and CellvM Enable switch*/ 
  #define ECU_M_ENABLE_TEMPER  /* TemperIf and TemperM Enable switch*/ 
  #define ECU_M_ENABLE_SUMV    /* SumvIf and SumvM Enable switch*/ 
  #define ECU_M_ENABLE_CURRENT /* CurrentIf and CurrentM Enable switch*/ 
  #define ECU_M_ENABLE_ISO     /* IsoIf and IsoM Enable switch */
  #define ECU_M_ENABLE_GBCHGIF   /* GB charge interface Eanble swithc */
  
  #define ECU_M_ENABLE_CARCAN   /* car can enable switch*/
  #define ECU_M_ENABLE_CHGCAN   /* charge can enable switch*/
  
  #define ECU_M_ENABLE_SOC      /* soc enable switch */
  #define ECU_M_ENABLE_SOH      /* soh enable switch */
  #define ECU_M_ENABLE_SOF      /* sof enable switch */
//  #define ECU_M_ENABLE_INTRES   /* internal resistance enable switch*/
  
  #define ECU_M_ENABLE_CHGM     /* charge manage enable switch */
  #define ECU_M_ENABLE_HVM     /* high-voltage manage enable switch */
  #define ECU_M_ENABLE_SAFTM   /* safe manage enable switch */
  
  #define ECU_M_ENABLE_NTC    /* ntc enable switch */
  
 //#define ECU_M_ENABLE_WR_PARA  /* Write para in flash */
  
  //#define ECU_M_IOHWAB_PWMIF   /* pwm interface switch */
  /* Default module have no switch */
  /* End of Module Enable swith define */
    
  
  /*
   *  Configurate for CAN communication
   */   
  #define CAN_CHANNEL_NUM 3  /* CAN channel number */   
  #define MAX_BUFFER_LEN 20  /* CAN buffer length */
  #define CAR_CAN_EN  /* switch for enable car can channel 0---disable 1---enable */
  #define CHG_CAN_EN  /* switch for enable charger can channel 0---disable 1---enable */
   /* End of Configurate for CAN communication */    
   
  /* 
   * Configurate for deal battery date  
   */        
  #define MAX_BMU_NUM 0      /* max bmu number */
    
  #define MAX_CELL_NUM 48     /* max cell number */       
  #define MAX_PACK_NUM  (MAX_BMU_NUM + 1)/* max pack number,include BCU_C*/   
  
  #define MAX_PACK_CELL_NUM   48 /* max cell number in one pack */ 
  #if((MAX_BMU_NUM * MAX_PACK_CELL_NUM) > (30 * 36)) // max permit 1080 cell
  #error "All cell number RAM overflow!"
  #endif
  #if(MAX_BMU_NUM > 30)
  #error "Bmu number overflow!"
  #endif
  #if(MAX_CELL_NUM > 120)
  #error "Max cell num overflow!" 
  #endif
  
  #define MAX_TEMPER_NUM    MAX_CELL_NUM // support detect per cell`s temperature  
  #define MAX_PACK_TEMPER_NUM  MAX_PACK_CELL_NUM 
  /* End of Configurate for deal battery date */
  
    /* Configurate for Cellv Detect */
  #define MAX_CELLV_IC_MODULE_NUM    20
  #define MAX_CELLV_NUM_PER_IC       12
  #define REAL_CELLV_IC_MODULE_NUM   2
  
  #define MAX_VOLT_PACK_NUM  4
  #define MAX_VOLTNUMPERPACK 12
  #define MAX_JUMPER_WIRE_NUM 10  
  /* End of Configurate for Cellv Detect */
  
#elif (ECU_CATEGORY == 2)
  /* 2: BMU --- Battery Measurement Unit */  
  /*
   * Module Enable swith define 
   */
   #define MAX_BMU_NO 30
  #define ECU_M_ENABLE_CELLV   /* CellvIf and CellvM Enable switch*/ 
  #define ECU_M_ENABLE_TEMPER  /* TemperIf and TemperM Enable switch*/ 
  //#define ECU_M_ENABLE_SUMV    /* SumvIf and SumvM Enable switch*/ 
  //#define ECU_M_ENABLE_CURRENT /* CurrentIf and CurrentM Enable switch*/ 
  //#define ECU_M_ENABLE_ISO     /* IsoIf and IsoM Enable switch */
  //#define ECU_M_ENABLE_GBCHGIF   /* GB charge interface Eanble swithc */
  
  //#define ECU_M_ENABLE_CARCAN   /* car can enable switch*/
  //#define ECU_M_ENABLE_CHGCAN   /* charge can enable switch*/
  
  //#define ECU_M_ENABLE_SOC      /* soc enable switch */
  //#define ECU_M_ENABLE_SOH      /* soh enable switch */
  //#define ECU_M_ENABLE_SOF      /* sof enable switch */
  //#define ECU_M_ENABLE_INTRES   /* internal resistance enable switch*/
  
  //#define ECU_M_ENABLE_CHGM     /* charge manage enable switch */
  //#define ECU_M_ENABLE_HVM     /* high-voltage manage enable switch */
  //#define ECU_M_ENABLE_SAFTM   /* safe manage enable switch */
  
  #define ECU_M_ENABLE_NTC    /* ntc enable switch */
  
  //#define ECU_M_IOHWAB_PWMIF   /* pwm interface switch */
  /* Default module have no switch */
  /* End of Module Enable swith define */
  
  /*
   *  Configurate for CAN communication
   */
  #define CAN_CHANNEL_NUM 1  /* CAN channel number, just internal CAN */
  #define MAX_BUFFER_LEN 5  /* CAN buffer length */
  /* End of Configurate for CAN communication */   
  
  /* 
   * Configurate for deal battery date  
   */   
  #define MAX_PACK_CELL_NUM   60 /* max cell number in one pack */   
  
  #define MAX_PACK_TEMPER_NUM  MAX_PACK_CELL_NUM
  /* End of Configurate for deal battery date */
  
  /* Configurate for Cellv Detect */
  #define MAX_CELLV_IC_MODULE_NUM   20    
  #define MAX_CELLV_NUM_PER_IC       12
  #define REAL_CELLV_IC_MODULE_NUM   5
  /* End of Configurate for Cellv Detect */
  
#elif (ECU_CATEGORY == 3)
 /* 3: BMU --- Battery Measurement Unit */ 
  /*
   * Module Enable swith define 
   */
  #define ECU_M_ENABLE_CELLV   /* CellvIf and CellvM Enable switch*/ 
  #define ECU_M_ENABLE_TEMPER  /* TemperIf and TemperM Enable switch*/ 
  #define ECU_M_ENABLE_SUMV    /* SumvIf and SumvM Enable switch*/ 
  #define ECU_M_ENABLE_CURRENT /* CurrentIf and CurrentM Enable switch*/ 
  //#define ECU_M_ENABLE_ISO     /* IsoIf and IsoM Enable switch */
  #define ECU_M_ENABLE_GBCHGIF   /* GB charge interface Eanble swithc */
  
  //#define ECU_M_ENABLE_CARCAN   /* car can enable switch*/
  #define ECU_M_ENABLE_CHGCAN   /* charge can enable switch*/
  
  #define ECU_M_ENABLE_SOC      /* soc enable switch */
  //#define ECU_M_ENABLE_SOH      /* soh enable switch */
  //#define ECU_M_ENABLE_SOF      /* sof enable switch */
  //#define ECU_M_ENABLE_INTRES   /* internal resistance enable switch*/
  
  #define ECU_M_ENABLE_CHGM     /* charge manage enable switch */
  //#define ECU_M_ENABLE_HVM     /* high-voltage manage enable switch */
  //#define ECU_M_ENABLE_SAFTM   /* safe manage enable switch */
  
  #define ECU_M_ENABLE_NTC    /* ntc enable switch */
  
  //#define ECU_M_IOHWAB_PWMIF   /* pwm interface switch */
  /* Default module have no switch */
  /* End of Module Enable swith define */
  
  /*
   *  Configurate for CAN communication
   */  
  #define CAN_CHANNEL_NUM 1  /* CAN channel number, just internal CAN */
  #define MAX_BUFFER_LEN 10  /* CAN buffer length */
  
   /* 
   * Configurate for deal battery date  
   */   
  #define MAX_PACK_CELL_NUM   60 /* max cell number in one pack */   
  
  #define MAX_PACK_TEMPER_NUM  MAX_PACK_CELL_NUM
  /* End of Configurate for deal battery date */
  
   /* Configurate for Cellv Detect */
  #define MAX_CELLV_IC_MODULE_NUM    20
  #define MAX_CELLV_NUM_PER_IC       12  
  #define REAL_CELLV_IC_MODULE_NUM   5  
  /* End of Configurate for Cellv Detect */
  
#else
 #error: "Error Ecu category!!"
#endif 



/* 
 * System Function switch 
 */
//#define BMS_ENABLE_CALC_INTRES     /* enable calculate internal resistance */
//#define BMS_ENABLE_CALC_CELL_SOC   /* enable calculate soc per cell */
//#define BMS_ENABLE_SINGLE_BAL_TIME /* enable single balance time calculation */


extern uByte Ecu_GetEcuSA(void);



#endif
