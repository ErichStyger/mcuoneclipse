%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Test)
%;**     Description :
%;**         Test routine to test the driver. Note that this routine
%;**         writes to the EEPROM!
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, possible values
%;** %>29 ERR_OK - OK
%;** %>29 ERR_FAULT - Test failed
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine