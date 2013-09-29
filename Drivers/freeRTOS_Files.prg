%-
%- FreeRTOS source files
%-
%if defined(RTOSFolderName)
 %define  RTOSDirFolder /%'RTOSFolderName'/
%else
 %define  RTOSDirFolder 
%endif

%FILE %'DirRel_Code'%'RTOSDirFolder'croutine.h
%include freeRTOS\croutine.h

%FILE %'DirRel_Code'%'RTOSDirFolder'croutine.c
%include freeRTOS\croutine.c

%FILE %'DirRel_Code'%'RTOSDirFolder'FreeRTOS.h
%include freeRTOS\FreeRTOS.h

%FILE %'DirRel_Code'%'RTOSDirFolder'FreeRTOSConfig.h
%include freeRTOS\FreeRTOSConfig.h

%FILE %'DirRel_Code'%'RTOSDirFolder'heap_1.c
%include freeRTOS\heap_1.c

%FILE %'DirRel_Code'%'RTOSDirFolder'heap_2.c
%include freeRTOS\heap_2.c

%FILE %'DirRel_Code'%'RTOSDirFolder'heap_3.c
%include freeRTOS\heap_3.c

%FILE %'DirRel_Code'%'RTOSDirFolder'heap_4.c
%include freeRTOS\heap_4.c

%FILE %'DirRel_Code'%'RTOSDirFolder'license.txt
%include freeRTOS\license.txt

%FILE %'DirRel_Code'%'RTOSDirFolder'list.h
%include freeRTOS\list.h

%FILE %'DirRel_Code'%'RTOSDirFolder'list.c
%include freeRTOS\list.c

%FILE %'DirRel_Code'%'RTOSDirFolder'port.c
%include freeRTOS\port.c

%FILE %'DirRel_Code'%'RTOSDirFolder'portTicks.h
%include freeRTOS\portTicks.h

%FILE %'DirRel_Code'%'RTOSDirFolder'portable.h
%include freeRTOS\portable.h

%FILE %'DirRel_Code'%'RTOSDirFolder'portasm.s
%include freeRTOS\portasm.s

%FILE %'DirRel_Code'%'RTOSDirFolder'portmacro.h
%include freeRTOS\portmacro.h

%FILE %'DirRel_Code'%'RTOSDirFolder'projdefs.h
%include freeRTOS\projdefs.h

%FILE %'DirRel_Code'%'RTOSDirFolder'queue.c
%include freeRTOS\queue.c

%FILE %'DirRel_Code'%'RTOSDirFolder'queue.h
%include freeRTOS\queue.h

%FILE %'DirRel_Code'%'RTOSDirFolder'semphr.h
%include freeRTOS\semphr.h

%FILE %'DirRel_Code'%'RTOSDirFolder'StackMacros.h
%include freeRTOS\StackMacros.h

%FILE %'DirRel_Code'%'RTOSDirFolder'task.h
%include freeRTOS\task.h

%FILE %'DirRel_Code'%'RTOSDirFolder'tasks.c
%include freeRTOS\tasks.c

%FILE %'DirRel_Code'%'RTOSDirFolder'mpu_wrappers.h
%include freeRTOS\mpu_wrappers.h

%FILE %'DirRel_Code'%'RTOSDirFolder'timers.h
%include freeRTOS\timers.h

%FILE %'DirRel_Code'%'RTOSDirFolder'timers.c
%include freeRTOS\timers.c

%if %CommandInterpreterEnabled='yes'
  %FILE? %'DirRel_Code'%'RTOSDirFolder'CommandInterpreter.h
  %include freeRTOS\CommandInterpreter.h

  %FILE? %'DirRel_Code'%'RTOSDirFolder'CommandInterpreter.c
  %include freeRTOS\CommandInterpreter.c
%endif