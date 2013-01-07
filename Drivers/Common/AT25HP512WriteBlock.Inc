%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteBlock)
%;**     Description :
%;**         Writes a block of memory to the EEPROM. Note that the EEPROM
%;**         only allows 128 byte page write operation. As such writing
%;**         just a byte will require to read a full page and to write a
%;**         full page.
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - 
%;**       * data%Pardata %>27 - 
%;**         size%Parsize %>27 - 
%;**     Returns     :
%;**         ---%RetVal %>27 - 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
