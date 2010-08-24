#include <stdio.h>
#include <stdlib.h>
#include "vmeAdrs.h"

//#ifdef WIN32
#include "nivxi.h"
#include <windows.h>
//#else
//#include "nivxi_wk.h"
//#endif

/*#ifdef WIN32
#define sleep(mu)  Sleep(mu)
#else
#include <unistd.h>
#define sleep(mu)  usleep(mu)
#endif
*/
//unsigned long tkr_rread(unsigned long *);

/* ---------------- */
/*    CONSTANTS     */
/* ---------------- */

const int TKR_DATA_SHIFT = 8;
const int L1T_DATA_SHIFT = 11;

const unsigned long TKR_DATA       = 0x100;
const unsigned long TKR_DATA_NOT   = 0xfffffeff;
const unsigned long TKR_N_CONF     = 0x200;
const unsigned long TKR_N_CONF_NOT = 0xfffffdff;
const unsigned long TKR_CLOCK      = 0x400;
const unsigned long TKR_CLOCK_NOT  = 0xfffffbff;

const unsigned long TKR_CONF_DONE      = 0x4;
const unsigned long TKR_STATUS         = 0x8;
const unsigned long TKR_RESET          = 0x4;
const unsigned long TKR_FIFO_EMPTY     = 0x11110000;
const unsigned long TKR_FIFO_HALF_FULL = 0x22220000;
const unsigned long TKR_FIFO_FULL      = 0x44440000;
const unsigned long TKR_FIFO_HAS_DATA  = 0x11110000;


const unsigned long L1T_DATA           = 0x800;
const unsigned long L1T_DATA_NOT       = 0xfffff7ff;
const unsigned long L1T_N_CONF         = 0x1000;
const unsigned long L1T_N_CONF_NOT     = 0xffffefff;
const unsigned long L1T_CLOCK          = 0x2000;
const unsigned long L1T_CLOCK_NOT      = 0xffffdfff;
const unsigned long L1T_CONF_DONE      = 0x1;
const unsigned long L1T_STATUS         = 0x2;
const unsigned long L1T_FIFO_EMPTY     = 0x1000;
const unsigned long L1T_FIFO_HALF_FULL = 0x2000;
const unsigned long L1T_FIFO_FULL      = 0x4000;
const unsigned long L1T_FIFO_HAS_DATA  = 0x1000;


/* --------------------------------- */
/*  read and write TEM vme register  */
/* --------------------------------- */


unsigned long tkr_rread(unsigned long *adr) {
    
    unsigned long value = *adr;
    
    Sleep(1);
    
    return value;
}

int tkr_rwrite(unsigned long *adr, unsigned long value) {
    
    int i,j;
    /* printf("write %x %x \n", adr, value); */
    
    *adr = value;
    for ( i=0; i<1000; i++ ) {
        j += i*i;
    }  
    
    //sleep(1);
    return j;
    //return 1;
}

/* ------------------------------------------------ */
/*  read and write variable sleep TEM vme register  */
/* ------------------------------------------------ */


int tkr_rwrite_wait(unsigned long *adr, unsigned long value, int sleep_mu) {
    *adr = value;
    Sleep(sleep_mu);
    return 1;
}


/* ------------------------------------- */
/* initialize the TEM VME address space  */
/* ------------------------------------- */

void tkrVMEInit (unsigned long vmeBaseAdrs)
{

    unsigned long   window;
    short stat;
    INT16 ret;

    ret = InitVXIlibrary(); 
    
    printf (" init VXI lib %d\n", ret);
    
    t_brdBase = (unsigned long*) MapVXIAddress(0x3, 0x8000000, 0x1, &window, &stat);  

    t_tkrFifo = t_brdBase;    
    t_l1tFifo = t_brdBase + 0x4;
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
    
    t_tcntlReg = t_brdBase + 0xa0;

    t_lcntlReg = t_brdBase + 0xa0;

}



int tkrVMEClose()
{
    return CloseVXIlibrary();
}

