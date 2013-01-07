%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetXYZmg)
%;**     Description :
%;**         Returns the  in milli g of all 3 axes
%include Common\GeneralParameters.inc(27)
%;**       * accel%Paraccel %>27 - Pointer to store the accel of the 3
%;** %>29 acces (minBufSize=3!)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
