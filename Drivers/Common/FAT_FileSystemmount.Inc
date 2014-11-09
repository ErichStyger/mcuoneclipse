%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (mount)
%;**     Description :
%;**         Mount/unmount a logical drive
%include Common\GeneralParameters.inc(27)
%;**         fs%Parfs %>27 - pointer to the new file system object (NULL
%;** %>29 for unmount)
%;**       * path%Parpath %>27 - Logical drive number to be
%;** %>29 mounted/unmounted
%;**         opt%Paropt %>27 - options: 0:Do not mount (delayed mount), 1:
%;** %>29 Mount immediately
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine