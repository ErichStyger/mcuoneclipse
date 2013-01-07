%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (chmod)
%;**     Description :
%;**         Changes the attribute of a file or directory
%;**         Following attribute flags to be set in one or more
%;**         combination of the following flags. The specified flags are
%;**         set and others are cleared.
%;**         AM_RDO	Read only
%;**         AM_ARC	Archive
%;**         AM_SYS	System
%;**         AM_HID	Hidden
%include Common\GeneralParameters.inc(27)
%;**         FileName%ParFileName %>27 - Pointer to the file or directory
%;**         Attribute%ParAttribute %>27 - Attribute flags. Attribute
%;** %>29 flags to be set in one or more combination
%;** %>29 of the following flags. The specified flags
%;** %>29 are set and others are cleard.
%;**         AttributeMask%ParAttributeMask %>27 - Attribute mask.
%;** %>29 Attribute mask that specifies which
%;** %>29 attribute is changed. The specified
%;** %>29 aattributes are set or cleard.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine