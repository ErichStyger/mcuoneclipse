%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (isDiskPresent)
%;**     Description :
%;**         Determines if the disk is present or not (e.g. disk inserted).
%include Common\GeneralParameters.inc(27)
%;**         drv%Pardrv %>27 - Disk drive number
%;**     Returns     :
%;**         ---%RetVal %>27 - TRUE if file system is write protected
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine