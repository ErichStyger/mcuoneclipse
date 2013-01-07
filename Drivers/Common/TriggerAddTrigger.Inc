%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (AddTrigger)
%;**     Description :
%;**         Adds a trigger
%include Common\GeneralParameters.inc(27)
%;**         trigger%Partrigger %>27 - The trigger to be added
%;**         incTicks%ParincTicks %>27 - Trigger time, in trigger ticks.
%;** %>29 The time will is relative to the current
%;** %>29 tick time
%;**         callback%Parcallback %>27 - Callback to be called when the
%;** %>29 trigger fires
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine