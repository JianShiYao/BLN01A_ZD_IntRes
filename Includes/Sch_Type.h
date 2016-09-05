// Sch_Type.h
#ifndef SCH_TYPE_H
#define SCH_TYPE_h

typedef enum
  {
    TIMER_TASK_CLASS,
    MAIN_TASK_CLASS,
  }eTaskClassType; 
  
  
typedef void (* TaskPtrType)(void);  

typedef struct
  {
   eTaskClassType TaskClass;    
   TaskPtrType TaskPtr;
  }sTaskType;

typedef enum
  {
   BYTE_TM,
   WORD_TM,
   LWORD_TM,   
  }eTimerClasType;
  

 

#endif /* SCH_MAIN_H */