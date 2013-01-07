%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetSensorInformation)
%;**     Description :
%;**         Reads the sensor information from the device. If the buffer
%;**         is not large enough to get all the information, then the
%;**         next call to this function will return the remaining
%;**         information. In any case the buffer passed will be zero
%;**         terminated.
%include Common\GeneralParameters.inc(27)
%;**       * buf%Parbuf %>27 - pointer to a buffer for the information.
%;**         bufSize%ParbufSize %>27 - size of the buffer, including zero
%;** %>29 byte. A buffer size of at least 45 bytes
%;** %>29 should be passed.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
