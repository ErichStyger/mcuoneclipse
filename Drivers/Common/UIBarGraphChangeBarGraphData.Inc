%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ChangeBarGraphData)
%;**     Description :
%;**         Changes an existing bar and only repaints the needed area.
%include Common\GeneralParameters.inc(27)
%;**       * window%Parwindow %>27 - Pointer to window
%;**       * barGraph%ParbarGraph %>27 - Pointer to bargraph
%;**         index%Parindex %>27 - index of column to change
%;**         newData%ParnewData %>27 - New data elements, in the range of
%;** %>29 0 to 100
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine