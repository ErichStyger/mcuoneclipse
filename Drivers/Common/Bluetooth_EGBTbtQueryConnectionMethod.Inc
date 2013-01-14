%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btQueryConnectionMethod)
%;**     Description :
%;**         Returns the connection method
%include Common\GeneralParameters.inc(27)
%;**       * method%Parmethod %>27 - Pointer to character which will hold
%;** %>29 the mode: '0' (specified device only,
%;** %>29 default), '1' (can connect to any device),
%;** %>29 '2' (test mode)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine