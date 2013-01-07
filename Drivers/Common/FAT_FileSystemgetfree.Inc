%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (getfree)
%;**     Description :
%;**         Get Number of Free Clusters
%include Common\GeneralParameters.inc(27)
%;**         path%Parpath %>27 - Pointer to the logical drive number
%;** %>29 (root dir)
%;**       * nclst%Parnclst %>27 - Pointer to the variable to return
%;** %>29 number of free clusters
%;**         fatfs%Parfatfs %>27 - Pointer to pointer to file system
%;** %>29 object
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine