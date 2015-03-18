# Introduction #

The board control register:

brdCntl= 0x0020

READ/WRITE

| D15 | D14 | D13 | D12 | D11 | D10 | D09 | D08 | D07 | D06 | D05 | D04 | D03 | D02 | D01 | D00 |
|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|
| L |  |  |  |  |  |  |  |  |  |  |  |  | H | L | L |
| HSK EN |  | L1T DCLK | L1T NCFG | L1T SDAT | TKRRD DCLK | TKRRD NCFG | TKRRD SDAT |  |  |  |  |  | RST TKR | RST FIFO | RST FPGAs |