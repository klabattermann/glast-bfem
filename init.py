#!usr/bin/env python

"""
UCSC SCIPP / NASA
Intialization script for GLAST. Starts VME and loads FIFO.
author: Wilko Kroeger, Cory Dominguez
author_email: cdomingu@ucsc.edu
data: June 22 2010
"""

import sys, subprocess, tkrTem

#must run RESMAN to remove sys.fail from VME board before initializing VME and loading FIFO
try:
  subprocess.check_call(["resman/Resman.exe", "-o"])
except OSError, e:
  print >>sys.stderr, "Execution failed:", e
  sys.exit()
  
tem = tkrTem
tem.tkrVMEInit(0x8000000)

status = tem.tkrLoadDataFifo("conf/tkrrdout2_1.ttf")
print 'Status FPGA DATA: ', status

status = tem.tkrLoadL1tFifo("conf/l1t2_1.ttf")
print 'Status L1t FIFO: ', status

tem.tkrLoadFinalize()

#close = tem.tkrVMEClose()
#print 'VME Close status ', close

#Success