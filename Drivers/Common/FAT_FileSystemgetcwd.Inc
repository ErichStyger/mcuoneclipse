%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (getcwd)
%;**     Description :
%;**         The f_getcwd function retrieves the current directory of the
%;**         current drive in full path string including drive number.
%include Common\GeneralParameters.inc(27)
%;**         Buffer%ParBuffer %>27 - Pointer to the buffer to receive the
%;** %>29 current directory string.
%;**         BufferLen%ParBufferLen %>27 - Size of the buffer in unit of
%;** %>29 TCHAR.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine