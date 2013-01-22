%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btQueryCurrentStateOfDeviceStr)
%;**     Description :
%;**         Query Current Status of the Device
%include Common\GeneralParameters.inc(27)
%;**       * buf%Parbuf %>27 - Pointer to buffer where to the device
%;** %>29 status string, any one of the following:
%;** %>29 INITIALIZED
%;** %>29 READY
%;** %>29 PAIRABLE
%;** %>29 PAIRED
%;** %>29 INQUIRING
%;** %>29 CONNECTING
%;** %>29 CONNECTED
%;** %>29 DISCONNECTED
%;** %>29 UNKNOWN
%;**         bufSize%ParbufSize %>27 - Size of the buffer in bytes.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine