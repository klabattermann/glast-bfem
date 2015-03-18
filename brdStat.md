# Introduction #

The board control register:

brdStat= 0x0030

READ

| D15 | D14 | D13 | D12 | D11 | D10 | D09 | D08 | D07 | D06 | D05 | D04 | D03 | D02 | D01 | D00 |
|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|
| H | L | L | L |  |  |  |  |  |  |  |  | L | H | L | H |
| L1T FIFO REOF | L1T FIFO FF | L1T FIFO HF | L1T FIFO EF |  |  |  |  |  |  |  |  | TKRRD NSTAT ERR | TKRRD CFG DONE | L1T NSTAT ERR | L1T CFG DONE |

| D31 | D30 | D29 | D28 | D27 | D26 | D25 | D24 | D23 | D22 | D21 | D20 | D19 | D18 | D17 | D16 |
|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|
| H | L | L | L | H | L | L | L | H | L | L | L | H | L | L | L |
| TKRRD FIFO3 REOF | TKRRD FIFO3 FF | TKRRD FIFO3 HF | TKRRD FIFO3 EF | TKRRD FIFO2 REOF | TKRRD FIFO2 FF | TKRRD FIFO2 HF | TKRRD FIFO2 EF | TKRRD FIFO1 REOF | TKRRD FIFO1 FF | TKRRD FIFO1 HF | TKRRD FIFO1 EF | TKRRD FIFO0 REOF | TKRRD FIFO0 FF | TKRRD FIFO0 HF | TKRRD FIFO0 EF |