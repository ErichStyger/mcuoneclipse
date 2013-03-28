%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ScanForHID)
%;**     Description :
%;**         Scans the USB port for devices. Call this function
%;**         periodically.
%include Common\GeneralParameters.inc(27)
%;**       * hid_type%Parhid_type %>27 - Pointer to where the device type
%;** %>29 is stored
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine