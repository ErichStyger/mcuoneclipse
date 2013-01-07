%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (lseek)
%;**     Description :
%;**         The f_lseek function moves the file read/write pointer of an
%;**         open file object. It can also be used to increase the file
%;**         size (cluster pre-allocation).
%include Common\GeneralParameters.inc(27)
%;**         fp%Parfp %>27 - Pointer to the file object
%;**         ofs%Parofs %>27 - File pointer from top of file
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine