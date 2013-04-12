%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteByteAddress8)
%;**     Description :
%;**         Write a byte to the device using an 8bit memory address:
%;**         (S+i2cAddr+0), (memAddr), (data)...(data+P)
%include Common\GeneralParameters.inc(27)
%;**         i2cAddr%Pari2cAddr %>27 - I2C address of device
%;**         memAddr%ParmemAddr %>27 - Device memory address
%;**         data%Pardata %>27 - Data value
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine