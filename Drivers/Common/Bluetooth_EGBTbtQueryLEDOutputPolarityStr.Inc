%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btQueryLEDOutputPolarityStr)
%;**     Description :
%;**         Returns the LED output polarity
%include Common\GeneralParameters.inc(27)
%;**       * buf%Parbuf %>27 - Pointer to buffer where to store the LED
%;** %>29 output polarity. LED polarity in <led1,
%;** %>29 <led2> format. 0 for LED output active low,
%;** %>29 1 for LED output active high (default)
%;**         bufSize%ParbufSize %>27 - 
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine