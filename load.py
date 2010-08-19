import sys
import os.path
import array
import subprocess
from time import sleep
import GtfeReg


#sys.path.append('/home/babar/wilko//glast/presto/proj0/src')

import tkrTem

#must run RESMAN to remove sys.fail from VME board before initializing VME and loading FIFO
try:
  subprocess.check_call(["resman/Resman.exe", "-o"])
except OSError, e:
  print >>sys.stderr, "Execution failed:", e
  sys.exit()

#
# initilize the VXI library
#


tem = tkrTem

stat = tem.tkrVMEInit (0x8000000)
print 'open VXI lib: ', stat


#
#  load FPGA register
#

l1tFifo_ttf = 'conf/l1t2_1.ttf' #os.path.expandvars("$HOME") + "/glast/presto/conf/l1t2_1.ttf"
dataFifo_ttf = 'conf/tkrrdout2_1.ttf' #os.path.expandvars("$HOME") + "/glast/presto/conf/tkrrdout2_1.ttf"

stat = tem.tkrLoadDataFifo(dataFifo_ttf)
print stat,  dataFifo_ttf
stat = tem.tkrLoadL1tFifo(l1tFifo_ttf)
print stat, l1tFifo_ttf
tem.tkrLoadFinalize()


tem.temReset()
tem.temR()

#tem.temEnableCable(0) 




fee = GtfeReg.GtfeReg(tem)