%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Write16bitValue)
%;**     Description :
%;**         Writes a 16bit value to the device. Value is written in Big
%;**         Endian.
%include Common\GeneralParameters.inc(27)
%;**         val%Parval %>27 - value to write
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine