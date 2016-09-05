
#include "GbChgM-B.h"
#include "GbChgCan.h"
//#include "SchIf.h"
#include "BatterySt.h"
#include "ChargeSt.h"
#include "ChgCan.h"
#include "AiIf.h"
#include "GbChg_IfDet.h"
#include "ErrorAlarm.h"
#include "DoIf.h"

typedef struct
{
    uWord RxChgMsg;
} sGbChgM_TmCntType;

sGbChgM_CtrlType GbChgM_Ctrl;
sGbChgM_TmCntType GbChgM_TmCnt;
uWord gwd_CntChgLinkFail;
uWord gwd_CntAcLinkFail;
uWord gwd_AcPmtChgCur;
uByte gby_byte_num_brm;
uByte gby_msg_num_brm;

extern void GbChgCan_UpdateRxFlg(uWord flg);
extern uWord GbChgCan_GetRxFlg(void);
extern uByte GbChgCan_GetCrmRxBms(void);
extern uByte GbChgCan_GetCroChgReady(void);
extern void GbChgCan_UpdateCntBst(uByte cnt);
extern uByte ChgM_GetChgRlyCtrl(void);
extern uWord ChgM_GetChgStartCnt(void);

void GbChgM_LinkModeJudge(void);
static void  GbChgM_FlowProc(void);
static void GbChgM_AcChg(void);


void GbChgM_UpdateAcPmtChgCur(uWord cur)
{
    gwd_AcPmtChgCur = cur;
}

uWord GbChgM_GetAcPmtChgCur(void)
{
    return gwd_AcPmtChgCur;
}

uByte GbChgM_GetFlgBrm(void)
{
    return GbChgM_Ctrl.Flg.Brm;
}

uByte GbChgM_GetFlgBcp(void)
{
    return GbChgM_Ctrl.Flg.Bcp;
}

uByte GbChgM_GetFlgBcs(void)
{
    return GbChgM_Ctrl.Flg.Bcs;
}

uByte GbChgM_GetFlgBmv(void)
{
    return GbChgM_Ctrl.Flg.Bmv;
}

uByte GbChgM_GetFlgBmt(void)
{
    return GbChgM_Ctrl.Flg.Bmt;
}

uByte GbChgM_GetFlgBsp(void)
{
    return GbChgM_Ctrl.Flg.Bsp;
}


uByte GbChgM_GetFlgBro(void)
{
    return GbChgM_Ctrl.Flg.Bro;
}
uByte GbChgM_GetFlgBcl(void)
{
    return GbChgM_Ctrl.Flg.Bcl;
}

uByte GbChgM_GetFlgBsm(void)
{
    return GbChgM_Ctrl.Flg.Bsm;
}

uByte GbChgM_GetFlgBst(void)
{
    return GbChgM_Ctrl.Flg.Bst;
}

uByte GbChgM_GetFlgBsd(void)
{
    return GbChgM_Ctrl.Flg.Bsd;
}

uByte GbChgM_GetFlgBem(void)
{
    return GbChgM_Ctrl.Flg.Bem;
}

uByte GbChgM_GetFlgBhm(void)
{
    return GbChgM_Ctrl.Flg.Bhm;
}

uByte GbChgM_GetStep(void)
{
    return GbChgM_Ctrl.ChgStep;
}

uByte GbChgM_GetChgEndReason1(void)
{
    return GbChgM_Ctrl.ChgEndReason1;
}
uByte GbChgM_GetChgEndReason2(void)
{
    return GbChgM_Ctrl.ChgEndReason2;
}
uByte GbChgM_GetChgEndReason3(void)
{
    return GbChgM_Ctrl.ChgEndReason3;
}
uByte GbChgM_GetChgEndReason4(void)
{
    return GbChgM_Ctrl.ChgEndReason4;
}

uByte GbChgM_GetChgHandShakeErr(void)
{
    return GbChgM_Ctrl.HandShakeErr;
}
uByte GbChgM_GetChgConfigErr(void)
{
    return GbChgM_Ctrl.ConfigErr;
}
uByte GbChgM_GetChargingErr(void)
{
    return GbChgM_Ctrl.ChargingErr;
}
uByte GbChgM_GetChargeEndErr(void)
{
    return GbChgM_Ctrl.ChargeEndErr;
}

void GbChgM_ModuleInit(void)
{
    uByte i, *p_byte;

    p_byte = (uByte*)(&GbChgM_Ctrl);
    for(i = 0; i < sizeof(GbChgM_Ctrl); i++)
    {
        *(p_byte++) = 0;
    }

    p_byte = (uByte *)(&GbChgM_TmCnt);
    for(i = 0; i < sizeof(GbChgM_TmCnt); i++)
    {
        *(p_byte++) = 0;
    }
    
    GbChgM_Ctrl.ChgStep = ChgStep11;
}

void GbChgM_ModuleCountCbk(void)
{
    (GbChgM_TmCnt.RxChgMsg < 65535) ? (GbChgM_TmCnt.RxChgMsg++) : (GbChgM_TmCnt.RxChgMsg = 65535);
}

/******************************************************************************/
/* FUNCTION: deal gb charge control                                           */
/*                                                                            */
/* DESCRIPTION: should call this funtion every 10ms                           */
/******************************************************************************/
void GbChgM_ChgCtrl(void)
{

#ifdef ECU_M_ENABLE_GBCHGIF
    /* deal GB protocol  */
    GbChgM_FlowProc();
    GbChgM_AcChg();
#endif
}

void GbChgM_EndReasonDeal(void)
{
    uLWord lwd_end_reason;

    lwd_end_reason = ChgM_GetChgEndReason();

    if((lwd_end_reason & CHG_ISO_ERR) == CHG_ISO_ERR)
    {
        GbChgM_Ctrl.ChgEndReason2 |= ISO_ERR;
    }

    if((lwd_end_reason & CHG_TEMP_HIGH) == CHG_TEMP_HIGH)
    {
        GbChgM_Ctrl.ChgEndReason3 |= BAT_OVER_T;
    }

    if(((lwd_end_reason & CHG_HD_ERR) == CHG_HD_ERR)
            || ((lwd_end_reason & CHG_TEMP_LOW) == CHG_TEMP_LOW)
            || ((lwd_end_reason & CHG_RLY_ERR) == CHG_RLY_ERR))
    {
        GbChgM_Ctrl.ChgEndReason3 |= OTHER_ERR;
    }

    if((lwd_end_reason & CHG_CUR_HIGH) == CHG_CUR_HIGH)
    {
        GbChgM_Ctrl.ChgEndReason4 |= OVER_CUR;
    }

    if( ((lwd_end_reason & CHG_CELLV_HIGH) == CHG_CELLV_HIGH)
            || ((lwd_end_reason & CHG_SUMV_HIGH) == CHG_SUMV_HIGH)
            || ((lwd_end_reason & CHG_SUMV_LOW) == CHG_SUMV_LOW))
    {
        GbChgM_Ctrl.ChgEndReason4 |= OVER_VOLT;
    }
}

uWord GbChgM_ACPmtCurCalc(void)
{
    uWord lwd_cur;
    uWord lwd_ac_cur;

    lwd_cur = Chg_GetPermitChgCurOn();
    lwd_ac_cur = GbChgM_GetAcPmtChgCur();
    if(lwd_cur > lwd_ac_cur)
    {
        lwd_cur = lwd_ac_cur;
    }

    return lwd_cur;
}

void GbChgM_StopReasonJudge(void)
{
    uWord lwd_sum_v;
    uWord lwd_max_v;
    uWord lwd_max_pmt_sum_v_thrhd;
    uWord lwd_max_pmt_cell_v_thrhd;

    lwd_sum_v = Bat_GetSumV(INT_SUMV);
    lwd_max_pmt_sum_v_thrhd = Chg_GetPermitMaxSumV();
    lwd_max_v = Bat_GetMaxV();
    lwd_max_pmt_cell_v_thrhd = Chg_GetPermitMaxCellV();

    if(lwd_sum_v >= lwd_max_pmt_sum_v_thrhd)
    {
        GbChgM_Ctrl.ChgEndReason1 |= REACH_SUMV;
    }
    if(lwd_max_v >= lwd_max_pmt_cell_v_thrhd)
    {
        GbChgM_Ctrl.ChgEndReason1 |= REACH_CELLV;
    }
}

/* AC mode or DC mode */
static void GbChg_ModeJudge(uByte *p_gb_chg_mode,  uWord *link_fail_cnt)
{
    uWord lwd_cc_volt;
    uWord lwd_cc2_volt;
    uByte lby_cp_signal;


    lwd_cc_volt = Chg_GetCcVolt();
    lwd_cc2_volt = Chg_GetCc2Volt();
    lby_cp_signal = Chg_GetCpDutyCycle();

    if((0 == lby_cp_signal)  && (lwd_cc2_volt > CON_CONFLICT_V) &&
      (((lwd_cc_volt > CC_V_L_10AMODE) && (lwd_cc_volt < CC_V_H_10AMODE)) // 10A
            || ((lwd_cc_volt > CC_V_L_16AMODE) && (lwd_cc_volt < CC_V_H_16AMODE)) // 16A
            || ((lwd_cc_volt > CC_V_L_32AMODE) && (lwd_cc_volt < CC_V_H_32AMODE)) // 32A
            || ((lwd_cc_volt > CC_V_L_63AMODE) && (lwd_cc_volt < CC_V_H_63AMODE)) // 63A
            ) )
    {
         *p_gb_chg_mode = AC_CHG_MODE1_B;
    }
    else if( (((lwd_cc_volt > CC_V_L_10AMODE) && (lwd_cc_volt < CC_V_H_10AMODE)) // 10A
            || ((lwd_cc_volt > CC_V_L_16AMODE) && (lwd_cc_volt < CC_V_H_16AMODE)) // 16A
            || ((lwd_cc_volt > CC_V_L_32AMODE) && (lwd_cc_volt < CC_V_H_32AMODE)) // 32A
            || ((lwd_cc_volt > CC_V_L_63AMODE) && (lwd_cc_volt < CC_V_H_63AMODE)) // 63A
            ) && (0 != lby_cp_signal) && (lwd_cc2_volt > CON_CONFLICT_V))
    {
        *p_gb_chg_mode = AC_CHG_MODE3_A;
    }
    else if(( (lwd_cc2_volt > CC2_V_L) && (lwd_cc2_volt < CC2_V_H) ) && (lwd_cc_volt > CON_CONFLICT_V))
    {
        *p_gb_chg_mode = DC_CHG_MODE;
    }
    else if((0 != lby_cp_signal)  && ( (lwd_cc2_volt > CC2_V_L) && (lwd_cc2_volt < CC2_V_H) ))
    {
        *p_gb_chg_mode = CHG_MODE_CONFLICT;
    }
    else
    {
        if((*link_fail_cnt) < CNT_DET_LINK)
        {
            (*link_fail_cnt)++;
        }
        else
        {
            *p_gb_chg_mode = NO_CHG_CON;
            (*link_fail_cnt) = CNT_DET_LINK;
        }
    }


  
}

void GbChgM_LinkModeJudge(void)
{
    uWord lwd_cp_cur = 0;
    uWord lwd_cc_cur = 0;
    uByte lby_cp_duty = 0;
    uWord lwd_cc_volt = 0;

    uByte lby_gb_chg_mode = 0;
    uByte lby_dc_link_st = 0;
    uByte lby_ac_link_st = 0;
    uWord lwd_ac_chg_pmt_cur = 0;

    lby_dc_link_st =  Chg_GetDcLinkSt();
    lby_ac_link_st =  Chg_GetAcLinkSt();
    lwd_ac_chg_pmt_cur = GbChgM_GetAcPmtChgCur();

    GbChg_ModeJudge(&lby_gb_chg_mode, &gwd_CntChgLinkFail);
    lwd_cc_volt = Chg_GetCcVolt();
    lby_cp_duty = Chg_GetCpDutyCycle();

    switch(lby_gb_chg_mode)
    {
    case DC_CHG_MODE:
    {
        lby_dc_link_st = GB_FLAG_OK;
        break;
    }
    case AC_CHG_MODE1_B:          /* family use  */
    {
        
        if((lwd_cc_volt  > CC_V_L_10AMODE) && (lwd_cc_volt < CC_V_H_10AMODE))
        {
             lby_ac_link_st = GB_FLAG_OK;                 //cap 10A
            lwd_cc_cur = 100;
            Chg_UpdateCableCap(lwd_cc_cur);                                                
        }
        else if((lwd_cc_volt > CC_V_L_16AMODE) && (lwd_cc_volt < CC_V_H_16AMODE)) /* cap 16A */
        {
            lby_ac_link_st = GB_FLAG_OK;
            lwd_cc_cur = 160;
            Chg_UpdateCableCap(lwd_cc_cur);
        }
        else if((lwd_cc_volt > CC_V_L_32AMODE) && (lwd_cc_volt < CC_V_H_32AMODE)) /* cap 32A */
        {
            lby_ac_link_st = GB_FLAG_OK;
            lwd_cc_cur = 320;
            Chg_UpdateCableCap(lwd_cc_cur);
        }
        else if((lwd_cc_volt  > CC_V_L_63AMODE) && (lwd_cc_volt < CC_V_H_63AMODE))
        {
            lby_ac_link_st = GB_FLAG_OK;
            lwd_cc_cur = 630;                     //cap 63A
            Chg_UpdateCableCap(lwd_cc_cur);
        }
        else
        {
            lby_ac_link_st = GB_FLAG_FAIL;
            lwd_cc_cur = 0;
            Chg_UpdateCableCap(lwd_cc_cur);
        }
       
        lwd_ac_chg_pmt_cur = lwd_cc_cur;

    }
    case AC_CHG_MODE3_A:
    case AC_CHG_MODE2_B:		    /*the same as AC_CHG_MODE3_C */
    case AC_CHG_MODE3_B:				/*the same as AC_CHG_MODE3_C */
    case AC_CHG_MODE3_C:
    {
      //  lwd_cc_volt *= 10;
        if((lwd_cc_volt  > CC_V_L_10AMODE) && (lwd_cc_volt < CC_V_H_10AMODE))
        {
             lby_ac_link_st = GB_FLAG_OK;                 //cap 10A
            lwd_cc_cur = 100;
            Chg_UpdateCableCap(lwd_cc_cur);                                                
        }
        else if((lwd_cc_volt > CC_V_L_16AMODE) && (lwd_cc_volt < CC_V_H_16AMODE)) /*cap 16A */
        {
            lby_ac_link_st = GB_FLAG_OK;
            lwd_cc_cur = 160;
            Chg_UpdateCableCap(lwd_cc_cur);
        }
        else if((lwd_cc_volt > CC_V_L_32AMODE) && (lwd_cc_volt < CC_V_H_32AMODE)) /*cap 32A */
        {
            lby_ac_link_st = GB_FLAG_OK;
            lwd_cc_cur = 320;
            Chg_UpdateCableCap(lwd_cc_cur);
        }
        else if((lwd_cc_volt  > CC_V_L_63AMODE) && (lwd_cc_volt < CC_V_H_63AMODE))
        {
            lby_ac_link_st = GB_FLAG_OK;
            lwd_cc_cur = 630;                     //cap 63A
            Chg_UpdateCableCap(lwd_cc_cur);
        }
        else
        {
            lby_ac_link_st = GB_FLAG_FAIL;
            lwd_cc_cur = 0;
            Chg_UpdateCableCap(lwd_cc_cur);
        }

        /* judge cp_signal current   ACC_curent */
        if(lby_cp_duty > 90)
        {
            lby_ac_link_st = GB_FLAG_FAIL;
            lwd_cp_cur = 0;
        }        
        else if(lby_cp_duty > 85)
        {
            lwd_cp_cur = (lby_cp_duty - 64) * 25;
            if(lwd_cp_cur > 630)
            {
                lwd_cp_cur = 630;
            }
        }
        else if(lby_cp_duty >= 10)
        {
            lwd_cp_cur = lby_cp_duty  * 6 ;
        }
        else if(lby_cp_duty >= 8)
        {
            lwd_cp_cur = 60;
        }
        else
        {
            lby_ac_link_st = GB_FLAG_FAIL;
            lwd_cp_cur = 0;
        }
        

        if(lwd_cc_cur > lwd_cp_cur)
        {
            lwd_ac_chg_pmt_cur = lwd_cp_cur;
        }
        else
        {
            lwd_ac_chg_pmt_cur = lwd_cc_cur;
        }

        break;
    }

    case AC_CHG_CON_ERR:							  /*the same as  CHG_MODE_CONFLICT */
    case AC_CHG_LOCK_ERR:								/*the same as  CHG_MODE_CONFLICT */
    case CHG_MODE_CONFLICT:
    {
        lby_dc_link_st = GB_FLAG_FAIL;
        lby_ac_link_st = GB_FLAG_FAIL;
        lwd_ac_chg_pmt_cur = 0;
        break;
    }

    default:
    {
        lby_dc_link_st = GB_FLAG_FAIL;
        lby_ac_link_st = GB_FLAG_FAIL;
        lwd_ac_chg_pmt_cur = 0;
        break;
    }
    }

    Chg_UpdateDcLinkSt(lby_dc_link_st);
    Chg_UpdateAcLinkSt(lby_ac_link_st);
    GbChgM_UpdateAcPmtChgCur(lwd_ac_chg_pmt_cur);
}

void GbChgM_FlowProc(void)
{
    uByte lby_dc_link_st;
    uByte lby_chg_enable_ext;
    uWord lwd_rx_flg;

    sGbChgM_CtrlType *pGbChgCtrl;
    pGbChgCtrl = &GbChgM_Ctrl;

    lby_dc_link_st = Chg_GetDcLinkSt();
    lby_chg_enable_ext = Chg_GetPermitChgExtSt();
    lwd_rx_flg = GbChgCan_GetRxFlg();

#ifdef __DEBUG_GB_CHG_TEST
    lby_dc_link_st = 1;
    lby_chg_enable_ext = 1;

#endif
    switch (pGbChgCtrl->ChgStep)
    {
    case ChgStep11:
    {
       if(GB_FLAG_OK == lby_dc_link_st)
       {
         if( ((CRM_RX == (lwd_rx_flg & CRM_RX)))
                  && (CHG_NOT_RX_BMS == GbChgCan_GetCrmRxBms() ) )/* charger has Not recognize BMS */
          {
              lwd_rx_flg = 0;
              pGbChgCtrl->Flg.Brm = GB_FLAG_ENABLE;	 /* send Brm enable */           
              pGbChgCtrl->ChgStep = ChgStep1;

              /* need clear error information when re-handshake successful  */
              pGbChgCtrl->Flg.Bem = GB_FLAG_DISABLE;  /* send Bem disable  */
              pGbChgCtrl->HandShakeErr = 0;
              pGbChgCtrl->ConfigErr = 0;
              pGbChgCtrl->ChargingErr = 0;
              pGbChgCtrl->ChargeEndErr = 0;
            /*pGbChgCtrl->ChgEndReason1 = 0;
              pGbChgCtrl->ChgEndReason2 = 0;
              pGbChgCtrl->ChgEndReason3 = 0;
              pGbChgCtrl->ChgEndReason4 = 0; */
              gby_byte_num_brm = 41;
              gby_msg_num_brm = 6;
          }       
          else if(CHM_RX == (lwd_rx_flg & CHM_RX))
          {
              lwd_rx_flg = 0;
              pGbChgCtrl->Flg.Bhm = GB_FLAG_ENABLE;	 /* send Brm enable */
              pGbChgCtrl->ChgStep = ChgStep12;

              /* need clear error information when re-handshake successful  */
              pGbChgCtrl->Flg.Bem = GB_FLAG_DISABLE;  /* send Bem disable  */
              pGbChgCtrl->HandShakeErr = 0;
              pGbChgCtrl->ConfigErr = 0;
              pGbChgCtrl->ChargingErr = 0;
              pGbChgCtrl->ChargeEndErr = 0;
              
              gby_byte_num_brm = 49;
              gby_msg_num_brm = 7;
            
          }
          else
          {
              if(GbChgM_TmCnt.RxChgMsg < TM_MS(5000))
              {
                  pGbChgCtrl->ChgStep = ChgStep11;
              }
              else
              {
                  pGbChgCtrl->HandShakeErr |= RX_CHM_ERR;
                  pGbChgCtrl->ChgStep = ChgStep9;
              }
          }
                   
       }
    
       break;
    } 
    case ChgStep12:
    {      
        if(CHM_RX == (lwd_rx_flg & CHM_RX))
        {
            lwd_rx_flg = 0;
            pGbChgCtrl->Flg.Bhm = GB_FLAG_ENABLE;	 /* send Brm enable */
            pGbChgCtrl->ChgStep = ChgStep12;

            /* need clear error information when re-handshake successful  */
            pGbChgCtrl->Flg.Bem = GB_FLAG_DISABLE;  /* send Bem disable  */
           
        }
        else 
        {
         //   pGbChgCtrl->Flg.Bhm = GB_FLAG_DISABLE;	 
            pGbChgCtrl->ChgStep = ChgStep0;
        }
         
        break;
    } 
    
    
    case ChgStep0:
    {
        
         if(pGbChgCtrl->ChgStepBak != pGbChgCtrl->ChgStep)
        {
            pGbChgCtrl->ChgStepBak = pGbChgCtrl->ChgStep;
            GbChgM_TmCnt.RxChgMsg = 0;
        }
       // if(GB_FLAG_OK == lby_dc_link_st)
        {
            if( ((CRM_RX == (lwd_rx_flg & CRM_RX)))
                    && (CHG_NOT_RX_BMS == GbChgCan_GetCrmRxBms() ) )/* charger has Not recognize BMS */
            {
                lwd_rx_flg = 0;
                pGbChgCtrl->Flg.Brm = GB_FLAG_ENABLE;	 /* send Brm enable */
                pGbChgCtrl->Flg.Bhm = GB_FLAG_DISABLE;  /* send Bhm disable */
                pGbChgCtrl->ChgStep = ChgStep1;

                /* need clear error information when re-handshake successful  */
                pGbChgCtrl->Flg.Bem = GB_FLAG_DISABLE;  /* send Bem disable  */
                pGbChgCtrl->HandShakeErr = 0;
                pGbChgCtrl->ConfigErr = 0;
                pGbChgCtrl->ChargingErr = 0;
                pGbChgCtrl->ChargeEndErr = 0;
              /*pGbChgCtrl->ChgEndReason1 = 0;
                pGbChgCtrl->ChgEndReason2 = 0;
                pGbChgCtrl->ChgEndReason3 = 0;
                pGbChgCtrl->ChgEndReason4 = 0; */
            }
            else
            {
               // if(GbChgM_TmCnt.RxChgMsg < TM_MS(5000))
                {
                    pGbChgCtrl->ChgStep = ChgStep0;
                }
                //else
                {
              //      pGbChgCtrl->HandShakeErr |= RX_CRM0_ERR;
              //      pGbChgCtrl->ChgStep = ChgStep9;
                }
            }
        }

        break;
    }

    case ChgStep1:
    {
        if(pGbChgCtrl->ChgStepBak != pGbChgCtrl->ChgStep)
        {
            pGbChgCtrl->ChgStepBak = pGbChgCtrl->ChgStep;
            GbChgM_TmCnt.RxChgMsg = 0;
        }

        if( ((CRM_RX == (lwd_rx_flg & CRM_RX)))
                && (CHG_RX_BMS == GbChgCan_GetCrmRxBms()))//GbChgCan_RxData.Crm.RxBms) )/* charger recognize BMS */
        {
            lwd_rx_flg = 0;
            pGbChgCtrl->Flg.Brm = GB_FLAG_DISABLE;	 /* send Brm disable */
            pGbChgCtrl->ChgStep = ChgStep2;
        }
        else
        {
            if(GbChgM_TmCnt.RxChgMsg < TM_MS(5000))
            {
                pGbChgCtrl->Flg.Brm = GB_FLAG_ENABLE;	 /* send Brm enable */
                pGbChgCtrl->ChgStep = ChgStep1;
            }
            else
            {
                pGbChgCtrl->Flg.Brm = GB_FLAG_DISABLE;	 /* send Brm disable  */
                pGbChgCtrl->HandShakeErr |= RX_CRM1_ERR;
                pGbChgCtrl->ChgStep = ChgStep9;
            }
        }

        break;
    }

    case ChgStep2:
    {
        if(pGbChgCtrl->ChgStepBak != pGbChgCtrl->ChgStep)
        {
            pGbChgCtrl->ChgStepBak = pGbChgCtrl->ChgStep;
            GbChgM_TmCnt.RxChgMsg = 0;
        }

        pGbChgCtrl->Flg.Bcp = GB_FLAG_ENABLE;	 /* send Bcp enable */

        /* receive charger time and max output ability */
        if ( (CTS_RX == (lwd_rx_flg & CTS_RX))
                && (CML_RX == (lwd_rx_flg & CML_RX)) )
        {
            lwd_rx_flg &= ~CTS_RX;
            lwd_rx_flg &= ~CML_RX;

            pGbChgCtrl->Flg.Bcp = GB_FLAG_DISABLE;	 /* send Bcp disable */
            pGbChgCtrl->ChgStep = ChgStep3;
        }
        else
        {
            if(GbChgM_TmCnt.RxChgMsg < TM_MS(5000))
            {
                pGbChgCtrl->Flg.Bcp = GB_FLAG_ENABLE;	 /* send Bcp enable */
                pGbChgCtrl->ChgStep = ChgStep2;
            }
            else
            {
                pGbChgCtrl->Flg.Bcp = GB_FLAG_DISABLE;	 /* send Bcp disable */
                pGbChgCtrl->ConfigErr |= RX_CTS_CML_ERR;
                pGbChgCtrl->ChgStep = ChgStep9;
            }
        }

        break;
    }

    case ChgStep3:
    {
        if(pGbChgCtrl->ChgStepBak != pGbChgCtrl->ChgStep)
        {
            pGbChgCtrl->ChgStepBak = pGbChgCtrl->ChgStep;
            GbChgM_TmCnt.RxChgMsg = 0;
        }

        // need modify
        if(GB_FLAG_ENABLE == lby_chg_enable_ext) /* bms Ready */
        {
        #ifdef __DEBUG_GB_CHG_TEST
            if(1)
        #else
            if(GB_RELAY_ON == ChgM_GetChgRlyCtrl())
        #endif
            {

                pGbChgCtrl->Flg.Bro = GB_FLAG_ENABLE;	 /* send Bro enable */
                pGbChgCtrl->ChgStep = ChgStep4;
            }
            else
            {
                break;
            }
        }
        else                                   /* bms Not Ready */
        {
            pGbChgCtrl->Flg.Bro = GB_FLAG_ENABLE;	 /* send Bro enable */

            pGbChgCtrl->ChgStep = ChgStep2;//ChgStep3;
        }

        break;
    }

    case ChgStep4:
    {
        if(pGbChgCtrl->ChgStepBak != pGbChgCtrl->ChgStep)
        {
            pGbChgCtrl->ChgStepBak = pGbChgCtrl->ChgStep;
            GbChgM_TmCnt.RxChgMsg = 0;
        }

        if( (CRO_RX == (lwd_rx_flg & CRO_RX))
                && (CHG_READY == GbChgCan_GetCroChgReady()))/* charger Ready */
        {
            lwd_rx_flg &= ~CRO_RX;
            pGbChgCtrl->Flg.Bro = GB_FLAG_DISABLE;	 /* send Bro disable */
            pGbChgCtrl->ChgStep = ChgStep5;
        }
        else
        {
            if(GbChgM_TmCnt.RxChgMsg < TM_MS(5000))
            {
                pGbChgCtrl->Flg.Bro = GB_FLAG_ENABLE;	 /* send Bro enable */
                pGbChgCtrl->ChgStep = ChgStep4;
            }
            else
            {
                pGbChgCtrl->Flg.Bro = GB_FLAG_DISABLE;	 /* send Bro disable */
                pGbChgCtrl->ConfigErr |= RX_CRO_ERR;
                pGbChgCtrl->ChgStep = ChgStep9;
            }
        }

        break;
    }

    case ChgStep5:
    {
        if(pGbChgCtrl->ChgStepBak != pGbChgCtrl->ChgStep)
        {
            pGbChgCtrl->ChgStepBak = pGbChgCtrl->ChgStep;
            GbChgM_TmCnt.RxChgMsg = 0;
        }

        pGbChgCtrl->Flg.Bcl = GB_FLAG_ENABLE;	 /* send Bcl enable */
        pGbChgCtrl->Flg.Bcs = GB_FLAG_ENABLE;	 /* send Bcs enable */

        GbChgCan_UpdateCntBst(0);
        // GbChgCan_TmCnt.Bst = 0; /* don't send Bst in this step */

        if( CCS_RX == (lwd_rx_flg & CCS_RX) ) /* charger status */
        {
            lwd_rx_flg &= ~CCS_RX;
            GbChgM_TmCnt.RxChgMsg = 0;

            pGbChgCtrl->Flg.Bsm = GB_FLAG_ENABLE;	 /* send Bsm enable */
            pGbChgCtrl->Flg.Bmv = GB_FLAG_ENABLE;	 /* send Bmv enable */
            pGbChgCtrl->Flg.Bmt = GB_FLAG_ENABLE;	 /* send Bmt enable */
            //pGbChgCtrl->Flg.Bsp = GB_FLAG_ENABLE;	 /* send Bsp enable */

            pGbChgCtrl->ChgStep = ChgStep5;
        }
        else
        {
            if(GbChgM_TmCnt.RxChgMsg < TM_MS(1000))
            {
                pGbChgCtrl->ChgStep = ChgStep5;
            }
            else
            {
                pGbChgCtrl->Flg.Bcl = GB_FLAG_DISABLE;	 /* send Bcl disable */
                pGbChgCtrl->Flg.Bcs = GB_FLAG_DISABLE;	 /* send Bcs disable */
                pGbChgCtrl->Flg.Bsm = GB_FLAG_DISABLE;	 /* send Bsm disable */
                pGbChgCtrl->Flg.Bmv = GB_FLAG_DISABLE;	 /* send Bmv disable */
                pGbChgCtrl->Flg.Bmt = GB_FLAG_DISABLE;	 /* send Bmt disable */
                //pGbChgCtrl->Flg.Bsp = GB_FLAG_DISABLE;	 /* send Bsp disable */

                pGbChgCtrl->ChgEndReason3 |= OTHER_ERR; /* other error*/
                pGbChgCtrl->Flg.Bst = GB_FLAG_ENABLE;	 /* send Bst enable */
                pGbChgCtrl->ChargingErr |= RX_CCS_ERR;
                pGbChgCtrl->ChgStep = ChgStep9;
            }
        }

        if( (GB_FLAG_DISABLE == lby_chg_enable_ext)		 /* BMS charge end */
                || (CST_RX == (lwd_rx_flg & CST_RX))	 /* charger charge end */
                || (GB_FLAG_FAIL == lby_dc_link_st) ) /* charge link open */
        {
            lwd_rx_flg &= ~CST_RX;
            pGbChgCtrl->ChgStep = ChgStep6;
            pGbChgCtrl->Flg.Bst = GB_FLAG_ENABLE;	 /* send Bst enable */

            if(GB_FLAG_FAIL == lby_dc_link_st)
            {
                pGbChgCtrl->ChgEndReason2 |= CHG_CON_ERR; /* charge connector error */
            }
        }

        break;
    }

    case ChgStep6:
    {
        if(pGbChgCtrl->ChgStepBak != pGbChgCtrl->ChgStep)
        {
            pGbChgCtrl->ChgStepBak = pGbChgCtrl->ChgStep;
            GbChgM_TmCnt.RxChgMsg = 0;
        }

        pGbChgCtrl->Flg.Bst = GB_FLAG_ENABLE;	 /* send Bst enable */

        pGbChgCtrl->Flg.Bcl = GB_FLAG_DISABLE;	 /* send Bcl disable */
        pGbChgCtrl->Flg.Bcs = GB_FLAG_DISABLE;	 /* send Bcs disable */
        pGbChgCtrl->Flg.Bsm = GB_FLAG_DISABLE;	 /* send Bsm disable */
        pGbChgCtrl->Flg.Bmv = GB_FLAG_DISABLE;	 /* send Bmv disable */
        pGbChgCtrl->Flg.Bmt = GB_FLAG_DISABLE;	 /* send Bmt disable */
        //pGbChgCtrl->Flg.Bsp = GB_FLAG_DISABLE;	 /* send Bsp disable */

        if( (CST_RX == (lwd_rx_flg & CST_RX)) ) /* charger stop msg */
        {
            lwd_rx_flg &= ~CST_RX;

            pGbChgCtrl->ChgStep = ChgStep7;
        }
        else
        {
            if(GbChgM_TmCnt.RxChgMsg < TM_MS(5000))
            {
                pGbChgCtrl->ChgStep = ChgStep6;
            }
            else
            {
                pGbChgCtrl->ChargingErr |= RX_CST_ERR;
                pGbChgCtrl->Flg.Bst = GB_FLAG_DISABLE;	 /* send Bst disable */
                pGbChgCtrl->ChgStep = ChgStep9;
            }
        }

        break;
    }

    case ChgStep7:
    {
        if(pGbChgCtrl->ChgStepBak != pGbChgCtrl->ChgStep)
        {
            pGbChgCtrl->ChgStepBak = pGbChgCtrl->ChgStep;
            GbChgM_TmCnt.RxChgMsg = 0;
        }

        pGbChgCtrl->Flg.Bst = GB_FLAG_DISABLE; /* send Bst disable */
        pGbChgCtrl->Flg.Bsd = GB_FLAG_ENABLE;	 /* send Bsd enable */

        if( CSD_RX == (lwd_rx_flg & CSD_RX) )
        {
            lwd_rx_flg &= ~CSD_RX;
            pGbChgCtrl->ChgStep = ChgStep8;
        }
        else
        {
            if(GbChgM_TmCnt.RxChgMsg < TM_MS(5000))
            {
                pGbChgCtrl->ChgStep = ChgStep7;
            }
            else
            {
                pGbChgCtrl->ChargeEndErr |= RX_CSD_ERR;
                pGbChgCtrl->Flg.Bsd = GB_FLAG_DISABLE;	 // send Bsd disable
                pGbChgCtrl->ChgStep = ChgStep9;
            }
        }

        break;
    }

    case ChgStep8:		//charge Nomal end
    {
        GbChgM_TmCnt.RxChgMsg = 0;
        pGbChgCtrl->Flg.Bsd = GB_FLAG_ENABLE;	 /* send Bsd enable */

        if(CRM_RX == (lwd_rx_flg & CRM_RX))
        {
            lwd_rx_flg = 0;
       //     pGbChgCtrl->Flg.Bsd = GB_FLAG_DISABLE; /* send Bsd disable */
            pGbChgCtrl->ChgStep = ChgStep0;   /* wait handshake again */
            pGbChgCtrl->ChgEndReason1 = 0;
            pGbChgCtrl->ChgEndReason2 = 0;
            pGbChgCtrl->ChgEndReason3 = 0;
            pGbChgCtrl->ChgEndReason4 = 0;
        }

        break;
    }

    case ChgStep9:  /* charge error end */
    {
        GbChgM_TmCnt.RxChgMsg = 0;
        pGbChgCtrl->Flg.Bem = GB_FLAG_ENABLE;	 /* send Bem enable */

        if(CRM_RX == (lwd_rx_flg & CRM_RX))
        {
            lwd_rx_flg = 0;
            pGbChgCtrl->Flg.Bst = GB_FLAG_DISABLE; /* send Bst disable */
            pGbChgCtrl->ChgStep = ChgStep0;   /* wait handshake again */
            pGbChgCtrl->ChgEndReason1 = 0;
            pGbChgCtrl->ChgEndReason2 = 0;
            pGbChgCtrl->ChgEndReason3 = 0;
            pGbChgCtrl->ChgEndReason4 = 0;
        }

        break;
    }

    default:
    {
        break;
    }
    }

    GbChgCan_UpdateRxFlg(lwd_rx_flg);

}


static void GbChgM_AcChg(void)
{
    uByte lby_ac_link_st;
    uByte lby_chg_enable_en;
    uWord lwd_ac_chg_pmt_cur;
    uWord rslt;

    rslt = 0;
    lby_ac_link_st = Chg_GetAcLinkSt();
    lby_chg_enable_en = Chg_GetPermitChgOnSt();
    lwd_ac_chg_pmt_cur = GbChgM_GetAcPmtChgCur();


    if(GB_FLAG_OK == lby_ac_link_st)
    {
        gwd_CntAcLinkFail = 0;
        if(GB_FLAG_ENABLE == lby_chg_enable_en)
        {
            // CHG_S2 = ON;
            rslt = DoIf_Ctrl((uByte)DOIF_CPU_CHG_S_NO, (bool)CHG_S_ON);
        }
        else
        {
            //  CHG_S2 = OFF;
            rslt = DoIf_Ctrl((uByte)DOIF_CPU_CHG_S_NO, (bool)CHG_S_OFF);
        }
    }
    else
    {
        if(gwd_CntAcLinkFail < LINK_FAIL_300MS)
        {
            gwd_CntAcLinkFail++;
        }
        else
        {
            gwd_CntAcLinkFail = 0;
            lby_chg_enable_en = GB_FLAG_DISABLE;
            lwd_ac_chg_pmt_cur = 0;
            //  CHG_S2 = OFF;
            rslt = DoIf_Ctrl((uByte)DOIF_CPU_CHG_S_NO, (bool)CHG_S_OFF);
        }
    }

    Chg_UpdatePermitChgOnSt(lby_chg_enable_en);
    GbChgM_UpdateAcPmtChgCur(lwd_ac_chg_pmt_cur);

    (void)rslt;
}
