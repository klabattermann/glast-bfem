/* vmeAdrs header file */

//prototyped functions

void tkrVMEInit (unsigned long);
int tkrVMEClose();
unsigned long tkr_rread(unsigned long *);
int tkr_rwrite(unsigned long *, unsigned long);
int tkrLoadDataFifo (char *);
int tkrLoadL1tFifo (char *);
int tkrLoadFinalize();

void temEnabledCables (unsigned long *cblenReg);


/* CONSTANTS */

extern const int TKR_DATA_SHIFT;
extern const int L1T_DATA_SHIFT;

extern const unsigned long TKR_DATA;
extern const unsigned long TKR_DATA_NOT;
extern const unsigned long TKR_N_CONF;
extern const unsigned long TKR_N_CONF_NOT;
extern const unsigned long TKR_CLOCK;
extern const unsigned long TKR_CLOCK_NOT;

extern const unsigned long TKR_CONF_DONE;
extern const unsigned long TKR_STATUS;
extern const unsigned long TKR_RESET;
extern const unsigned long TKR_FIFO_EMPTY;
extern const unsigned long TKR_FIFO_HALF_FULL;
extern const unsigned long TKR_FIFO_FULL;
extern const unsigned long TKR_FIFO_HAS_DATA;

extern const unsigned long L1T_DATA;
extern const unsigned long L1T_DATA_NOT;
extern const unsigned long L1T_N_CONF;
extern const unsigned long L1T_N_CONF_NOT; 
extern const unsigned long L1T_CLOCK;    
extern const unsigned long L1T_CLOCK_NOT;     
extern const unsigned long L1T_CONF_DONE;     
extern const unsigned long L1T_STATUS;     
extern const unsigned long L1T_FIFO_EMPTY;    
extern const unsigned long L1T_FIFO_HALF_FULL;
extern const unsigned long L1T_FIFO_FULL;
extern const unsigned long L1T_FIFO_HAS_DATA;

#ifdef VME_ADDRESS_H

extern unsigned long *t_brdBase;

extern unsigned long *t_brdCntl;
extern unsigned long *t_brdStat;
extern unsigned long *t_l1tFifo;
extern unsigned long *t_tkrFifo;
extern unsigned long *t_lcntlReg;
extern unsigned long *t_coinxen1;
extern unsigned long *t_coinxen2;
extern unsigned long *t_coinyen1;
extern unsigned long *t_coinyen2;
extern unsigned long *t_coinplen1;
extern unsigned long *t_coinplen2;
extern unsigned long *t_mskxl1;
extern unsigned long *t_mskxl2;
extern unsigned long *t_mskxr1;
extern unsigned long *t_mskxr2;
extern unsigned long *t_mskyl1;
extern unsigned long *t_mskyl2;
extern unsigned long *t_mskyr1;
extern unsigned long *t_mskyr2;
extern unsigned long *t_mskMisc;
extern unsigned long *t_tsttkrx1;
extern unsigned long *t_tsttkrx2;
extern unsigned long *t_tsttkry1;
extern unsigned long *t_tsttkry2;
extern unsigned long *t_tstMisc;
extern unsigned long *t_rngcalxy;
extern unsigned long *t_rngacdlh;
extern unsigned long *t_rngdelay;
extern unsigned long *t_gps_timecap1;
extern unsigned long *t_gps_timecap2;
extern unsigned long *t_tcntlReg;

extern unsigned long *t_lastCntrl;
extern unsigned long *t_lastCntlrs10;
extern unsigned long *t_lastCntlrs32;
extern unsigned long *t_lastCntlrs54;
extern unsigned long *t_lastCntlrs76;
extern unsigned long *t_cblen;

extern unsigned long *t_tkrCmd;
extern unsigned long *t_tkrcmd0;
extern unsigned long *t_tkrcmd1;
extern unsigned long *t_tkrcmd2;
extern unsigned long *t_tkrcmd3;
extern unsigned long *t_tkrcmd4;
extern unsigned long *t_tkrcmd5;
extern unsigned long *t_tkrcmd6;
extern unsigned long *t_tkrcmd7;
extern unsigned long *t_tkrcmd8;
extern unsigned long *t_tkrcmd9;
extern unsigned long *t_tkrcmd10;
extern unsigned long *t_tkrcmd11;
extern unsigned long *t_tkrcmd12;
extern unsigned long *t_tkrcmd13;
extern unsigned long *t_tkrcmd14;
extern unsigned long *t_tkrcmd15;
extern unsigned long *t_tkrcmd16;
extern unsigned long *t_tkrcmd17;
extern unsigned long *t_tkrcmd18;
extern unsigned long *t_tkrcmd19;
extern unsigned long *t_tkrcmd20;
extern unsigned long *t_tkrcmd21;
extern unsigned long *t_tkrcmd22;
extern unsigned long *t_tkrcmd23;
extern unsigned long *t_tkrcmd24;
extern unsigned long *t_tkrcmd25;
extern unsigned long *t_tkrcmd26;
extern unsigned long *t_tkrcmd27;


#else
#define VME_ADDRESS_H
unsigned long *t_brdBase;

unsigned long *t_brdCntl;
unsigned long *t_brdStat;
unsigned long *t_l1tFifo;
unsigned long *t_tkrFifo;
unsigned long *t_lcntlReg;
unsigned long *t_coinxen1;
unsigned long *t_coinxen2;
unsigned long *t_coinyen1;
unsigned long *t_coinyen2;
unsigned long *t_coinplen1;
unsigned long *t_coinplen2;
unsigned long *t_mskxl1;
unsigned long *t_mskxl2;
unsigned long *t_mskxr1;
unsigned long *t_mskxr2;
unsigned long *t_mskyl1;
unsigned long *t_mskyl2;
unsigned long *t_mskyr1;
unsigned long *t_mskyr2;
unsigned long *t_mskMisc;
unsigned long *t_tsttkrx1;
unsigned long *t_tsttkrx2;
unsigned long *t_tsttkry1;
unsigned long *t_tsttkry2;
unsigned long *t_tstMisc;
unsigned long *t_rngcalxy;
unsigned long *t_rngacdlh;
unsigned long *t_rngdelay;
unsigned long *t_gps_timecap1;
unsigned long *t_gps_timecap2;
unsigned long *t_tcntlReg;

unsigned long *t_lastCntrl;
unsigned long *t_lastCntlrs10;
unsigned long *t_lastCntlrs32;
unsigned long *t_lastCntlrs54;
unsigned long *t_lastCntlrs76;
unsigned long *t_cblen;

unsigned long *t_tkrCmd;
unsigned long *t_tkrcmd0;
unsigned long *t_tkrcmd1;
unsigned long *t_tkrcmd2;
unsigned long *t_tkrcmd3;
unsigned long *t_tkrcmd4;
unsigned long *t_tkrcmd5;
unsigned long *t_tkrcmd6;
unsigned long *t_tkrcmd7;
unsigned long *t_tkrcmd8;
unsigned long *t_tkrcmd9;
unsigned long *t_tkrcmd10;
unsigned long *t_tkrcmd11;
unsigned long *t_tkrcmd12;
unsigned long *t_tkrcmd13;
unsigned long *t_tkrcmd14;
unsigned long *t_tkrcmd15;
unsigned long *t_tkrcmd16;
unsigned long *t_tkrcmd17;
unsigned long *t_tkrcmd18;
unsigned long *t_tkrcmd19;
unsigned long *t_tkrcmd20;
unsigned long *t_tkrcmd21;
unsigned long *t_tkrcmd22;
unsigned long *t_tkrcmd23;
unsigned long *t_tkrcmd24; 
unsigned long *t_tkrcmd25;
unsigned long *t_tkrcmd26;
unsigned long *t_tkrcmd27;

#endif   


