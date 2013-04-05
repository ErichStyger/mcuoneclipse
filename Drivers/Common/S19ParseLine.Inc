%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ParseLine)
%;**     Description :
%;**         Parses an S19 input stream line by line and calls the
%;**         callbacks in order to process it.
%include Common\GeneralParameters.inc(27)
%;**       * iteratorInfo%PariteratorInfo %>27 - Pointer to iterator
%;** %>29 information struct
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, ERR_OK for no error
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine