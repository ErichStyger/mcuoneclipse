%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (PrintDiskInfo)
%;**     Description :
%;**         Prints information about the current disk
%include Common\GeneralParameters.inc(27)
%;**         drive%Pardrive %>27 - drive number, starting with zero
%;**       * io%Pario %>27 - Pointer to I/O callbacks
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine