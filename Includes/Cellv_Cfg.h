//Cellv_cfg.h
#ifndef CELLV_CFG_H
#define CELLV_CFG_H
 
#include "CPUCSCK.h"
#include "CPUCSO.h"
#include "CPUCSI.h"
#include "CPUCCS.h"
#include "DRDY_CELL.h"
#include "EN_CELL.h"
#include "SPI2IF.h"

#define MAX_DEVICE_NUM 4 
          
#define CELLV_READY_VAL()  DRDY_CELL_GetVal()
#define CELLV_EN_CLR       EN_CELL_PutVal(1)
#define CELLV_EN_SET       EN_CELL_PutVal(0)



#endif
