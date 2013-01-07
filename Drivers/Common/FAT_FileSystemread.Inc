%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (read)
%;**     Description :
%;**         Read file
%include Common\GeneralParameters.inc(27)
%;**         fp%Parfp %>27 - Pointer to the file object
%;**         buff%Parbuff %>27 - Pointer to the data buffer
%;**         btr%Parbtr %>27 - Number of bytes to read
%;**         br%Parbr %>27 - Pointer to the number of bytes read
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine