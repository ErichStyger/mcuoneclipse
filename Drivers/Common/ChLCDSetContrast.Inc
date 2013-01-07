%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetContrast)
%;**     Description :
%;**         Sets the display contrast
%;**         The contrast setting is a signed 2’s complement value. Thus,
%;**         it can range from -128 to +127.  A setting of zero produces
%;**         the default contrast.  This should generally be suitable as
%;**         the display modules have integrated temperature compensation
%;**         and are calibrated at the factory.  Positive contrast values
%;**         brighten the display, while negative values darken the
%;**         display.  The magnitude of the contrast value determines the
%;**         amount of contrast adjustment, with higher magnitudes
%;**         producing the larger effect.  The contrast setting is stored
%;**         in RAM and resets to zero when power is cycled or the RESET
%;**         command is issued.
%include Common\GeneralParameters.inc(27)
%;**         contrast%Parcontrast %>27 - contrast value.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine