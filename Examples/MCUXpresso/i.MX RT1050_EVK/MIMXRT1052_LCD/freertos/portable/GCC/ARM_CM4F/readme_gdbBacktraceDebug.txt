readme.txt
----------
Tasks backtrace switcher/viewer snippet is from the following FreeRTOS Interactive site:
http://interactive.freertos.org/entries/23468301-Tasks-backtrace-switcher-viewer-snippet-for-debugger-gcc-gdb-ARM-Cortex-M3-MPU-port-Eclipse-support-

It generates the following files:
- readme_gdbBacktraceDebug.txt (this file)
- .gdbinit-FreeRTOS-helpers (GDB script file)

Usage:
- execute GDB script (either manually or in the launch configuration):
  source .//Generated_Code//.gdbinit-FreeRTOS-helpers
- execute
  freertos_show_threads
  to show threads with handlers
- use 
  freertos_switch_to_task <handle>
  to show task stack
- use
  freertos_restore_running_context
  to restore the context before running

Credits to:
- Artem Pisarneko for his initial contribution
- Prasana for the PendSVHandler updates
- Geoffrey Wossum for the Cortex-M4 contribution

Link to article:
http://mcuoneclipse.com/2015/10/03/freertos-arm-thread-debugging-with-eclipse-and-gdb/


