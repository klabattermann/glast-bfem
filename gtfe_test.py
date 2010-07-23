cable = 0

tem.tkrCmd_rstGtrc(31,cable)
tem.tkrCmd_gtrcReg(31,cable,25,0)

tem.tkrCmd_rstGtfe(2,0,cable)

fee.readDir(0)
fee.maskAll(fee.allMsk)
fee.unMask(fee.chanMsk | fee.trigMsk | fee.calibMsk, 12)
fee.unMaskRange( fee.allMsk, 3,25,1 )
fee.threshold(30)
fee.qinjAmpl(60)
fee.set(31,31,cable)
fee.show()


tem.tkrCmd_rstGtfeFifo(31,31,cable)


