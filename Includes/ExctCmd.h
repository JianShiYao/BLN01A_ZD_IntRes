// ExctCmd.h


#if ((ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BCU_D))

/*BCU project information   */
extern void WR_BCUSysconfProductNo(void);
extern void WR_BCUCellvNum(void);
extern void WR_BCUCellNumPerChip(void);
extern void WR_BCUNoUseCellNumPerChip(void);
extern void WR_BCUCellvStartNo(void);
extern void WR_BCUTemperNum(void);
extern void WR_BCUTemperStartNo(void);
extern void WR_BCUSoc(void);
extern void WR_BCURatesCapActualCap(void);
extern void WR_BCUCfgVer(void);
extern void WR_BCUCfgUpdate(void);
extern void WR_BCUVehiclePlate(void);
extern void WR_BCUSoh(void);
extern void WR_BCUFusePos(void);
extern void WR_BCUSystemClock(void);

extern void RD_BCUSysconfProductNo(void);
extern void RD_BCUCellvNum(void);
extern void RD_BCUCellNumPerChip(void);
extern void RD_BCUNoUseCellNumPerChip(void);
extern void RD_BCUCellvStartNo(void);
extern void RD_BCUTemperNum(void);
extern void RD_BCUTemperStartNo(void);
extern void RD_BCUSoc(void);
extern void RD_BCURatesCapActualCap(void);
extern void RD_BCUCfgVer(void);
extern void RD_BCUCfgUpdate(void);
extern void RD_BCUVehiclePlate(void);
extern void RD_BCUSoh(void);
extern void RD_BCUFusePos(void);
extern void RD_BCUSystemClock(void);


/*BCU thrhd level */
extern void WR_BCUThrhdLvl1(void);
extern void WR_BCUThrhdLvl2(void);
extern void WR_BCUThrhdLvl3(void);

extern void RD_BCUThrhdLvl1(void);
extern void RD_BCUThrhdLvl2(void);
extern void RD_BCUThrhdLvl3(void);

/*BCU control information */
extern void WR_BCUHeatControl(void);
extern void WR_BCUChargeControl(void);

extern void RD_BCUHeatControl(void);
extern void RD_BCUChargeControl(void);

/*BCU history information  */
extern void WR_BCUHistoryCellvInfo(void);
extern void WR_BCUHistoryTemperInfo(void);
extern void WR_BCUHistoryLowTemperArea(void);
extern void WR_BCUHistoryHighTemperArea(void);
extern void WR_BCUHistoryAvrgTemperArea(void);
extern void WR_BCUHistoryDetTemperArea(void);
extern void WR_BCUHistoryPowerInfo(void);
extern void WR_BCUHistoryCurrentArea(void);
extern void WR_BCUHistorySocInfo(void);
extern void WR_BCUHistoryCapacityInfo(void);

extern void RD_BCUHistoryCellvInfo(void);
extern void RD_BCUHistoryTemperInfo(void);
extern void RD_BCUHistoryLowTemperArea(void);
extern void RD_BCUHistoryHighTemperArea(void);
extern void RD_BCUHistoryAvrgTemperArea(void);
extern void RD_BCUHistoryDetTemperArea(void);
extern void RD_BCUHistoryPowerInfo(void);
extern void RD_BCUHistoryCurrentArea(void);
extern void RD_BCUHistorySocInfo(void);
extern void RD_BCUHistoryCapacityInfo(void);

/*BCU battery information */
extern void WR_BCUBatPackInfo1(void);
extern void WR_BCUBatPackInfo2(void);
extern void WR_BCUBatPackInfo3(void);
extern void WR_BCUBatPackInfo4(void);

extern void RD_BCUBatPackInfo1(void);
extern void RD_BCUBatPackInfo2(void);
extern void RD_BCUBatPackInfo3(void);
extern void RD_BCUBatPackInfo4(void);

/*BCU battery system information */
extern void RD_BCUBatsysInfo1(void);
extern void RD_BCUBatsysInfo2(void);
extern void RD_BCUBatsysInfo3(void); 

extern void Wr_2dCode(void);
extern void Rd_2dCode(void);
#endif

/* hard details errcode */
extern void RD_HDErrInfo1(void);
extern void RD_HDErrInfo2(void);
extern void RD_HDErrInfo3(void);
extern void RD_HDErrInfo4(void);
extern void RD_HDErrInfo5(void);
extern void RD_HDErrInfo6(void);
extern void RD_HDErrInfo7(void);

/* read version information */ 
extern void RD_GetProjectVer(void);
extern void RD_GetPlatVer(void);
extern void RD_GetModuleVer(void);
extern void RD_GetHardwareVer(void);

#if ((ECU_CATEGORY == M_BMU) || (ECU_CATEGORY == M_BMU_R))

/*BMU project information */
extern void WR_BMUBatteryNum(void);
extern void WR_BMUCellNumPerChip(void);
extern void WR_BMUFusePosition(void);
extern void WR_BMUTemperNum(void);
extern void WR_BMUHeatManagePara(void);
extern void WR_BMUNum(void);

extern void RD_BMUBatteryNum(void);
extern void RD_BMUCellNumPerChip(void);
extern void RD_BMUFusePosition(void);
extern void RD_BMUTemperNum(void);
extern void RD_BMUHeatManagePara(void);
extern void RD_BMUNum(void);

/*BMU thrhd level */ 
extern void WR_BMUThrhdLvl1(void);
extern void WR_BMUThrhdLvl2(void);
extern void WR_BMUThrhdLvl3(void);

extern void RD_BMUThrhdLvl1(void);
extern void RD_BMUThrhdLvl2(void);
extern void RD_BMUThrhdLvl3(void);

/*BMU Kuai huan information */ 
extern void WR_BMUKHBatteryPackInfo1(void);
extern void WR_BMUKHBatteryPackInfo2(void);
extern void WR_BMUKHBatteryPackInfo3(void);
extern void WR_BMUKHBatteryPackInfo4(void);
extern void WR_BMUKHSoc(void);
extern void WR_BMUKHVehiclePlate(void);
extern void WR_BMUKHChargeControlPara(void);

extern void RD_BMUKHBatteryPackInfo1(void);
extern void RD_BMUKHBatteryPackInfo2(void);
extern void RD_BMUKHBatteryPackInfo3(void);
extern void RD_BMUKHBatteryPackInfo4(void);
extern void RD_BMUKHSoc(void);
extern void RD_BMUKHVehiclePlate(void);
extern void RD_BMUKHChargeControlPara(void);

/*BMU bal manage para */ 
extern void WR_BMUBalCtrlPara1(void);
extern void WR_BMUBalCtrlPara2(void);

extern void RD_BMUBalCtrlPara1(void);
extern void RD_BMUBalCtrlPara2(void);


#endif
