# Introduction #

The events.py script uses the EventData Class to display information about the exported data fifo file.

## How To ##

The python script events.py read the binary data file created by tkr\_dumpFifo and prints out some info.
```
events.py --help
```
shows the options.

### Examples ###
```
events.py --evts 3 --headeronly testfile
```
print the first three events. Shows header (event#, hits, layers)
```
events.py --evts 3 testfile
```
as before but show also the GTRC info
```
events.py --evts 3 --hits testfile
```
show also the hits per layer.