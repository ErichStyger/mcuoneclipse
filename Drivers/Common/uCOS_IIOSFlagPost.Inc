%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSFlagPost)
%;**     Description :
%;**         This function is called to set or clear some bits in an
%;**         event flag group.  The bits to set or clear are specified by
%;**         a 'bit mask'.
%include Common\GeneralParameters.inc(27)
%;**       * pgrp%Parpgrp %>27 - Pointer to the desired event flag group.
%;**         flags%Parflags %>27 - If 'opt' (see below) is OS_FLAG_SET,
%;** %>29 each bit that is set in 'flags' will  set
%;** %>29 the corresponding bit in the event flag
%;** %>29 group.
%;**         opt%Paropt %>27 - indicates whether the flags will be: set
%;** %>29 (OS_FLAG_SET) or cleared (OS_FLAG_CLR)
%;**       * perr%Parperr %>27 - Pointer to an error code
%;**     Returns     :
%;**         ---%RetVal %>27 - the new value of the event flags bits that
%;** %>29 are still set.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine