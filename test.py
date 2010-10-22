#!/usr/bin/env python2.7
"""
This is the main function for our tests it pulls together the
other python scripts used to interact with the BFEM module 
"""
import sys
import init
import qt
import tkrTem as tem
import GtfeReg 


def q_loop(start, stop, filename):
    fee = GtfeReg.GtfeReg(tem)
    for cable in range(start, stop, 1):
        cablename = filename + '%d' % cable
        qt.q_inj_test(cable, tem, fee, cablename)


def close_vme():
    close = tem.tkrVMEClose()
    print 'VME Close status ',close


def reset():
    tem.temR()
    tem.temReset()
    tem.temRstDataFifo()
    tem.temRegister()


def start():	
    init.resman()
    init.load(tem)
