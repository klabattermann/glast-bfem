# Introduction #

This is the tool used to extend the already written C code that the VME-MXI2 and TEM cards use to control the BFEM module. In our case the the three pertinent files are:

  * pyTkrTem.i _interface file necessary for SWIG to write pyTkrTem\_wrap.c_
  * pyTkrTem.h _lists the c functions that are to be extended to the tkrTem.py module_
  * setup.py _python script that uses the distultils module's functions setup and Extension to build the module and library, tkrTem.py and tkrTem.pyc respectively_

The process of extending the C code to python is as follows:

Make sure all pertinent C, header and lib files are in the current directory.

Run:
```
C:\path\to\swig.exe -python pyTkrTem.i
```

This creates the pyTkrTem\_wrap.c file which then can be used in the setup.py script:

```
python setup.py build_ext --inplace
```

  * build\_ext - telling distutils to build extensions
  * --inplace - this tells distutils to put the extension lib in the current directory. Otherwise it will put it in a build hierarchy and you will have to move it to use it.

For more information see the [SWIG](http://swig.org/doc.html) documentation