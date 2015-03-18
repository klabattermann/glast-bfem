# void temReset() #

## Summary ##

This function writes to the register brdCntl four times with the result being that the last four bits in the register are written to 0111 (0x6) and then back to 0011 (0x3).

## Code ##
From temBoard.c:
```
void temReset()
{
    unsigned long origCmd = 0;
    
    origCmd = tkr_rread(t_brdCntl);    
    printf ("tem reset: brd-cntl = %x\n", origCmd);
    
    tkr_rwrite_wait(t_brdCntl, origCmd | 0x4, 10);
    tkr_rwrite_wait(t_brdCntl, origCmd | 0x1, 10);
    tkr_rwrite_wait(t_brdCntl, origCmd | 0x6, 10);
    tkr_rwrite_wait(t_brdCntl, origCmd | 0x2, 10);
    
    tkr_rwrite_wait(t_brdCntl, 0x1b03, 10);    
}

```