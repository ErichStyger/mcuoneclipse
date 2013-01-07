%-
%- FatFS source files
%- 

%FILE %'DirRel_Code'integer.h
%include FatFS\integer.h

%FILE %'DirRel_Code'diskio.h
%include FatFS\diskio.h

%FILE %'DirRel_Code'ff.h
%include FatFS\ff.h

%FILE %'DirRel_Code'ff.c
%include FatFS\ff.c

%FILE %'DirRel_Code'ffconf.h
%include FatFS\ffconf.h

%FILE %'DirRel_Code'00readme.txt
%include FatFS\00readme.txt

%if %CodePage='932'
  %FILE? %'DirRel_Code'cc932.c
  %include FatFS\cc932.c
%elif %CodePage='936'
  %FILE? %'DirRel_Code'cc936.c
  %include FatFS\cc936.c
%elif %CodePage='949'
  %FILE? %'DirRel_Code'cc949.c
  %include FatFS\cc949.c
%elif %CodePage='950'
  %FILE? %'DirRel_Code'cc950.c
  %include FatFS\cc950.c
%elif %UseLFN != '0'
  %FILE? %'DirRel_Code'ccsbcs.c
  %include FatFS\ccsbcs.c
%endif



