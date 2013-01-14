%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btSetLEDOutputPolarityStr)
%;**     Description :
%;**         Sets the LED output polarity
%include Common\GeneralParameters.inc(27)
%;**       * ledPolarityStr%ParledPolarityStr %>27 - Pointer to string
%;** %>29 with the LED polarity in <led1,<led2>
%;** %>29 format. 0 for LED output active low, 1 for
%;** %>29 LED output active high (default)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine