XSM Simulator
=============

**Introduction** : The XSM (eXperimental String Machine) Simulator is used to simulate the XSM hardware.

Prerequisites :
-------------
	• GCC (GNU project C and C++ compiler)
	• Flex / Lex (Fast Lexical Analyser Generator)
	• Bison / Yacc (GNU Project Parser Generator)

Compiling:
----------
Run `make`.

Running:
--------
 `./xsm [--timer #1] [--disk #2] [--console #3] [--disk-file #4] [--debug #5]`

1. Syntax: `--timer value`  
    Semantics: This flag sets the number of user mode instructions after which 
    timer interrupt is triggered to the value specified.  
    `--timer 0` disables the timer.  
    The range of value is from 0 to 1024.   
    Default value: 20  

2. Syntax: `--disk value`  
    Semantics: This flag sets the number of user mode instructions after which 
    the disk interrupt is triggered to the value specified.  
    The range of value is from 20 to 1024.  
    Note that count begins only after a LOAD or STORE machine instruction gets executed.  
    Default value: 20

3. Syntax: `--console value`  
    Semantics: This flag sets the number of user mode instructions after which console 
    interrupt is triggered to the value specified.  
    The range of value is from 20 to 1024.  
    Note that count begins only after a IN machine instruction gets executed.  
    Default value: 20

4. Syntax: `--disk-file path/to/disk`  
    Semantics: This flag specifies the disk file to be used.  
    Default value: `../xfs-interface/disk.xfs`

5. Syntax: `--debug`  
    Semantics: This flag sets the machine into DEBUG mode when it encounters a BRKP machine instruction.  
    Any BRKP instruction in the program will be ignored by the machine if this flag is not set.  
    Further details are given in the section below.  
    The machine instruction INI gets enabled only in DEBUG mode. 
