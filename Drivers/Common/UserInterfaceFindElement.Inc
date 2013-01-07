%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (FindElement)
%;**     Description :
%;**         Iterates through all elements of a screen with an element
%;**         compare function to find a certain element.
%include Common\GeneralParameters.inc(27)
%;**       * screen%Parscreen %>27 - Pointer to screen
%;**       * pWindow%ParpWindow %>27 - Pointer to window pointer. Used to
%;** %>29 return a result.
%;**       * pElement%ParpElement %>27 - Pointer to element pointer. Used
%;** %>29 to return a result.
%;**         compare%Parcompare %>27 - Comparator function/callback.
%;** %>29 Called for each element and returns TRUE if
%;** %>29 element matches search criteria.
%;**         data%Pardata %>27 - optional data pointer for the compare
%;** %>29 function
%;**     Returns     :
%;**         ---%RetVal %>27 - TRUE if an element has been found matching
%;** %>29 the find function
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine