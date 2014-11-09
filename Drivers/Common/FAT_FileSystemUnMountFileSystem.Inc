%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (UnMountFileSystem)
%;**     Description :
%;**         Mounts a file system
%include Common\GeneralParameters.inc(27)
%;**       * logicalDrive%ParlogicalDrive %>27 - Pointer to the drive
%;** %>29 string, or ""
%;**       * io%Pario %>27 - Pointer to I/O handler
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine