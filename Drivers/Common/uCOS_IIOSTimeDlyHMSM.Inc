%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSTimeDlyHMSM)
%;**     Description :
%;**         This function is called to delay execution of the currently
%;**         running task until some time expires.  This call allows you
%;**         to specify the delay time in HOURS, MINUTES, SECONDS and
%;**         MILLISECONDS instead of ticks.
%include Common\GeneralParameters.inc(27)
%;**         hours%Parhours %>27 - specifies the number of hours that the
%;** %>29 task will be delayed (max. is 255)
%;**         minutes%Parminutes %>27 - 
%;**         seconds%Parseconds %>27 - specifies the number of seconds
%;** %>29 (max. 59)
%;**         milli%Parmilli %>27 - specifies the number of milliseconds
%;** %>29 (max. 999)
%;**     Returns     :
%;**         ---%RetVal %>27 - OS_ERR_NONE
%;** %>29 OS_ERR_TIME_INVALID_MINUTES
%;** %>29 OS_ERR_TIME_INVALID_SECONDS
%;** %>29 OS_ERR_TIME_INVALID_MS
%;** %>29 OS_ERR_TIME_ZERO_DLY
%;** %>29 OS_ERR_TIME_DLY_ISR
%;** %>29 Note(s)    : The resolution on the
%;** %>29 milliseconds depends on the tick rate.  For
%;** %>29 example, you can't do a 10 mS delay if the
%;** %>29 ticker interrupts every 100 mS.  In this
%;** %>29 case, the delay would be set to 0.  The
%;** %>29 actual delay is rounded to the nearest tick.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine