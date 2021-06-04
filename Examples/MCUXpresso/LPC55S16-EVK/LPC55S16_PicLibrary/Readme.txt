readme.txt
----------
Example for a shared library with PIC (Position-independent-code).
To create a shared library, replace the
-c
in the compiler 'Miscellaneous' settings to
-shared 

Change the artifact extension from .a (static archive/library) to .so for a shared library or shared object)

/////////////////////////////////////////////////
// Issue
/////////////////////////////////////////////////
Using
gcc version 9.3.1 20200408 (release) (GNU Arm Embedded Toolchain 9-2020-q2-update)

Note that with the above compiler trying to generate code for M33
-mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard

gives:
c:/nxp/mcuxpressoide_11.3.0_5222/ide/plugins/com.nxp.mcuxpresso.tools.win32_11.3.0.202008311133/tools/bin/../lib/gcc/arm-none-eabi/9.3.1/../../../../arm-none-eabi/bin/ld.exe: src/lib.o: 
warning: thumb-1 mode PLT generation not currently supported


That's why the following is used:
-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard 
