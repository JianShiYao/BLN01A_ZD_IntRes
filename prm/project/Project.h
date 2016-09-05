#ifndef PROJECT_H
#define PROJECT_H

// define for ready flag
#define DEFAULT_READY         0x00
#define HARDWARE_READY        0x01
#define ALL_BMU_READY         0x02
#define MAXMIN_TEMPER_READY   0x04
#define MAXMIN_CELLV_READY    0x08
#define SUMV_READY            0x10
#define CUR_READY             0x20
#define ALL_CELLV_READY       0x40
#define ALL_TEMPER_READY      0x80

void Prj_PreMainInit(void);
void Prj_PosMainInit(void);
void Prj_UpdateRecvFirFrame(uByte bmu_no);
void Prj_MainCounterCbk(void);
void Prj_MainProCbk(void);

 
uByte Prj_GetReadyFlag(void);
void Prj_WrDefaultCfg(void);
void Prj_WrChgPara(void);
void Prj_WrHeatPara(void); 
void Prj_WrDefaultErrorThrhd(void);
//void Prj_WrCapacity(void);


#endif