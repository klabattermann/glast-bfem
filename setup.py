#!/usr/bin/env python

"""
UCSC SCIPP / NASA
Setup script for GLAST tkrTem.py extension module.
author: Cory Dominguez
author_email: cdomingu@ucsc.edu
date: June 22 2010
"""

from distutils.core import setup, Extension


tkrTem_module = Extension('_tkrTem',
  sources=['pyTkrTem_wrap.c', 'vmeAdrs.c', 'load.c', 'tkrCmd.c', 'temBoard.c', 'dataFifo.c'],
  libraries=['nivxint'],
  extra_compile_args=['/Od'],
  )

setup(name='tkrTem',
  version='0.1',
  description='Python extension module for tkrTem',
  author='Wilko Kroeger, Cory Dominguez',
  author_email='cdomingu@ucsc.edu',
  ext_modules=[tkrTem_module],
  py_modules=['tkrTem'],
  )