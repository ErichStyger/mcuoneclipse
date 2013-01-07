%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CheckCardPresence)
%;**     Description :
%;**         This method checks if card has been inserted or removed and
%;**         mounts or unmounts the file system.
%include Common\GeneralParameters.inc(27)
%;**       * cardMounted%ParcardMounted %>27 - Pointer to initialize this
%;** %>29 variable to FALSE on the caller side the
%;** %>29 first time.
%;**         drive%Pardrive %>27 - drive number, pass 0 as default drive
%;**       * fileSystemObject%ParfileSystemObject %>27 - Pointer to 
%;**       * io%Pario %>27 - Pointer to io handler to be used. Can be
%;** %>29 NULL, then no messages are written.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine