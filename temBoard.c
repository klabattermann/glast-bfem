

#include <stdio.h>
#include <windows.h>
#include "vmeAdrs.h"
#include "glast.h"

/* --------------------------------------------

void temSetCheckSum (int value)
int temGetCheckSum ()
void temEnableCable (int cableNr)
void temDisableCable (int cableNr)
int temIsCableEnabled (int cableNr)
void temRstLastGtrc ()
void temLastGtrc (int addr, int cable)
void temRstPulse ()
void temRstDataFifo ()
void temInit ()
void temStatus()
void temRegister()
void temMaskReg()
void temReset()
void temR ()
void temTreq ()
void temTreq1 ()
void temDF()
void rstOn(int mode)


   ----------------------------------------- */


/* ----------------------------------- 
   Check Sum 
   ----------------------------------- */
   

void temSetCheckSum (int value)
{
    
  unsigned long tmpCblen = *t_cblen;

  if ( value >= 1 ) {
    tmpCblen |= 0x8000;
  } else {
    tmpCblen &= 0x7fff;
  }

  /*tmpCblen = (value >= 1) ? tmpCblen |= 0x8000 : tmpCblen &= 0x7fff; */

  *t_cblen = tmpCblen;

  printf(" Check sum: %x \n", tmpCblen);
  return;

}


int temGetCheckSum ()
{
  
  unsigned long tmpCblen = *t_cblen;
  
  if ( (tmpCblen & 0x8000) != 0 ) {
    printf(" check sum is on \n");
    return 1;
  }
  else {
    printf(" check sum is off \n");
    return 0;
  }    
}


/* ------------------------------------
   Enable Cables 
   ------------------------------------ */

void temEnableCable (int cableNr)
{
  
  unsigned long enableBit;

  if ( cableNr < -1 || cableNr > 7 ) return;
  
  enableBit = (cableNr == -1) ?  enableBit = 0x0ff  :  0x1 << cableNr;  

  *t_cblen |= enableBit;

}


void temDisableCable (int cableNr)
{

  unsigned long tmpCblen;
  unsigned long disBit = 0x0;
  
  if ( cableNr < -1 || cableNr > 7 ) return;
    
  if ( cableNr > -1 ) disBit = (0xff & ~(0x1 << cableNr));
  disBit |= 0x8000;
  

  tmpCblen = *t_cblen;
  tmpCblen &= disBit;
 
  *t_cblen = tmpCblen;
}


int temIsCableEnabled (int cableNr)
{

  unsigned long tmpCblen = *t_cblen;
  if ( (tmpCblen & 0x1 << cableNr) != 0 ) return 1;
  return 0;

}

void temEnabledCables (unsigned long *cblenReg)
{
  *cblenReg = *t_cblen;
}




/* -----------------------
   Last Gtrc
   ----------------------- */


void temRstLastGtrc ()
{

    int i;
    for ( i = 0; i < 4; i++ ) {
        *(t_lastCntrl + i) = 0x0;
    }
    
}


void temLastGtrc (int addr, int cable)
{

    unsigned long addrBits = addr;
    unsigned long maskBits = 0x1f;
    
    unsigned long lastGtrc;
    int ind = cable / 2;
    
  
    if ( addr  < 0 || addr  > 31 ) return;
    if ( cable < 0 || cable >  7 ) return;
    
    if ( cable % 2 == 1 ) { 
      addrBits = addrBits << 8;
      maskBits = maskBits << 8;
    }

    lastGtrc = *(t_lastCntrl + ind);
    lastGtrc &= ~maskBits;
    lastGtrc |= addrBits;
    
    *(t_lastCntrl + ind) = lastGtrc;
    
}


/* -------------------
   Resets
   ------------------- */

void temRstPulse ()
{
    tkr_rwrite(t_brdCntl, 0x1b07);
    tkr_rwrite(t_brdCntl, 0x1b03);   
}


void temRstDataFifo ()
{
    tkr_rwrite(t_brdCntl, 0x1b01);
    tkr_rwrite(t_brdCntl, 0x1b03);
}


/* ------------------
   Tem
   ------------------ */

void temInit ()
{  
    temSetCheckSum (0);
    temRstLastGtrc ();    
    temDisableCable (-1); 
    
    *t_mskxl1 = 0x0;
    *t_mskxr1 = 0x0;
    *t_mskyl1 = 0x0;
    *t_mskyr1 = 0x0;
}

void temStatus()
{
  
    unsigned long *status = t_brdStat;
    unsigned long *cmd = t_brdCntl;
    unsigned long *result;
  
    printf(" status %x\n", *status);
  
    if ( (*status & TKR_STATUS) == 0 ) printf("\nFPGA program error");
    if ( (*status & TKR_CONF_DONE) == 0 ) printf("\nFPGA not programmed");
    
    printf("\nThe board is ");
    if ( (*cmd & 1) != 0 ) printf("not ");
    printf("reset");
    
    printf("\nTKRrigger is  ");
    if ( (*cmd & TKR_RESET) == 0 ) printf("not ");
    printf("reset");
    
    printf("\nFIFO ");
    if ( (*status & TKR_FIFO_EMPTY) == 0 ) printf("is empty");
    else if ( (*status & TKR_FIFO_HALF_FULL) == 0) printf("is half full");
    else if ( (*status & TKR_FIFO_FULL) == 0 ) printf("is full");
    else if ( (*status & TKR_FIFO_HAS_DATA) == TKR_FIFO_HAS_DATA) printf("has data");
    else printf("is out of sync ,%lx",*status);
    printf("\n");
    
}

/* ----------------
   Register
   ---------------- */

void temRegister()
{
    printf (" tcntlreg : %8x \n", *t_lcntlReg);
    printf (" brdCntl  : %8x   %8x\n", *t_brdCntl, t_brdCntl);
    printf (" brdStat  : %8x   %8x\n", *t_brdStat, t_brdStat);
    printf (" last 10  : %8x \n", *t_lastCntrl);
    printf (" last 32  : %8x \n", *(t_lastCntrl+1));
    printf (" last 54  : %8x \n", *(t_lastCntrl+2));
    printf (" last 76  : %8x \n", *(t_lastCntrl+3));
    printf (" cblen    : %8x \n", *t_cblen);
    
    
    printf (" cmd0    : %8x \n", *t_tkrCmd);
}

/* ================================ */
/*          L1T Masks               */
/* ================================ */


void temMaskReg()
{
    printf (" maskxl1   : %8x  maskxr1  : %8x\n", *t_mskxl1, *t_mskxr1);
    printf (" maskyl1   : %8x  maskyr1  : %8x\n", *t_mskyl1, *t_mskyr1);
    printf (" coinxen1  : %8x  coinyen1 : %8x\n", *t_coinxen1, *t_coinyen1);
    printf (" coinplen1 : %8x\n", *t_coinplen1);
}


/* ================================ */
/*                                  */
/* ================================ */

void temReset()
{
    unsigned long origCmd = 0;

    origCmd = tkr_rread(t_brdCntl);    
    printf ("tem reset: brd-cntl = %x\n", origCmd);
    
    trk_rwrite(t_brdCntl, origCmd | 0x4);
    trk_rwrite(t_brdCntl, origCmd | 0x1);
    trk_rwrite(t_brdCntl, origCmd | 0x6);
    trk_rwrite(t_brdCntl, origCmd | 0x2);
    
    trk_rwrite(t_brdCntl, 0x1b03);    
}

void temR ()
{
    unsigned long regValue = 0;

    regValue = tkr_rread(t_brdCntl);
    printf ("reset temR%x\n", regValue);
    regValue &= ~0x2;
    tkr_rwrite(t_brdCntl, regValue);

    regValue = tkr_rread(t_brdCntl);
    printf ("reset temR %x\n", regValue);
    regValue |= 0x2;
    tkr_rwrite(t_brdCntl, regValue);

    regValue = tkr_rread(t_brdCntl);
    printf ("reset temR %x\n", regValue);
    regValue &= ~0x1;
    tkr_rwrite(t_brdCntl, regValue);

    regValue = tkr_rread(t_brdCntl);
    printf ("reset temR %x\n", regValue);
    regValue |= 0x1;
    tkr_rwrite(t_brdCntl, regValue);

    printf ("reset temR %x\n", tkr_rread(t_brdCntl));
}



/* -------------------- */
/*   software trigger   */
/* -------------------- */

void temTreq ()
{
    tkr_rwrite(t_tstMisc, tkr_rread(t_tstMisc) |= 0x80);
    tkr_rwrite(t_tstMisc, tkr_rread(t_tstMisc) &= ~0x80);
}

void temTreq1 ()
{
    printf (" tstMisc %x\n", *t_tstMisc);
    *t_tstMisc |=  0x1;
    printf (" tstMisc %x\n", *t_tstMisc);
    *t_tstMisc &= ~0x1;
    printf (" tstMisc %x\n", *t_tstMisc);
    
}





void temDF()
{
  printf (" %x\n", *t_tkrFifo);
}



void rstOn(int mode)
{
  if ( mode == 1 ) {
    *t_brdCntl = 0x1b07;
  } else {
    *t_brdCntl = 0x1b03;
  }
  
}
















