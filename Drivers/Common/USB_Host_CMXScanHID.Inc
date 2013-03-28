%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ScanHID)
%;**     Description :
%;**         Scans the USB port for devices. Call this function
%;**         periodically.
%include Common\GeneralParameters.inc(27)
%;**       * HID_type%ParHID_type %>27 - Pointer to where the device type
%;** %>29 is stored
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine