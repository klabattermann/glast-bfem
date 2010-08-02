#
#  inject charge into all GTFE's of one layer
#  
#

from time import sleep

def qinTest (cable, tem, fee) :

    tem.temDisableCable(-1)
    tem.temEnableCable(cable)
    

    tem.tkrCmd_rstGtrc(31,cable)
    tem.tkrCmd_gtrcReg(31,cable,25,0)
    
    sleep(0.5)


    tem.tkrCmd_rstGtfe(31,31,cable)


    if cable in [0,3,5,6] :
        fee.readDir(0)
    else:
        fee.readDir(1)

    fee.maskAll(fee.allMsk)
    fee.unMask(fee.chanMsk | fee.trigMsk | fee.calibMsk, 12)
    fee.threshold(30)
    fee.qinjAmpl(60)
    fee.set(31,31,cable)
    fee.show()

    tem.tkrCmd_rstGtfeFifo(31,31,cable)

    sleep(0.5)
    tem.temStatus()
    
    tem.tkrCmd_strobe(31,31,cable)
    tem.temStatus()
    
    tem.temTreq()
    tem.tkr_dumpFifo ("tkr", 0, 0)