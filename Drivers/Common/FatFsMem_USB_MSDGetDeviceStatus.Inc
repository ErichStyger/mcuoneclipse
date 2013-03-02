%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetDeviceStatus)
%;**     Description :
%;**         Returns the current device status. Is one of the following:
%;**         #define  USB_DEVICE_IDLE, USB_DEVICE_ATTACHED ,
%;**         USB_DEVICE_CONFIGURED, USB_DEVICE_SET_INTERFACE_STARTED,
%;**         USB_DEVICE_INTERFACED, USB_DEVICE_DETACHED, USB_DEVICE_OTHER 
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - Device status
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine