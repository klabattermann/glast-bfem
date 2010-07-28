
import array


class GtfeReg :

    calibMsk = 1
    chanMsk = 2
    trigMsk = 4
    allMsk  = 7
    
    def __init__(self, tem):
        self.reg = array.array('L', [0,0,0,0,0,0])
        self.calDac = 10
        self.thresDac = 30
        self.side = 0
        self.t = tem
        
    # =======================================================
    #    mask for all channels
    # =======================================================
    
    def maskAll (self, maskType) : 

        print maskType, self.trigMsk, maskType & self.trigMsk
        if maskType & self.chanMsk:
            self.reg[2] = self.reg[3] = 0x0
        if maskType & self.trigMsk :
            self.reg[4] = self.reg[5] = 0x0
        if maskType & self.calibMsk : 
            self.reg[0] = self.reg[1] = 0x0

    def unMaskAll (self, maskType) : 

        print maskType, self.trigMsk, maskType & self.trigMsk
        if maskType & self.chanMsk:
            self.reg[2] = self.reg[3] = 0xffffffff
        if maskType & self.trigMsk :
            self.reg[4] = self.reg[5] = 0xffffffff
        if maskType & self.calibMsk : 
            self.reg[0] = self.reg[1] = 0xffffffff
            
    # =======================================================
    #    mask single channels or range of channels
    # =======================================================


    def mask(self, maskType, chan):
       
        ind = chan / 32
        shift = 31 - (chan % 32)
        tmp = 0x1 << shift
        tmp = ~tmp

        if maskType & self.chanMsk:
            self.reg[ind+2] = self.reg[ind+2] & tmp 
        if maskType & self.trigMsk:
            self.reg[ind+4] = self.reg[ind+4] & tmp 
        if maskType & self.calibMsk:
            self.reg[ind] = self.reg[ind] & tmp 


    def maskRange (self, maskType, start, stop, step) :

        for chan in range (start, stop+1, step):
            self.mask(maskType, chan)

    # =======================================================
    #    un-mask single channels or range of channels
    # =======================================================
    
    def unMask(self, maskType, chan):
       
        ind = chan / 32
        shift = 31 - (chan % 32)
        tmp = 0x1 << shift
      
        if maskType & self.chanMsk:
            self.reg[ind+2] = self.reg[ind+2] | tmp 
        if maskType & self.trigMsk:
            self.reg[ind+4] = self.reg[ind+4] | tmp 
        if maskType & self.calibMsk:
            self.reg[ind] = self.reg[ind] | tmp 

    def unMaskRange (self, maskType, start, stop, step) :

        for chan in range (start, stop+1, step):
            self.unMask(maskType, chan)

    # =======================================================
    #    dac's and directions
    # =======================================================

    def threshold (self, value):
        self.thresDac = value

    def qinjAmpl (self, value):
        self.calDac = value

    def readDir (self, value):
        if value == 0 :
            self.side = 0
        else:
            self.side = 1

    # ==============================================
    #
    # ==============================================


    def set(self, gtfeAdrs, gtrcAdrs, cable):
        self.t.tkrCmd_gtfeReg(gtfeAdrs, gtrcAdrs, cable, self.calDac, self.thresDac,
                              self.side, self.reg[0], self.reg[1],
                              self.reg[2], self.reg[3], self.reg[4], self.reg[5])

    def show(self):
        print '%x %x %x %x %x %x' %(self.reg[0],self.reg[1],
                                    self.reg[2],self.reg[3],self.reg[4],self.reg[5])
        print "dac thres = %d,  calib %d, side %d" % (self.thresDac, self.calDac, self.side)
        


if __name__ == '__main__':

    a = GtfeReg()
    a.unMaskRange(a.trigMsk, 0,63,1)
    a.threshold(10)
    a.qinjAmpl(60)
    a.readDir(12)
    a.show()
    print a.chanMsk
    


