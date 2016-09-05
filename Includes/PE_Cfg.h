// PE_cfg.h
#ifndef PE_CFG_H
#define PE_CFG_H

/*     
 * Define switch for pe use call back interface
 * When Use PE independent Compile,need close this switch
 * When Add Call Back to Pe Event or mcal,need Use #ifdef PE_CBK_EN/#endif
 * This default switch status is open, when closed, must not commit to version control
 */
#define PE_CBK_EN

#endif /* PE_CFG_H */