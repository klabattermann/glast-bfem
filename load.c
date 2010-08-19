#include <stdio.h>
#include <windows.h>
#include "vmeAdrs.h"
//#include "glast.h"


static const long a = 12;

/* ---------------------------------------- */
/*   load data fpga                         */
/* ---------------------------------------- */

int tkrLoadDataFifo (char *fileName)
{
   
    FILE *cfp;
    int x;
    int loopDelay = 250;

    
    unsigned long *reg = t_brdCntl; 
    unsigned long *status = t_brdStat;
    unsigned long regOrig;
    unsigned long bits = 0;
    unsigned long val;
    unsigned long bits1 = 0;


    regOrig = tkr_rread(reg);
    
    printf("brdStat, brdCntl %x %x\n", *t_brdStat, *t_brdCntl);
    
    regOrig = regOrig & TKR_DATA_NOT & TKR_N_CONF_NOT & TKR_CLOCK_NOT;
    tkr_rwrite(reg, regOrig);
    
    if ( (cfp = fopen(fileName,"r")) == NULL ) {
        printf("%s not found\n",fileName);  
        return(-1);
    }
    
    if ( ( tkr_rread(status) & TKR_CONF_DONE ) !=0 )  return(-2);
    regOrig = regOrig | TKR_N_CONF;
    tkr_rwrite(reg, regOrig);

    while ( fscanf(cfp,"%d,",&val) != EOF ) {
      //printf("BBBBITS %d\n", bits);
        for ( x = 0; x < 8; x++ ) {
            bits++;
            
            regOrig = (regOrig & TKR_DATA_NOT) | (( val & 0x1) << TKR_DATA_SHIFT);
            tkr_rwrite(reg, regOrig);
            
            val = val >> 1;
            
            regOrig = ( regOrig | TKR_CLOCK );
            tkr_rwrite(reg, regOrig);
    
            regOrig = ( regOrig & TKR_CLOCK_NOT );
            tkr_rwrite(reg, regOrig);
        }
    }
    
    bits1 = bits;
    fclose(cfp);
    
    for ( x = 0; x < 10; x++ ) {
        bits++;
        regOrig = ( regOrig | TKR_CLOCK);
        tkr_rwrite(reg, regOrig);
        
        regOrig = ( regOrig & TKR_CLOCK_NOT );
        tkr_rwrite(reg, regOrig);
        /*printf("stat %x\n", tkr_rread(status)); */
    }
    
    if ( (*status & TKR_CONF_DONE) == 0 )  {
        printf(" status = %x \n", tkr_rread(status));
        printf("Data loading failed\n");
        printf(" bits = %d %d\n", bits, bits1);
        return(-3);
    }
    
    printf(" bits = %d %d\n", bits, bits1);
    return(0);
    
}


/* ---------------------------------------- */
/*   load L1T FPGA                          */
/* ---------------------------------------- */


int tkrLoadL1tFifo(char *fileName)
{
   
    FILE  *cfp;
    int x;
  
    unsigned long *reg = t_brdCntl;
    unsigned long *status = t_brdStat;
    
    unsigned long regOrig = *reg;
    unsigned long bits = 0;   
    unsigned long val;
    unsigned long bits1 = 0;
    
  
    regOrig = tkr_rread(reg);

	printf("brdStat, brdCntl %x %x\n", *t_brdStat, *t_brdCntl);

    regOrig = regOrig & L1T_DATA_NOT & L1T_N_CONF_NOT & L1T_CLOCK_NOT;
    tkr_rwrite(reg, regOrig);

    
    if ( (cfp = fopen(fileName,"r")) == NULL) {
        printf("%s not found\n",fileName);
        return(-1);
    }


    Sleep(10);

	if ( (tkr_rread(status) & L1T_CONF_DONE) != 0 ) { 
        return(-2);
    }
  
    regOrig = regOrig | L1T_N_CONF;
    tkr_rwrite(reg, regOrig); 
  
    while ( fscanf(cfp,"%d,",&val) != EOF ) {
        for ( x = 0; x < 8; x++ ) {
            bits++;
            
            regOrig = ( regOrig & L1T_DATA_NOT ) | ( (val&1) << L1T_DATA_SHIFT );
            tkr_rwrite(reg, regOrig);
            
            val = val >> 1;
            regOrig = (regOrig | L1T_CLOCK);
            tkr_rwrite(reg, regOrig);

            regOrig = (regOrig & L1T_CLOCK_NOT);
            tkr_rwrite(reg, regOrig);
        }
    }
    

    bits1 = bits;
    fclose(cfp);
  
    for( x = 0; x < 30; x++)  {
        bits++;
        regOrig = (regOrig | L1T_CLOCK);
        tkr_rwrite(reg, regOrig);

        regOrig = (regOrig & L1T_CLOCK_NOT);
        tkr_rwrite(reg, regOrig);
    }
    
    if ( (*status & L1T_CONF_DONE) == 0) {
        printf(" status = %x \n", tkr_rread(status));
        printf("L1t loading failed\n");
        printf ("bits=%ld  %ld\n", bits, bits1);
        return(-3);
    }
    printf(" status = %x \n", tkr_rread(status));  
    printf ("bits=%ld  %ld\n", bits, bits1);
    return(0);
    
}


int tkrLoadFinalize ()
{

    unsigned long tmpCntl;
  

    tmpCntl = tkr_rread(t_brdCntl);
    
    tmpCntl &= 0xfffffffe;
    tkr_rwrite(t_brdCntl, tmpCntl);
    
    tmpCntl = tkr_rread(t_brdCntl) | 0x1;
    tkr_rwrite(t_brdCntl, tmpCntl);
    
    printf (" finalize loading %x\n",  tkr_rread(t_brdCntl));
    
}


