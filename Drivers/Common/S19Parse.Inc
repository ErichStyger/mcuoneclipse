%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Parse)
%;**     Description :
%;**         Parses an S19 file and calls the callbacks in order to
%;**         process it.
%include Common\GeneralParameters.inc(27)
%;**         getChar%PargetChar %>27 - Iterator to read a character from
%;** %>29 the input stream
%;**       * data%Pardata %>27 - Pointer to data for the iterator
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine