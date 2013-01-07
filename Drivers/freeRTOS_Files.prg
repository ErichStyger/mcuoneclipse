%-
%- FreeRTOS source files
%-

%FILE %'DirRel_Code'croutine.h
%include freeRTOS\croutine.h

%FILE %'DirRel_Code'croutine.c
%include freeRTOS\croutine.c

%FILE %'DirRel_Code'FreeRTOS.h
%include freeRTOS\FreeRTOS.h

%FILE %'DirRel_Code'FreeRTOSConfig.h
%include freeRTOS\FreeRTOSConfig.h

%FILE %'DirRel_Code'heap.c
%if MemoryScheme = "Scheme1"
  %include freeRTOS\heap_1.c
%elif MemoryScheme = "Scheme2"
  %include freeRTOS\heap_2.c
%elif MemoryScheme = "Scheme3"
  %include freeRTOS\heap_3.c
%elif MemoryScheme = "Scheme4"
  %include freeRTOS\heap_4.c
%endif

%FILE %'DirRel_Code'license.txt
%include freeRTOS\license.txt

%FILE %'DirRel_Code'list.h
%include freeRTOS\list.h

%FILE %'DirRel_Code'list.c
%include freeRTOS\list.c

%FILE %'DirRel_Code'port.c
%include freeRTOS\port.c

%FILE %'DirRel_Code'portTicks.h
%include freeRTOS\portTicks.h

%FILE %'DirRel_Code'portable.h
%include freeRTOS\portable.h

%FILE %'DirRel_Code'portasm.s
%include freeRTOS\portasm.s

%FILE %'DirRel_Code'portmacro.h
%include freeRTOS\portmacro.h

%FILE %'DirRel_Code'projdefs.h
%include freeRTOS\projdefs.h

%FILE %'DirRel_Code'queue.c
%include freeRTOS\queue.c

%FILE %'DirRel_Code'queue.h
%include freeRTOS\queue.h

%FILE %'DirRel_Code'semphr.h
%include freeRTOS\semphr.h

%FILE %'DirRel_Code'StackMacros.h
%include freeRTOS\StackMacros.h

%FILE %'DirRel_Code'task.h
%include freeRTOS\task.h

%FILE %'DirRel_Code'tasks.c
%include freeRTOS\tasks.c

%FILE %'DirRel_Code'mpu_wrappers.h
%include freeRTOS\mpu_wrappers.h

%FILE %'DirRel_Code'timers.h
%include freeRTOS\timers.h

%FILE %'DirRel_Code'timers.c
%include freeRTOS\timers.c

%FILE %'DirRel_Code'CommandInterpreter.h
%include freeRTOS\CommandInterpreter.h

%FILE %'DirRel_Code'CommandInterpreter.c
%include freeRTOS\CommandInterpreter.c
