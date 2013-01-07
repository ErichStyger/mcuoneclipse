%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CreateCalendarDay)
%;**     Description :
%;**         Creates a new calendar day element
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to 
%;**       * calendarDay%ParcalendarDay %>27 - Pointer to calendar day
%;** %>29 element
%;**         x%Parx %>27 - x position
%;**         y%Pary %>27 - y position
%;**         width%Parwidth %>27 - width of element
%;**         height%Parheight %>27 - height of element
%;**       * start%Parstart %>27 - Pointer to start date/time for calendar
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
