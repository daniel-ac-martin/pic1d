__Note:__ The vast majority of this code was written in a rush, back in 2006.
As such there is a lot wrong with it. Notably, the gnuplot output mode is
buggy and the code does *NOT* represent good, modern C++ practice.

It was written as one of the two main projects for my M.Phys, the [report]
for which is available online.

It has been made public at the request of one of the staff of Benue State
University, Nigeria.

Those wishing to conduct similar simulations might be better served by
[XES1] for which the code is far more mature.

--------------------------------------------------------------------------------

PIC1D, the Plasma Simulator
===========================

Copyright (C) 2007 Daniel A.C. Martin.

This file is free documentation; Daniel A.C. Martin gives unlimited
permission to copy, distribute and modify it.

Introduction
============

PIC1D is a plasma simulator written by Daniel A.C. Martin. It is `free
software' meaning that you have the freedom to study, modify, and share
it as well as share your modifications. You deserve free software, don't
accept anything less.

   This software may contain bugs, and should only be used for research
purposes if the user is willing to study the code and where necessary
make the modifications he/she requires.

Installation
============

Please see the INSTALL file.

Usage
=====

Please see the full documentation, either by running 'info pic1d' or by
viewing the files in the doc/ directory of this package. Additionally, 
the output of 'plasma --help' should give you some rough guidance.

Example - The 2-stream instability
----------------------------------

To simulate the 2-stream instability call pic1d with the following arguments:

	pic1d -l 6.283 -p 512 -t 0.1 -T 500 -W 1 \
	      --species -P 2048 -m 1 -q -1 -w 1 --v0 1 --x1 0.0001 \
	      --species -P 2048 -m 1 -q -1 -w 1 --v0 -1 --x1 -0.0001

 [report]: http://www.daniel-martin.co.uk/files/pic.pdf
 [XES1]:   http://w3.pppl.gov/~hammett/courses/trieste01/es1_code.html
