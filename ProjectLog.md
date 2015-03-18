

# Introduction #

This page is the main page that links to all of the dated log pages, documenting progress on the GLAST Museum Project. Individual log entries will be labeled and sorted by date, using the YYYYMONTHDD example.

## 2010OCT19 ##

OK so back today for the first time in a while. The project is not in poor shape, we have successfully degugged to code so that we can run charge injeciton tests on the module. There is a bug in that cables 5-7 are not responding.

## 2010OCT20 ##

~~Need to fix the Hg registry since it doesn't represent what is on the modules base computer~~

## 2010OCT27 ##

Added the glast user guide to the repository, reading it to help understand masking.

## 2010DEC13 ##

Changed some of the information on the main page to represent the work I have been doind with me writing.

## 2010DEC14 ##

found new charge injection procedure at http://scipp.ucsc.edu/groups/glast/labtest/presto/

Added bfem() function to test.py and charge injection test tc() to qt.py. Will run tests next time I am in lab.

### Bugs ###
  1. cables 5-7 are not responding
  1. readout direction does not appear to be working.

### Possible explanations ###
  1. Bias Voltage currently set at 60v maybe too low, although I run each cable one at a time I am unsure of how the bias voltage is distributed to the tower, raising i to 100V will test this theory and should not harm the module.

  1. The readout direction is specified in two files, GtfeReg.py and the qt.py python files, There might be a conflict there.