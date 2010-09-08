#!/usr/bin/env python2.6
"""
"""
from time import sleep


def qinTest(cable, tem, fee, cablename):
    """Inject charge into all GTFE's of one cable"""
    tem.temDisableCable(-1)
    sleep(1)
    tem.temEnableCable(cable)

    if cable in [0,3,5,6]:
        fee.readDir(0)
    else:
        fee.readDir(1)
    # this isn't really needed but set it anyhow.
    # fee.maskAll(fee.allMsk)
    # fee.threshold(30)
    # fee.qinjAmpl(80)
    # fee.set(31,31,cable)
    
    tem.tkrCmd_rstGtrc(31, cable)
    tem.tkrCmd_rstGtfe(31, 31, cable)
    
    
    #Turn off CRC
    tem.tkrCmd_gtrcReg(31, cable, 31, 0)
    tem.temSetCheckSum(0)
    tem.temGetCheckSum()
    
    # reset now the fifo and check if it is empty
    tem.temRstDataFifo()
    
    sleep(1)
    tem.temStatus()
    
    #strobe several times and check to see if there is data.
    tem.tkrCmd_strobe(31, 31, cable)
    
    print'strobing...\n'

    sleep(1)
    
    tem.temStatus()
    tem.tkr_dumpFifo(cablename, 0, 0)


def noqTest(cable, tem, fee, cablename):
    """Check all GTFE's using a checksum"""
    tem.temDisableCable(-1)
    tem.temEnableCable(cable)

    # this isn't really needed but set it anyhow.
    fee.readDir(0)
    fee.maskAll(fee.allMsk)
    fee.threshold(30)
    fee.qinjAmpl(0)
    fee.set(31,31,cable)
    
    tem.tkrCmd_rstGtrc(31, cable)
    # all controllers on cable 0 are configured to read 0 GTFE's and don't 
    # send checksum info. tem.tkrCmd_gtrcReg(31,0,0,0)
    # this will tell the tem board that the controller is not sending the 
    # checksum word.
    tem.tkrCmd_gtrcReg(31, cable, 0, 0)
    tem.temSetCheckSum(0)
    tem.temGetCheckSum()

        # reset now the fifo and check if it is empty and then issue the trigger
    tem.temRstDataFifo()
    
    tem.temStatus()
    
    tem.temTreq()
    
    print'Trigger pulled\n'
    
    tem.temStatus()
    
    # and then dump the fifo
    tem.tkr_dumpFifo(cablename, 0, 0)

    
#
#  Depricated charge injection since I don't understand what all the functions do 
#  
#
    

# def qinTest (cable, tem, fee) :

#     tem.temDisableCable(-1)
#     tem.temEnableCable(cable)
    

#     tem.tkrCmd_rstGtrc(31,cable)
#     tem.tkrCmd_gtrcReg(31,cable,25,0)
    
#     sleep(1)


#     tem.tkrCmd_rstGtfe(31,31,cable)


#     if cable in [0,3,5,6] :
#         fee.readDir(0)
#     else:
#         fee.readDir(1)

#     fee.maskAll(fee.allMsk)
#     fee.unMask(fee.chanMsk | fee.trigMsk | fee.calibMsk, 1)
#     #fee.unMaskRange(fee.chanMsk | fee.trigMsk | fee.calibMsk, 1, 12, 1)

#     fee.threshold(30)
#     fee.qinjAmpl(60)
#     fee.set(31,31,cable)
#     fee.show()

#     tem.tkrCmd_rstGtfeFifo(31,31,cable)

#     sleep(1)
#     tem.temStatus()
    
#     #tem.tkrCmd_strobe(31,31,cable)
    
#     sleep(1)
    
#     tem.temTreq()
    
#     tem.temStatus()
#     #tem.tkr_dumpFifo ("tkr", 0, 0)
    
