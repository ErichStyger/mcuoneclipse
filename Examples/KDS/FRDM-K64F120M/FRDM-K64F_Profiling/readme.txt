readme.txt
----------
This is an example project for Kinetis Design Studio demonstrating the Kinetis SDK with Processor Expert.

Tools used:
- Kinetis Design Studio v3.0.0 with Processor Expert
- Kinetis SDK v1.2.0

Note that this project uses semihosting (linker option -specs=rdimon.specs  instead of -specs=nosys.specs),
and the project will *NOT* run without a debugger attached!

Coverage per File options: -fprofile-arcs -ftest-coverage
Profiling: -pg

 * http://doc.ironwoodlabs.com/arm-arm-none-eabi/html/getting-started/arm-mcount.html
 * gmon.c/h from C:\Temp2\newlib\winsup\cygwin
 
 https://answers.launchpad.net/gcc-arm-embedded/+question/249429
 
 Do not instrument gmon.c (recursive calls!). How to disable -pg for a function??
