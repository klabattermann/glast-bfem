#!/usr/bin/env python2.7
"""
UCSC SCIPP / NASA
bfem script initializes module and configures cables and front end electronics
"""
from time import sleep

def init(tem, fee):
	tem.temRstPulse()
	sleep(0.5)
	tem.temR()
	sleep(0.1)
	tem.temInit()
	tem.temDisableCable(-1)
	tem.temSetCheckSum(0)

	#Last Controller to read
	lastGtrc = [7,7, 7,7, 6,6, 5,5]
	tem.temRstLastGtrc()
	for cable in range(len(lastGtrc)):
	    print "cable - ", cable, " last gtrc= ", lastGtrc[cable]
	    tem.temLastGtrc(lastGtrc[cable], cable)

	# gtrc setup
	for cable in range(8) :
	    tem.tkrCmd_rstGtrc(31, cable)
	    tem.tkrCmd_gtrcReg(31, cable, 25, 0)
	sleep(0.5)

	#
	# gtffe setup
	#
	tem.tkrCmd_rstGtfe(31, 31, 0)
	fee.maskAll(fee.allMsk)
	# fee.unMask(fee.chanMsk | fee.trigMsk | fee.calibMsk, 12)
	fee.threshold(30)
	fee.qinjAmpl(60)
	fee.readDir(0)
	fee.set(31, 31, 0)
	fee.show()
	sleep(0.5)
	tem.tkrCmd_rstGtfeFifo(31, 31, 0)

def conf(tem, fee, threshold):
	tem.temDisableCable(-1)

	#  CABLE 0/1
	tem.temEnableCable(0)
	tem.tkrCmd_rstGtrc(31, 0)
	tem.tkrCmd_gtrcReg(31, 0, 25, 0)

	#  CABLE 2/3
	tem.temEnableCable(3)
	tem.tkrCmd_rstGtrc(31,3)
	tem.tkrCmd_gtrcReg(31,3,25,0)

	#  CABLE 4/5
	tem.temEnableCable(5)
	tem.tkrCmd_rstGtrc(31,5)
	tem.tkrCmd_gtrcReg(31,5,25,0)
	tem.tkrCmd_gtrcReg(3,5,0,0)

	#  CABLE 6/7
	tem.temEnableCable(6)
	tem.tkrCmd_rstGtrc(31,6)
	tem.tkrCmd_gtrcReg(31,6, 25,0)

	sleep(0.1)

	#
	# configure GTFE chips
	#
	cableToUse = [0,3,5,6]
	for cable in cableToUse:
	    tem.tkrCmd_rstGtfe(31,31,cable)
	    if cable in [0,3,5,6] :
	        fee.readDir(0)
	    else:
	        fee.readDir(1)
	    fee.maskAll(fee.allMsk)
	    fee.unMaskAll(fee.chanMsk | fee.trigMsk)
	    fee.threshold(threshold)
	    fee.qinjAmpl(0)
	    fee.set(31,31,cable)
	    sleep(0.1)
	    tem.tkrCmd_rstGtfeFifo(31,31,cable)
