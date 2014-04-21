%-
%- minIni source files
%- 
%-
%FILE %'DirRel_Code'minIni.h
%include minIni\minIni.h

%FILE %'DirRel_Code'minIni.c
%include minIni\minIni.c

%FILE %'DirRel_Code'minGlue.h
%include minIni\minGlue.h

%FILE %'DirRel_Code'minGlue-FatFs.h
%include minIni\minGlue-FatFs.h

%FILE %'DirRel_Code'minGlue-FatFs.c
%include minIni\minGlue-FatFs.c

%FILE %'DirRel_Code'minIni_NOTICE.txt
%include minIni\NOTICE

%FILE %'DirRel_Code'minIni_LICENSE.txt
%include minIni\LICENSE

%- dummy code to include the PDF
%if %minIniVersion='dummy'
  %FILE? %'DirRel_Code'minIni.pdf
  %include minIni\minIni.pdf
%endif