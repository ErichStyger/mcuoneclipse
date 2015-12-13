readme.txt
----------

http://stackoverflow.com/questions/5332849/parsing-lint-errors-in-eclipse

GNU warning:
../Sources/main.c:34:1: warning: type defaults to 'int' in declaration of 'j'

lint: 
C:\tmp\wsp_kds_3.0.0\FRDM-K64F_pc-lint\Sources\test.c:10:1: Warning 552: Symbol 'i' (line 10, file C:\tmp\wsp_kds_3.0.0\FRDM-K64F_pc-lint\Sources\test.c) not accessed


Steps:
- create new build configuration
- C/C++ build, set it builder settings: ${ProjDirPath}\lint\do_lint.bat "${ProjDirPath}"

Error parser:
- use  the eclipse_msg.lnt
- only have GNU gcc/g++ error parser present


Running co_gcc.bat
- need make, awk, gcc, g++, touch in path
- GNU core utilities (setup, otherwise dll is missing)


Links:
http://syncor.blogspot.ch/2010/03/using-lint-in-eclipse-with-netburner.html
http://stackoverflow.com/questions/5332849/parsing-lint-errors-in-eclipse
GNU awk project: https://www.gnu.org/software/gawk/
GNU awk user's guide: http://www.gnu.org/software/gawk/manual/gawk.html
GNU awk for windows: http://gnuwin32.sourceforge.net/packages/gawk.htm
GNU core utilities for windows: http://gnuwin32.sourceforge.net/packages/coreutils.htm
