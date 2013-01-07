%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ChangeCalendarDay)
%;**     Description :
%;**         Increases or decreases the calendar day for a calendar day
%;**         item. The method cares as well about leap years.
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to window
%;**       * calendarDay%ParcalendarDay %>27 - Pointer to calendar day
%;** %>29 item
%;**         changeDays%ParchangeDays %>27 - number of days to increment.
%;** %>29 Note that the argument is positive for the
%;** %>29 future and negative to move the date back
%;**         changeMinutes%ParchangeMinutes %>27 - Number of minutes to
%;** %>29 change the start time. Positive to change
%;** %>29 it to the future, and negative to change it
%;** %>29 to the back.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
