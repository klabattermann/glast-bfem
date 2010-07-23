#!/usr/local/bin/python

import EventData
#import getopt
import sys
from optparse import OptionParser


# ================================================
#
# ================================================

def main(argv=None):

    parser = OptionParser()

    parser.add_option("--tup", help="output dir")
    parser.add_option("--evts", type="int", default=-1, help="output dir",
                      help="show only EVTS events")
    parser.add_option("--skip", type="int", default=0, help="output dir",
                      help="skip the first SKIP events")
    parser.add_option("--headeronly", action="store_true", default=False,
                      help="print only the header no hits or GTRC info")
    parser.add_option("--hits", action="store_true", default=False,
                      help="print the hits")

    if argv:
        (options, args) = parser.parse_args(argv)
    else:
        (options, args) = parser.parse_args()

    
    event = EventData.EventData()

    event.readFromFile(args[0])

    
    #if options.tup :
    #    event.openTup(options.tup)
        

    stat = 1
    max_evts = options.evts + options.skip
    skip = options.skip

    for n,dummy in enumerate(event):

        if n < skip:
            continue

        if max_evts > -1 and  n >= max_evts:
            break

        event.status(options.headeronly)


        #if options.tup:
        #    event.writeTup()

        if options.hits :
            event.printHitList ()
            command = raw_input ("q to quit > ")
            if command == 'q' :
                break
            
    # -------------------------------------

    #if options.tup:
    #    event.closeTup()




if __name__ == '__main__' :

    rc = main()
    sys.exit(rc)




