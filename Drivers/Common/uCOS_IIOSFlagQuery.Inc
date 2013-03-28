%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSFlagQuery)
%;**     Description :
%;**         This function is used to check the value of the event flag
%;**         group.
%include Common\GeneralParameters.inc(27)
%;**       * pgrp%Parpgrp %>27 - is a pointer to the desired event flag
%;** %>29 group.
%;**         perr%Parperr %>27 - is a pointer to an error code returned
%;** %>29 to the called:
%;**     Returns     :
%;**         ---%RetVal %>27 - The current value of the event flag group.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine