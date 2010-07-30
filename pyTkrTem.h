
/*                   */
/*    VME Access     */ 
/*                   */

 
extern int tkrVMEInit (unsigned long baseAdrs);
extern int tkrVMEClose();

/* --------------------- */
/*   load TEM FPGA's    */
/* --------------------- */

extern int tkrLoadDataFifo (char *fileName);
extern int tkrLoadL1tFifo(char *fileName);
extern int tkrLoadFinalize();


extern int  tkr_dumpFifo (char *fileName, int fileApp, int writeL1tFifo);
extern int  tkrDump ();


/* ------------------------------- */
/*      tracker commands           */
/* ------------------------------- */


extern void tkrCmd_rstGtrc (int gtrcAdrs, int cable);


extern void tkrCmd_clockOn (int gtrcNr, int cableNr);
extern void tkrCmd_readEvt (int gtrcNr, int cableNr);
extern void tkrCmd_gtrcReg(int gtrcNr, int cableNr, int nChipsToRead, int checkSum);

extern void tkrCmd_rstGtfe (int gtfeNr, int gtrcNr, int cableNr);
extern void tkrCmd_rstGtfeFifo (int gtfeNr, int gtrcNr, int cableNr);
extern void tkrCmd_strobe (int gtfeNr, int gtrcNr, int cableNr);
extern void tkrCmd_gtfeReg (int gtfeAdrs, int gtrcAdrs, int cableNr,
			    int calDac, int threshDac, int readDir,
			    unsigned long chanMask0, unsigned long chanMask1,
			    unsigned long trigMask0, unsigned long trigMask1,
			    unsigned long calMask0, unsigned long calMask1);
extern void tkrCmd_gtfeRegt ();

/* --------------------------------------- */
/*     tem board                           */
/* --------------------------------------- */


extern void temSetCheckSum (int value);
extern int temGetCheckSum ();
extern void temEnableCable (int cableNr);
extern void temDisableCable (int cableNr);
extern int temIsCableEnabled (int cableNr);
extern void temRstLastGtrc ();
extern void temLastGtrc (int addr, int cable);
extern void temRstPulse ();
extern void temRstDataFifo ();
extern void temInit ();

extern void temStatus ();
extern void temRegister ();
extern void temMaskReg();

extern void temReset();
extern void temR();

extern void temTreq();
extern void temTreq1();
extern void temDF();


void rstOn(int mode);

/* --------------------------------------- */
/*   l1t                                   */
/* --------------------------------------- */


//extern void l1tTreq (int view, int rl, int layer, int en_dis);
//extern void l1tEnableTreq(int view, int rl, int layer);
//extern void l1tDisableTreq(int view, int rl, int layer);
//extern void l1tEnableCoinPlane (int planeNr);
//extern void l1tDisableCoinPlane (int planeNr);
//extern void l1tBypassTreqLayer(int layer, int view);
//extern void l1tNoBypassTreqLayer(int layer, int view);


/* ------------------------------------ */
/*                                      */
/* ------------------------------------ */

//extern int testLoop(int loops, int delay);

//extern int runLoop (int nEvt, int runNr, int mode, int delay);

