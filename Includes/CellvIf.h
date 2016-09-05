#ifndef __CELLV_H__
#define __CELLV_H__
#include "GeneralTypeDef.h"
#include "Cellv_Cfg.h"

typedef union 
{
    uByte CRC_BYTE;
    struct
    {
        /* slave board error code */
        uByte ff0        :   1;
        uByte ff1        :   1;
        uByte ff2        :   1;
        uByte ff3        :   1;
        uByte reserve1	  :   4;
    } bit;
} CRC_94212;

typedef union 
{
    uByte CRC_BYTE;
    struct
    {
        /* slave board error code */
        uByte bit0        :   1;
        uByte bit1        :   1;
        uByte bit2        :   1;
        uByte bit3        :   1;
        uByte reserve1	   :   4;

    } bit;
} CRC_94212_2;


typedef union 
{
    uLWord COM;
    uByte COM_BYTE[4];
    struct
    {
        /* slave board error code */


        uByte PAGE	       :   3;
        uByte RW          :   1;
        uByte DEVICE      :   4;        //位是先低后高，字节是先高后低

        uByte DATA        :   2;
        uByte DA_ADDRESS  :   6;

        uByte CRC4        :   4;
        uByte ZERO        :   4;

        uByte reserve1    :   8;

    } bit;
} COM_94212;



typedef union 
{
    uLWord COM;
    uByte COM_BYTE[4];
    struct
    {
        /* slave board error code */
        uByte PAGE	       :   3;
        uByte RW          :   1;
        uByte DEVICE      :   4;        //位是先低后高，字节是先高后低

        uByte DATA3       :   2;
        uByte DA_ADDRESS  :   6;

        uByte DATA2       :   8;

        uByte CRC4        :   4;
        uByte DATA1       :   4;

    } bit;
} COM_94212_4;


#define SCAN_V_ALL    0XF3040300
#define SCAN_T_ALL    0XF3080400
#define SCAN_LINE_ALL 0XF3100A00

#define READ_V_1      0X113C0500
#define READ_V_2      0X213C0300

#define READ_T_1      0X117C0200
#define READ_T_2      0X217C0400

#define READ_LINE_1   0X12080400
#define READ_LINE_2   0X22080200

#define ONE           1
#define TWO           2

#define AD_CNVT_MODE_NORMAL   0
#define AD_CNVT_MODE_DIAG     1  






#define  ERR_CRC_CELLV   ERR_CDD_CELLVIF_BASE               //CRC error 
#define  ERR_WR_CELLV    (ERR_CDD_CELLVIF_BASE + 1)         //write error
#define  ERR_BUSY_CELLV  (ERR_CDD_CELLVIF_BASE + 2)         //busy
#define  ERR_CFG_CELLV   (ERR_CDD_CELLVIF_BASE + 3)         //configuration register error
#define  ERR_DCC_LTC     (ERR_CDD_CELLVIF_BASE + 4)         //discharge cell register error
#define  ERR_MCI_LTC     (ERR_CDD_CELLVIF_BASE + 5)         //mask cell interrupt error
#define  ERR_VUV_LTC     (ERR_CDD_CELLVIF_BASE + 6)         //undervoltage comparison voltage error
#define  ERR_VOV_LTC     (ERR_CDD_CELLVIF_BASE + 7)         //overvoltage comparison voltage error
#define  ERR_TYPE_BLC    (ERR_CDD_CELLVIF_BASE + 8)         //type of balance is error
#define  ERR_NOT_INIT    (ERR_CDD_CELLVIF_BASE + 9)  
#define  ERR_UNEXPECT     (ERR_CDD_CELLVIF_BASE + 10)       //unexpected error

#define  ERR_CELLV_INIT  (ERR_CDD_CELLVIF_BASE + 11)
#define  ERR_CELLV_START (ERR_CDD_CELLVIF_BASE + 12)
#define  ERR_CELLV_RDCV  (ERR_CDD_CELLVIF_BASE + 13)
#define  ERR_CELLV_CFG   (ERR_CDD_CELLVIF_BASE + 14)
#define  ERR_CELLV_NOT_MEASURE (ERR_CDD_CELLVIF_BASE + 15)
#define  ERR_CELLV_SLEFTEST    (ERR_CDD_CELLVIF_BASE + 16)
#define  ERR_CELLV_MUXFAIL     (ERR_CDD_CELLVIF_BASE + 17)
#define  ERR_CELLV_VREF_FAIL   (ERR_CDD_CELLVIF_BASE + 18)
#define  ERR_CELLV_GPIO        (ERR_CDD_CELLVIF_BASE + 19)
#define  ERR_BALANCE_DCH       (ERR_CDD_CELLVIF_BASE + 20)
#define  ERR_BALANCE_DIAG      (ERR_CDD_CELLVIF_BASE + 21)
#define  ERR_CELLV_MUX         (ERR_CDD_CELLVIF_BASE + 22)
#define  ERR_CELLV_VREF        (ERR_CDD_CELLVIF_BASE + 23)
#define  ERR_CELLV_DIAG        (ERR_CDD_CELLVIF_BASE + 24)
#define  ERR_CELLV_NULL_POINTER  (ERR_CDD_CELLVIF_BASE + 25)

#define  ERR_CELLV_IDOUTRANG   ERR_UNEXPECT//(ERR_CDD_CELLVIF_BASE + 25)
#define  ERR_CELLV_ROWOUTRANG   (ERR_CDD_CELLVIF_BASE + 26)
#define  ERR_CELLV_BALANCE_CMD   (ERR_CDD_CELLVIF_BASE + 27)
#define  MAX_CELLV_NUM_PER_CHIP  12




#define DCH_BALANCE_OFF   0x10
#define DCH_BALANCE_ON    0x11

#define CHG_BALANCE_OFF   0x20
#define CHG_BALANCE_ON    0x21

#define CMD_BAL_OFF   0x10
#define CMD_BAL_ON    0x11


typedef enum
{
  CELLVIF_CHIP_1,
  CELLVIF_CHIP_2,
  CELLVIF_CHIP_3,
  CELLVIF_CHIP_4,
  CELLVIF_CHIP_5,
  CELLVIF_CHIP_6,
  CELLVIF_CHIP_7,
  CELLVIF_CHIP_8,
  CELLVIF_CHIP_9,
  CELLVIF_CHIP_10,
}eCellvIf_DeviceIdType;

/*extern uLWord glwd_Cnt;
extern uLWord glwd_Cnt1;
extern uLWord glwd_Cnt2;
extern uLWord glwd_Cnt3;
extern uLWord glwd_Cnt4;
extern uLWord glwd_Cnt5; */

#define CellvIf_ChipDisable()  CELLV_EN_CLR
              
//ModuleID_Type Cellv_ID_GetVesionModuleVer(sVersion_CodeType * VerPtr);
extern GeneralReturnType CellvIf_Init(eCellvIf_DeviceIdType DeviceId);
extern void CellvIf_Cbk(void);
extern void CellvIf_CntCbk(void);
extern void CellvIf_EnControl(uByte En);
extern GeneralReturnType CellvIf_StartCnvt(eCellvIf_DeviceIdType DeviceId,  uByte CnvtMode);
extern GeneralReturnType CellvIf_RdValue(eCellvIf_DeviceIdType DeviceId, uWord *Rd_DataBuffPtr,uByte *LengthPtr);
//GeneralReturnType CellvIf_GetDeviceInfo(eCellvIf_DeviceIdType DeviceId, sDeviceInfo *DevicePtr);
//GeneralReturnType CellvIf_HwDiag(eCellvIf_DeviceIdType DeviceId, uByte HwDiagMode, uByte CellNum, uWord *ErrCodePtr, uWord *FaultPosPtr);
extern GeneralReturnType CellvIf_CtrlBalanceSw(eCellvIf_DeviceIdType DeviceId, uWord Row, uByte Cmd);
extern GeneralReturnType CellvIf_StopBalance(eCellvIf_DeviceIdType DeviceId);

extern uByte Ctrl_Bal(uByte DeviceId);

#endif