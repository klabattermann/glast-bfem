

#include "nivxi.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "vmeAdrs.h"


#ifdef WIN32
#define sleep(mu)  Sleep(mu)
#else
#include <unistd.h>
#define sleep(mu)  usleep(mu)
#endif

unsigned long tkr_rread(unsigned long *);

/* --------------------------------- */
/*  read and write TEM vme register  */
/* --------------------------------- */


unsigned long tkr_rread(unsigned long *adr) {
    
    unsigned long value = *adr;
    sleep(1);
    
    return value;
}

int tkr_rwrite(unsigned long *adr, unsigned long value) {
    
    /* printf("write %x %x \n", adr, value); */
    
    *adr = value;
    //sleep(1);
    
    return 1;
}

/* ------------------------------------- */
/* initialize the TEM VME address space  */
/* ------------------------------------- */

tkrVMEInit (unsigned long vmeBaseAdrs)
{

    unsigned long   window;
    short stat;
    INT16 ret;

    ret = InitVXIlibrary(); 
    
    printf (" init VXI lib %d\n", ret);
    
    t_brdBase = (unsigned long*) MapVXIAddress(0x3, 0x8000000, 0x1, &window, &stat);  
    
  
    t_l1tFifo = t_brdBase + 0x4;
    t_tkrFifo = t_brdBase;
  
    t_brdCntl = t_brdBase + 0x8;
    t_brdStat = t_brdBase + 0xc;
    
    printf ("%x   %x %x %d\n", stat, t_brdBase, t_brdCntl, sizeof(long));

 
    t_cblen     = t_brdBase + 0xa5;
    t_lastCntrl = t_brdBase + 0xa1; 
  
    t_tkrCmd = t_brdBase + 0x40;
  
    t_mskxl1 = t_brdBase + 0x87;
    t_mskxr1 = t_brdBase + 0x89;
    t_mskyl1 = t_brdBase + 0x8b;
    t_mskyr1 = t_brdBase + 0x8d;
    
    t_coinxen1 = t_brdBase + 0x81;
    t_coinyen1 = t_brdBase + 0x83;
    t_coinplen1 = t_brdBase + 0x85;
    
    t_mskMisc = t_brdBase + 0x8f;
    t_tstMisc = t_brdBase + 0x94;
    
    t_tcntlreg = t_brdBase + 0xa0;
}



int tkrVMEClose()
{
    return CloseVXIlibrary();
}





