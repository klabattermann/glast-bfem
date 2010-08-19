
#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#include "vmeAdrs.h"

void temEnableCable(int cableNr);
void temDisableCable(int cableNr);
int temIsCableEnabled(int cableNr);
//void mySleep(int loops); This uses another system for sleep so I included windows.h and used the more modern sleep() function


const unsigned long  cmd_load_gtrcReg = 0x0;
const unsigned long  cmd_clearEvt     = 0x1;
const unsigned long  cmd_readEvt      = 0x2;
const unsigned long  cmd_clkOn        = 0x4;
const unsigned long  cmd_rstGtrc      = 0x7;
const unsigned long  cmd_load_gtfeReg = 0xc003;
const unsigned long  cmd_rstFifo      = 0xb006;
const unsigned long  cmd_rstGtfe      = 0xd006;
const unsigned long  cmd_strobe       = 0xe005;




/* --------------------------------------------- */
/*                                               */
/* --------------------------------------------- */


void tkrCmd_execute (unsigned long *cmd, int length)
{
    
    int i;
    int cable;

    /* printf("tkr CMD %x\n", *cmd); */
   
    for ( i = 1; i < length; i++ )  {
        *(t_tkrCmd + i) = cmd[i];
    }
    

    cable = 0x7 & (cmd[0] >> 8);
  
    if ( ! temIsCableEnabled(cable) ) {
        temEnableCable(cable);
        *t_tkrCmd = cmd[0];
        Sleep(100);              /* sleep a little bit so that all bits get shifted out */
        temDisableCable(cable);
    } else {
        *t_tkrCmd = cmd[0];
    }
    
}



void tkrCmd_gtrc (const unsigned long cmd, int gtrcAdrs, int cable)
{
   
    unsigned long cmd_tkr = 0xff & cmd;
   
    cmd_tkr |= 0x700 & (cable << 8);
    cmd_tkr |= 0xf8 & (gtrcAdrs << 3);
    
    tkrCmd_execute (&cmd_tkr, 1);
    
    if ( cmd == cmd_readEvt ) {
        printf ( " read evt :  %x\n", cmd_tkr);
    }
    
}

void tkrCmd_gtrcHeader (const unsigned long cmd, int gtrcAdrs, int cable, 
                        unsigned long * cmdWord)
{
   
    unsigned long cmd_tkr = 0xff & cmd;
   
    cmd_tkr |= 0x700 & (cable << 8);
    cmd_tkr |= 0xf8 & (gtrcAdrs << 3);
    
    *cmdWord = cmd_tkr;
    
}




void tkrCmd_gtfe (const unsigned long cmd, int gtfeAdrs, int gtrcAdrs, int cable)
{
   
    unsigned long cmd_tkr[3] = {0,0,0};
    int inv_gtfeAdrs = 0; 
    int i;
    
   
    tkrCmd_gtrcHeader(cmd, gtrcAdrs, cable, cmd_tkr);

    cmd_tkr[1] = 0xf0 & (cmd >> 8);    
      
    // reverse bit order for GTFE chip adress   
   
    for ( i = 0; i < 6; i++ )  {
        if ( (gtfeAdrs >> i) & 0x1 )  inv_gtfeAdrs |= 0x1 << (4 - i);
    } 
    
    cmd_tkr[1] |= 0x0f & (inv_gtfeAdrs >> 1);
    cmd_tkr[2] |= 0x80 & (inv_gtfeAdrs << 7);
   
 
    tkrCmd_execute(cmd_tkr, 3);

}


void tkrCmd_gtfeHeader (const unsigned long cmd, int gtfeAdrs, int gtrcAdrs, int cable,
                        unsigned long *cmdWord)
{
   
    unsigned long cmd_tkr[3] = {0,0,0};
    int inv_gtfeAdrs = 0; 
    int i;
    
   
    tkrCmd_gtrcHeader(cmd, gtrcAdrs, cable, cmd_tkr);

    cmd_tkr[1] = 0xf0 & (cmd >> 8);    
      
    // reverse bit order for GTFE chip adress   
    
    for ( i = 0; i < 6; i++ )  {
        if ( (gtfeAdrs >> i) & 0x1 )  inv_gtfeAdrs |= 0x1 << (4 - i);
    } 
   
    cmd_tkr[1] |= 0x0f & (inv_gtfeAdrs >> 1);
    cmd_tkr[2] |= 0x80 & (inv_gtfeAdrs << 7);
    
    cmdWord[0] = cmd_tkr[0];
    cmdWord[1] = cmd_tkr[1];
    cmdWord[2] = cmd_tkr[2];
}



/* ------------------------------------------ */
/*     gtrc commands                          */
/* -----------------------------------------  */


void tkrCmd_rstGtrc (int gtrcAdrs, int cable)
{
    
    tkrCmd_gtrc(cmd_rstGtrc, gtrcAdrs, cable);
}


void tkrCmd_clockOn (int gtrcNr, int cableNr)
{   
    tkrCmd_gtrc (cmd_clkOn, gtrcNr, cableNr);
    
}

void tkrCmd_readEvt (int gtrcAdrs, int cable)
{    
    tkrCmd_gtrc(cmd_readEvt, gtrcAdrs, cable);
}



void tkrCmd_gtrcReg(int gtrcNr, int cableNr, int nChipsToRead, int checkSum)
{
    
    unsigned long tmp_reg[2];

    tkrCmd_gtrcHeader(cmd_load_gtrcReg, gtrcNr, cableNr, tmp_reg);

    if ( checkSum > 0 ) {
        tmp_reg[1] = 0x60;
    } else {
        tmp_reg[1] = 0x40;
    }
    
    tmp_reg[1] |= 0x1f & nChipsToRead; 
    
    tkrCmd_execute (tmp_reg, 2);
}



/* --------------------------------------------- */
/*    gtfe commands                              */
/* --------------------------------------------- */


void tkrCmd_rstGtfe (int gtfeNr, int gtrcNr, int cableNr)
{
    tkrCmd_gtfe (cmd_rstGtfe, gtfeNr, gtrcNr, cableNr);
}


void tkrCmd_rstGtfeFifo (int gtfeNr, int gtrcNr, int cableNr)
{
    tkrCmd_gtfe (cmd_rstFifo, gtfeNr, gtrcNr, cableNr);
}


void tkrCmd_strobe (int gtfeNr, int gtrcNr, int cableNr)
{
    tkrCmd_gtfe (cmd_strobe, gtfeNr, gtrcNr, cableNr);
}



void tkrCmd_gtfeReg (int gtfeAdrs, int gtrcAdrs, int cableNr,
                     int calDac, int threshDac, int readDir,
                     unsigned long calMask0, unsigned long calMask1,
                     unsigned long chanMask0, unsigned long chanMask1,
                     unsigned long trigMask0, unsigned long trigMask1)
    
{
  
    unsigned long t_cmd[28];
    unsigned long t_regdata[7];
    unsigned long tmp_reg[2] = {0,0};
    unsigned long pt_reg;
    int i, ind_cmd;
    

    for ( i = 0; i < 28; i++ )  t_cmd[i] = 0;
  

    /* command header gtrc, gtfe */

    tkrCmd_gtfeHeader (cmd_load_gtfeReg, gtfeAdrs, gtrcAdrs, cableNr, t_cmd);
  
    /* fill dac values and direction */
    
    t_regdata[6] = 0;

    t_regdata[6] |= (calDac & 0x7f) << 25;
    t_regdata[6] |= (threshDac & 0x7f) << 18;

 
    if ( readDir > 0 )  {
        t_regdata[6] |= 0x00030000UL;
    } else {
        t_regdata[6] &= 0xfffc0000UL;
    }
 

  
  /* ---------------------------------------------------------------- */

  /*  reverse the bit pattern for the chan-mask */

    for ( i = 0; i < 32; i++ ) {
        if ( (chanMask0 >> i) & 0x1 )  tmp_reg[1] |= 0x1 << (31 - i);
        if ( (chanMask1 >> i) & 0x1 )  tmp_reg[0] |= 0x1 << (31 - i);
    }
    
  
    t_regdata[0] = calMask0;
    t_regdata[1] = calMask1;
    t_regdata[2] = tmp_reg[0];
    t_regdata[3] = tmp_reg[1];
    t_regdata[4] = trigMask0;
    t_regdata[5] = trigMask1;

    /*
      printf (" %x %x   %x\n", t_regdata[0], t_regdata[1], (t_regdata[0] >> 25) );
      printf (" %x %x   %x\n", t_regdata[2], t_regdata[3], (t_regdata[0] >> 25) );
      printf (" %x %x   %x\n", t_regdata[4], t_regdata[5], (t_regdata[0] >> 25) );
    */
  
    ind_cmd = 2;
    for ( i = 0; i < 7 ; i++ ) {
    
        pt_reg = t_regdata[i];
      
        t_cmd[ind_cmd]   |= (pt_reg >> 25) & 0x7f;
        t_cmd[ind_cmd+1] |= (pt_reg >> 17) & 0xff;
        if ( i != 6 ) {
            t_cmd[ind_cmd+2] |= (pt_reg >>  9) & 0xff;
            t_cmd[ind_cmd+3] |= (pt_reg >>  1) & 0xff;
            t_cmd[ind_cmd+4] = (pt_reg <<  7) & 0x80;
        }
        ind_cmd += 4;
    }
    
    /* 
       for ( i = 0; i < 28; i++ ) {
       printf (" %d  %x \n", i, t_cmd[i]);
       }
    */
    
    tkrCmd_execute (t_cmd, 28); 
    
}



void tkrCmd_gtfeRegt ()
{
    
    unsigned long t_cmd[28];
    int i;
    
    tkrCmd_gtfeHeader (cmd_load_gtfeReg, 31, 31, 5, t_cmd);
    
    t_cmd[2] |= 0xefffffff;
    for ( i = 3; i < 28; i++ ) {
        t_cmd[i] = 0xffffffff;
    }
    
}



