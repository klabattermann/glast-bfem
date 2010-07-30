
import struct
import string
import array
import struct
import sys



"""
Read the BFEM event data from binary file

hist_list = [(layerInd, channel), ]

"""




class EventData :


    def __init__ (self) :
        self.reset ()

    # ==============================================================

    def reset (self) :
	
        self.eventNr = -1
        self.hitList = []
        self.stat = {}


    # ==============================================================

    def readFromFile (self, fileName) :

        try:
            self.fp = open (fileName, "rb")
        except IOError:
            print '*** error opening file ***'
            sys.exit (4)

	    
    # ===============================================================

    def decode_fifo_header(self, fp):

        data_s = fp.read(4)
        data = struct.unpack('L', data_s)
        
        if data[0] == 0x23456789:
            print "found FIFO header"
        
            data_s = fp.read(4)
            data_length = struct.unpack('L', data_s)[0]
            print "ffh length", data_length

            data_s = fp.read(4)
            data = struct.unpack('L', data_s)
            print "ffh data", data[0]
            
            if data_length != 3:
                print "seek:", 8
                fp.seek(8)
        else:
            print "no header found, rewind"
            fp.seek(0)

        return 


    def __iter__ (self) :


        dataStruct = array.array('L')
        
        # try to read header
        self.decode_fifo_header(self.fp)
        

        while 1:

            data_s = self.fp.read (4)
            if not data_s :
                self.reset()
                self.fp.close()
                return

            data = struct.unpack('L', data_s)

            data0_16 = (data[0] >> 16) & 0xffff
            data1_16 = data[0] & 0xffff
            #print '  d %x  %x' % (data0_16, data1_16)
                        
	
            if data0_16 == 0xbffe and data1_16 == 0xbfff:  # end-of-event
                self.decode(dataStruct)
                yield
                dataStruct = array.array('L')
            else:
                dataStruct.append(data0_16)
                dataStruct.append(data1_16)

		
    # ==============================================================


    def decode (self, data):
        """


        """
        
        self.reset()

        # for every GTRC header increase the layerInd by 1
        layerInd = -1
        
        self.eventNr = (data[1] & 0xffff) | ( (data[0] << 16) & 0xffff0000)

        for data16 in data[2:] :

            # end of data flag            
            tag = data16 & 0xc000    
            cableId = (data16 >> 11) & 0x7

            #dummy = data16 & 0x7ff
            #print "%x %d %x" % (tag, cableId, dummy)

            if tag == 0x8000 :          # hit 
                if data16 == 0x87ff :   # fill Byte
                    continue

                hitAddr = data16 & 0x07ff
                hitAddr = hitAddr - 64
	
                self.hitList.append((layerInd, hitAddr))

            elif tag == 0x0000 :         # controller
                ctrlAddr = data16 >> 6
                ctrlAddr = ctrlAddr & 0x1f

                nrHits = data16 & 0x3f
		
                layerInd = layerInd + 1
                #print "  ", ctrlAddr, cableId, layerInd

                if not self.stat.has_key((cableId, layerInd)) :
                    self.stat[(cableId, layerInd)]  = [ctrlAddr,nrHits,-1,-1]
		    
            elif tag == 0x4000  :        #  error/tot flag
                errorFlag = (data16 >> 10) & 0x1
                tot = data16 & 0x03ff

                if self.stat.has_key((cableId, layerInd)) :
                    self.stat[(cableId, layerInd)][2]  = tot
                    self.stat[(cableId, layerInd)][3]  = errorFlag
            else:
                print " error no key found "


    # =====================================================================


    def status (self, header_only=False) :
        
        print " ==== status  event nr:", self.eventNr, " nr of hist:", len(self.hitList), \
              " layers:", len(self.stat)

        if header_only:
            return
            
        keyList = self.stat.keys()
        keyList.sort()

        print " (gtrc-adrs, nrHits, layerInd, cableId,    ToT, erroFlag)"
        for key in keyList :
            print "gtrc  ", self.stat[key][0], self.stat[key][1], key[1], key[0], "     ", \
                  self.stat[key][2], self.stat[key][3]


    # ============================================================================================


    def openTup (self, fileName) :
	
        try:
            self.fpTup = open (fileName, "w")
        except IOError:
            print '*** error opening tuple file ***', fileName
            sys.exit (4)	


    def writeTup (self) :

        for hit in self.hitList :
            self.fpTup.write("%d %d %d\n" % (self.eventNr, hit[0], hit[1]))
	
    def closeTup (self) :
        self.fpTup.close()


    # =========================================
    # 
    # =========================================


    def printHitList (self) :

        layerNr = -1
        hitsPrinted = 0

        for hit in self.hitList :

            if hit[0] != layerNr :
                layerNr = hit[0]
                hitsPrinted = 1
                sys.stdout.write("\n Layer %d  \n        %4d " % (hit[0], hit[1]))
            else:	    
                if hitsPrinted == 14 :
                    sys.stdout.write("\n        ")
                    hitsPrinted = 0

            sys.stdout.write("%4d " % hit[1])

            hitsPrinted = hitsPrinted + 1

            sys.stdout.write("\n")
