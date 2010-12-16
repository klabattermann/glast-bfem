#!/usr/bin/env python2.7
"""
This is the main function for our tests, it pulls together the
other python scripts used to interact with the BFEM
"""
import tkrTem
import GtfeReg 
import init
import bfem
import qt
import tkrTem
import GtfeReg 

tem = tkrTem
fee = GtfeReg.GtfeReg(tem)

def start():    
    init.resman()
    init.load(tem)

def reset():
    tem.temReset()
    tem.temR()
    # tem.temRstDataFifo()
    tem.temRegister()

def module(threshold):
    bfem.init(tem, fee)
    bfem.conf(tem, fee, threshold)

def charge_test(cable):
    qt.tc(tem, fee, cable)

def q_loop(start, stop, filename):
    fee = GtfeReg.GtfeReg(tem)
    for cable in range(start, stop, 1):
        cablename = filename + '%d' % cable
        qt.q_inj_test(cable, tem, fee, cablename)

def close():
    close = tem.tkrVMEClose()
    print 'VME Close status ',close
