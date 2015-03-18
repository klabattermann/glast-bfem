# Introduction #


## VME Access ##
[int tkrVMEInit (unsigned long baseAdrs)](tkrVMEInit.md)

[int tkrVMEClose ()](tkrVMEClose.md)

## Load TEM FPGA's ##
[int tkrLoadDataFifo (char \*fileName)](tkrLoadDataFifo.md)

[int tkrLoadL1tFifo (char \*fileName)](tkrLoadL1tFifo.md)

[int tkrLoadFinalize ()](tkrLoadFinalize.md)

## Tracker Commands ##
[void tkrCmd\_rstGtrc (int gtrcAdrs, int cable)](tkrCmd_rstGtrc.md)

[void tkrCmd\_clockOn (int gtrcNr, int cableNr)](tkrCmd_clockOn.md)

[void tkrCmd\_readEvt (int gtrcNr, int cableNr)](tkrCmd_readEvt.md)

[void tkrCmd\_gtrcReg (int gtrcNr, int cableNr, int nChipsToRead, int checkSum)](tkrCmd_gtrcReg.md)

[void tkrCmd\_rstGtfe (int gtfeNr, int gtrcNr, int cableNr)](tkrCmd_rstGtfe.md)

[void tkrCmd\_rstGtfeFifo (int gtfeNr, int gtrcNr, int cableNr)](tkrCmd_rstGtfeFifo.md)

[void tkrCmd\_strobe (int gtfeNr, int gtrcNr, int cableNr)](tkrCmd_strobe.md)

[void tkrCmd\_gtfeReg (int gtfeAdrs, int gtrcAdrs, int cableNr, int calDac, int threshDac, int readDir, unsigned long chanMask0, unsigned long chanMask1, unsigned long trigMask0, unsigned long trigMask1, unsigned long calMask0, unsigned long calMask1)](tkrCmd_gtfeReg.md)

[void tkrCmd\_gtfeRegt ()](tkrCmd_gtfeRegt.md)


## TEM Board ##
[void temSetCheckSum (int value)](temSetCheckSum.md)

[int temGetCheckSum ()](temGetCheckSum.md)

[void temEnableCable (int cableNr)](temEnableCable.md)

[void temDisableCable (int cableNr)](temDisableCable.md)

[int temIsCableEnabled (int cableNr)](temIsCableEnabled.md)

[void temRstLastGtrc ()](temRstLastGtrc.md)

[void temLastGtrc (int addr, int cable)](temLastGtrc.md)

[void temRstPulse ()](temRstPulse.md)

[void temRstDataFifo ()](temRstDataFifo.md)

[void temInit ()](temInit.md)

[void temStatus ()](temStatus.md)

[void temRegister ()](temRegister.md)

[void temMaskReg ()](temMaskReg.md)

[void temReset ()](temReset.md)

[void temR ()](temR.md)

[void temTreq ()](temTreq.md)

[void temTreq1 ()](temTreq1.md)

[void temDF ()](temDF.md)

## L1T ##

[void l1tTreq (int view, int rl, int layer, int en\_dis)](l1tTreq.md)

[void l1tEnableTreq (int view, int rl, int layer)](l1tEnableTreq.md)

[void l1tDisableTreq (int view, int rl, int layer)](l1tDisableTreq.md)

[void l1tEnableCoinPlane (int planeNr)](l1tEnableCoinPlane.md)

[void l1tDisableCoinPlane (int planeNr)](l1tDisableCoinPlane.md)

[void l1tBypassTreqLayer (int layer, int view)](l1tBypassTreqLayer.md)

[void l1tNoBypassTreqLayer (int layer, int view)](l1tNoBypassTreqLayer.md)

## Loops ##

[int testLoop (int loops, int delay)](testLoop.md)

[int runLoop (int nEvt, int runNr, int mode, int delay)](runLoop.md)