%-
%- FreeRTOS source files
%-
%if defined(RTOSSrcFolderName)
  %define  RTOSSrcDirFolder /%'RTOSSrcFolderName'/
%else
  %define  RTOSSrcDirFolder 
%endif
%if defined(RTOSHeaderFolderName)
  %define  RTOSHeaderDirFolder /%'RTOSHeaderFolderName'/
%else
  %define  RTOSHeaderDirFolder 
%endif
%if defined(RTOSPortFolderName)
  %define  RTOSPortDirFolder /%'RTOSPortFolderName'/
%else
  %define  RTOSPortDirFolder 
%endif
%-
%FILE %'DirRel_Code'%'RTOSHeaderDirFolder'croutine.h
%include freeRTOS\croutine.h

%FILE %'DirRel_Code'%'RTOSSrcDirFolder'croutine.c
%include freeRTOS\croutine.c

%FILE %'DirRel_Code'%'RTOSHeaderDirFolder'FreeRTOS.h
%include freeRTOS\FreeRTOS.h

%FILE %'DirRel_Code'%'RTOSHeaderDirFolder'FreeRTOSConfig.h
%include freeRTOS\FreeRTOSConfig.h

%FILE %'DirRel_Code'%'RTOSSrcDirFolder'heap_1.c
%include freeRTOS\heap_1.c

%FILE %'DirRel_Code'%'RTOSSrcDirFolder'heap_2.c
%include freeRTOS\heap_2.c

%FILE %'DirRel_Code'%'RTOSSrcDirFolder'heap_3.c
%include freeRTOS\heap_3.c

%FILE %'DirRel_Code'%'RTOSSrcDirFolder'heap_4.c
%include freeRTOS\heap_4.c

%FILE %'DirRel_Code'%'RTOSSrcDirFolder'license.txt
%include freeRTOS\license.txt

%FILE %'DirRel_Code'%'RTOSHeaderDirFolder'list.h
%include freeRTOS\list.h

%FILE %'DirRel_Code'%'RTOSSrcDirFolder'list.c
%include freeRTOS\list.c

%FILE %'DirRel_Code'%'RTOSPortDirFolder'port.c
%include freeRTOS\port.c

%FILE %'DirRel_Code'%'RTOSPortDirFolder'portTicks.h
%include freeRTOS\portTicks.h

%FILE %'DirRel_Code'%'RTOSHeaderDirFolder'portable.h
%include freeRTOS\portable.h

%FILE %'DirRel_Code'%'RTOSPortDirFolder'portasm.s
%include freeRTOS\portasm.s

%FILE %'DirRel_Code'%'RTOSPortDirFolder'portmacro.h
%include freeRTOS\portmacro.h

%FILE %'DirRel_Code'%'RTOSHeaderDirFolder'projdefs.h
%include freeRTOS\projdefs.h

%FILE %'DirRel_Code'%'RTOSSrcDirFolder'queue.c
%include freeRTOS\queue.c

%FILE %'DirRel_Code'%'RTOSSrcDirFolder'queue.h
%include freeRTOS\queue.h

%FILE %'DirRel_Code'%'RTOSHeaderDirFolder'semphr.h
%include freeRTOS\semphr.h

%FILE %'DirRel_Code'%'RTOSHeaderDirFolder'StackMacros.h
%include freeRTOS\StackMacros.h

%FILE %'DirRel_Code'%'RTOSHeaderDirFolder'task.h
%include freeRTOS\task.h

%FILE %'DirRel_Code'%'RTOSSrcDirFolder'tasks.c
%include freeRTOS\tasks.c

%FILE %'DirRel_Code'%'RTOSHeaderDirFolder'mpu_wrappers.h
%include freeRTOS\mpu_wrappers.h

%FILE %'DirRel_Code'%'RTOSHeaderDirFolder'timers.h
%include freeRTOS\timers.h

%FILE %'DirRel_Code'%'RTOSSrcDirFolder'timers.c
%include freeRTOS\timers.c

%if %CommandInterpreterEnabled='yes'
  %FILE? %'DirRel_Code'%'RTOSSrcDirFolder'CommandInterpreter.h
  %include freeRTOS\CommandInterpreter.h

  %FILE? %'DirRel_Code'%'RTOSSrcDirFolder'CommandInterpreter.c
  %include freeRTOS\CommandInterpreter.c
%endif

%undef RTOSSrcDirFolder
%undef RTOSHeaderDirFolder
%undef RTOSPortDirFolder