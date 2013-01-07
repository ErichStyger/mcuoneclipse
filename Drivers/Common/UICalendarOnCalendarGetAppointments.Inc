%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnCalendarGetAppointments)
%;**     Description :
%;**         Event called in order to get a list of appointment. Note
%;**         that the list needs to remain in memory until the next call.
%include Common\GeneralParameters.inc(27)
%;**       * startHint%ParstartHint %>27 - Pointer to the start date/time
%;** %>29 the event is interested in. As the event is
%;** %>29 requesting only appointments for a certain
%;** %>29 day, you may limit the amount of data
%;** %>29 passed.
%;**       * appointmentList%ParappointmentList %>27 - Pointer to linked
%;** %>29 list of appointments. The callee has to
%;** %>29 return here the pointer to the first
%;** %>29 element of the list.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine