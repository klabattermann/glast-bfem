#!/usr/bin/env python2.7
"""
This is the main function for our tests, it pulls together the
other python scripts used to interact with the BFEM
"""
import sys
import init
import time
import qt
import tkrTem
import GtfeReg 

tem = tkrTem
fee = GtfeReg.GtfeReg(tem)

def q_loop(start, stop, filename):
    fee = GtfeReg.GtfeReg(tem)
    for cable in range(start, stop, 1):
        cablename = filename + '%d' % cable
        qt.q_inj_test(cable, tem, fee, cablename)

def close():
    close = tem.tkrVMEClose()
    print 'VME Close status ',close

def reset():
    tem.temReset()
    tem.temR()
    # tem.temRstDataFifo()
    tem.temRegister()

def start():	
    init.resman()
    init.load(tem)

def bfem():
    tem.temRstPusle()

    sleep(0.5)

    tem.temR()
    sleep(0.1)
    tem.temInit()

    tem.temDisableCable(-1)
    tem.temSetChecksum(0)

    #Last Contoller to read

    lastGtrc = [7,7, 7,7, 6,6, 5,5]
    tem.temRstLastGtrc()
    for cable in range(len(lastGtRc)):
        print "cable - ", cable, " last gtrc= ", lastGtrc[cable]
        tem.temLastGtrc(lastGtrc[cable], cable)
    
    # gtrc setup

    for cable in range(8) :
        tem.tkrCmd_rstGtrc(31,cable)
        tem.tkrCmd_gtrcReg(31,cable, 25,0)
    sleep(0.5)

    # gtffe setup

    tem.tkrCmd_rstGtfe(31,31,0)

    fee,maskAll(fee.allMsk)
    # fee.unMask(fee.chanMsk | fee.trigMsk | fee.calibMsk, 12)

    fee.threshold(30)
    fee.qinjAmpl(60)
    fee.readDir(0)
    fee.set(31,31,0)
    fee.show()
    sleep(0.5)

    tem.tkrCmd_rstGtfeFifo(31,3



if __name__ == '__main__':

