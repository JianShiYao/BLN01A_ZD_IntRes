#ifndef SPIIF_H
#define SPIIF_H

#include "Spi_Lcfg.h"

GeneralReturnType SpiIf_WriteReadByte(uByte SpiIf_Id,uByte cmd,uByte *Rd_DataPtr);
GeneralReturnType SpiIf_WriteByte(uByte SpiIf_Id,uByte cmd);
GeneralReturnType SpiIf_ReadByte(uByte SpiIf_Id,uByte *SpiIf_ValuePtr);

#endif /* SPIIF_H */