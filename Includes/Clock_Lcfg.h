 // Clock_Lcfg.h
#ifndef CLOCK_LCFG_H
#define CLOCK_LCFG_H

typedef struct
{
    const void (*SetInput)(void);
    const void (*SetOutput)(void);
    const void (*SetVal)(void);
    const void (*ClrVal)(void);
    const bool (*GetVal)(void);
}sClock_IoOperationType;

typedef struct 
{
    sClock_IoOperationType Clock_Scl;
    sClock_IoOperationType Clock_Sda;
    sClock_IoOperationType Clock_Int;
}sClock_OperationType;


extern const sClock_OperationType Clock_Operation;

#endif