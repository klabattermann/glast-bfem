

#include <stdio.h>
#include "vmeAdrs.h"
#include "glast.h"



/* ---------------------------------------- */
/*   save data fifo                         */
/* ---------------------------------------- */


int tkrDump()
{
    /* read the a word from the data and L1T FIFo's */
    printf ("%x %x\n", *t_l1tFifo, *t_tkrFifo);\
    
    return 0;
    
}


int tkr_dumpFifo (char *fileName, int fileAppend, int writeL1tFifo)
{
    /* read the data and if requested the L1T FiFo and write the  */
    /* data to a file. Either write to a new file or append to an */
    /* existing one. */
    
    FILE *fp;
    int  i;
    char fileMode[3];
    unsigned long data;
    unsigned long *status  = t_brdStat;
    unsigned long count = 0;
    unsigned long cableEn = 0;
    unsigned long header[3];
    unsigned long headerLength = 3;
    
    
    sprintf (fileMode ,"wb");
    if (fileAppend == 1 )  sprintf (fileMode, "ab");
    

    if ( (fp = fopen(fileName, fileMode)) == NULL ) {
        printf("unable to create %s\n", fileName);
        return(-1);
    }
    printf ("file mode : %s \n", fileMode);
    
    

    /* ------------------------------------------- */
    /*     Header words                            */
    /* ------------------------------------------- */
    
    if ( !fileAppend ) {
        header[0] = 0x23456789;
        header[1] = headerLength;
        
        if ( writeL1tFifo == 1 ) {  
            header[2] = 0x300;              /* l1t and tkr data fifo */
        } else {
            header[2] = 0x100;             /* tkr data fifo data */
        }
        
        cableEn = 0;
        temEnabledCables(&cableEn);

        header[2] |= cableEn & 0xff;
        printf ("file header word 3  %x %x\n", header[2], cableEn);
        
        fwrite ( header, 4, 3, fp);
    }
    printf ("Writing L1T Fifo");    
  
    /* ------------------------------------------- */
    /*     Write L1T fifo                          */
    /* ------------------------------------------- */
    
    if ( writeL1tFifo == 1 ) {
        for ( i = 0; i < 20; i++ ) {
            data = *t_l1tFifo;
            fwrite ( &data, 4, 1, fp);
        }
    }
    
    /* ------------------------------------------- */

  
    count = 0;
    
    while ( ( *status & TKR_FIFO_EMPTY) != 0 ) {
        
        data = *t_tkrFifo;
        fwrite ( &data, 4, 1, fp);
        
        // if ( data == 0xbffebfff ) break;
        
        count++;
         if ( count > 40000 ) break;
        
    }
    
    printf (" FIFO count = %d \n", count);
    
    fclose(fp);
    
    return 0;
    
}












