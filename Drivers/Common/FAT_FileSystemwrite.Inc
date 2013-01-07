%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (write)
%;**     Description :
%;**         Write to a file
%include Common\GeneralParameters.inc(27)
%;**         fp%Parfp %>27 - Pointer to the file object structure 
%;**         buff%Parbuff %>27 - Pointer to the data to be written
%;**         btw%Parbtw %>27 - Number of bytes to write
%;**         bw%Parbw %>27 - Pointer to the variable to return number of
%;** %>29 bytes written
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine