%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btSetBindingBluetoothStr)
%;**     Description :
%;**         Sets the Binding Bluetooth Address.
%include Common\GeneralParameters.inc(27)
%;**       * addr%Paraddr %>27 - Pointer to new bluetooth address sting
%;** %>29 in NAP,UAP,LAP format.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine