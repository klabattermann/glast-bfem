"""
This is the main function for our tests it pulls together the
other python scripts used to interact with the BFEM module 
"""

import init
import qt

def main():
	init.Resman()
	init.load()
	
	qt.qLoop()

	close = tem.tkrVMEClose()
	print 'VME Close status ',close
	
if _name_ == "_main_":
	main()