#!/usr/bin/env python2.6
"""
This is the main function for our tests it pulls together the
other python scripts used to interact with the BFEM module 
"""
import sys
import init
import qt
import tkrTem
import GtfeReg


def qLoop(start, stop, step, filename):
    for cable in range(start, stop, step):
    	cablename = filename + '%d' % cable
        qt.qinTest(cable, tem, fee, cablename)


def closeVME():
	close = tem.tkrVMEClose()
	print 'VME Close status ',close


def reset():
	tem.temR()
	tem.temReset()
	tem.temRstDataFifo()
	tem.temRegister()


def main():
	init.resman()
	
	tem = tkrTem
	init.load(tem)
	
	fee = GtfeReg.GtfeReg(tem)
	
	
if __name__ == '__main__':
	main()