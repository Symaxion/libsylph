<!------------------------------------------------------------------------------
                                                                                
  _=<|=;_. .                                                                  
 <vm#Xsii|====;;...             _,                        _,           ,,      
:i3##o1|iii||||+=;.   a/    _,. $#        .awa,           QE           Qk      
:i3Xn1i|ii||||+=:..   Qk    WQ( m#       _QB?9Qc          Wk           Qf      
 <iiii||i|+===-::.    Qk    -"  m#       jW`  "`          WE           Qf      
  :++++==- .   .      Qk    ..  m# _,    ]Ww.    ..    .. Wk  .. _,    Qf._,   
  . ..                Qk    jQ  mQmQQQc   ?QWgc  4Q/  <QF Wk .QmQQQm,  QmQQQc  
           .::__..    Qk    jQ  mW^  4Q,    "4QL  $Q. m@  Wk .Q@` -Qm  Q@  $Q  
 ....:::_=||iwoai|.   Qk    jQ  mE   =Q[  .   4Q. "WLjW'  WE .Qf   ]Q; Qf  jQ  
 .;=+|+||iiimWZoiI>   Qk    jQ  mm   ]Q[ Qh   jQ   ]QQF   Wk .QL   jQ  Qf  jQ  
 .:=+||||i|vXXSlii>.  Qmwaw jQ  mQgaam@  ]QgayQf    Q@    WE .QQwawQF  Qf  jQ  
 ..:===+||iiI1li|l=   Y?T?T )T  ???9V?    "9TT'    ]Q(    ?! .Qf?VT!   T(  )T  
  . ... -==+||||+=.                               _QP        .Qf              
             -=  .                                dW`        .Qf              
                                                 =V(         .V[              
                                                 
------------------------------------------------------------------------------->

![ ](http://synthi.net/libsylph-full-small.png)

Table of Contents
=================

- Dependencies
    - Supported Operating Systems
    - Supported Compilers
    - Additional Libraries
- Build instructions
    - Compiling the source code
    - Installing

- Contact info
    - Copyright and licensing
    - Reporting bugs

<!----------------------------------------------------------------------------->

1. Dependencies
===============

1.1 Supported Operating Systems
-------------------------------

  Currently, LibSylph can be run most Unix-systems, including, but not limited to,
  Linux, FreeBSD, Cygwin, Mac OS X, and a few others.  In order for the binary
  relocation function to work (i.e.  `thisapp->XXX()` ), support for
  `/proc/self/exe` is required. On Mac OS X, the `/proc` filesystem is not 
  enabled by default. However, OS X provides an alternate method for retrieving
  the full path to the running executable, therefore no extra software is needed
  to function correctly on Mac OS X.

  Minimal support for Microsoft Windows is included as well. However, no
  prepackaged compiler for this platform meets the required features (see
  section 1.2), therefore LibSylph WON'T run by default on Microsoft Windows
  currently. You can always try to set up a conforming compiler yourself. For
  that reason, we do not support nor endorse LibSylph on Microsoft Windows. You
  will see that certain functionality might be flawed, lacking, or nonexistent
  on Windows. Please do not report this as a bug until official support is
  added.  

1.2 Supported Compilers
-----------------------

  As of now, only one specific compiler is supported: the GNU C++ compiler
  (g++), version 4.5.3. LibSylph uses certain GNU C++ specific extensions.
  Furthermore, support for certain C++11 constructs is required. At the day of
  writing this document, only the compiler mentioned above supports these
  extensions. In case you found another compiler to meet these requirements,
  please contact the LibSylph developers (see section 3.2).

2. Build Instructions
=====================

2.1 Compiling the source code
-----------------------------

### 2.1.1 Dependencies ###
             
  LibSylph depends on boehm-gc, icu, and gettext. You need to have these
  programs installed first. Please consult your operating system vendor's
  manuals or look at the Installation page on our wiki.
            
### 2.1.2 Building ###
            
  To build the source code, issue the following commands:

      cmake .
      make

  Please note you might need to specify the path to a C++11 compiler
  explicitly by using `-DCMAKE_CXX_COMPILER=/path/to/c++`.

  To enable debugging symbols and other useful debug output, such
  as debug logging, assertions, and line number information,
  pass `-DCMAKE_BUILD_TYPE=Debug -DSYLPH_DEBUG=1` to cmake. Read
  the CMake documentation for more information about additional
  parameters that control the build.

2.2 Installing
--------------

  To install LibSylph, issue the following command as root (or your operating
  systems respective administrator account):

      make install
  
  By default, LibSylph will install in `/usr/local`. If this is not what you
  want, you need to pass the `-DCMAKE_INSTALL_PREFIX=/your/prefix` to cmake
  before the build.

2.3 Running the test suite
--------------------------
 
  To run the test suite, issue the following command in the build directory:

      make test

  This will build and run the entire test suite, as well as building the gtest
  (Google Test) framework, which is included with the source code.

3. Contact info
===============

3.1 Copyright and licensing
---------------------------

  Please see the files 'AUTHORS' and 'COPYING' to see the names of the original
  authors and the license of the code, respectively.

3.2 Reporting bugs
------------------

  Please report bugs to the 
  [libsylph-devel@lists.sf.net](mailto:libsylph-devel@lists.sf.net) 
  mailing list. You need
  to register in order to be able to send e-mails to this list.  See
  [http://synthi.net/-lsdevel](http://synthi.net/-lsdevel) for more info on how
  to register. When submitting bug reports, please state the version of LibSylph
  used. If you aren't using the latest version from git, first look if your bug
  is already fixed. If it isn't, include a full description of what is going
  wrong, and any possible error messages.

  Things you should mention:
  
  * Your operating system, including version. For Linux users, state
    your kernel version, architecture, and distro.
  * The version of your compiler.
  * The version of any other tools you are using important to the
    problem (including LibSylph!).
  * What you were trying to do, what actually happened, and how this
    is not what you expected. Perhaps it's a feature, and not
    a bug? ;)
  * If you can reproduce the bug, and so, under what conditions.
  * If the bug is specifically tied to a certain operating system, or
    if you tried reproducing the bug on another operating system.
  * A minimal test case showcasing the bug. In case this is not
    possible, step-by-step instructions on how to reproduce the bug.
    The test case should not contain anything more than necessary,
    and shouldn't link with any other libraries than the standard
    libraries and LibSylph. If a certain library is essential to
    demonstrate the problem, please make sure it's readily available.
  * Any error messages, including backtraces from a debugger in case
    of program-terminating bugs (e.g. overflows, exceptions, ...)
  * If you have one, a patch to fix the bug :)

<!----------------------------------------------------------------------------->
