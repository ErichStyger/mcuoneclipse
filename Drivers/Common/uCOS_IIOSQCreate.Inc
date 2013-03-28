%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (OSQCreate)
%;**     Description :
%;**         This function creates a message queue if free event control
%;**         blocks are available.
%include Common\GeneralParameters.inc(27)
%;**         start%Parstart %>27 - start is a pointer to the base address
%;** %>29 of the message queue storage area.  The
%;** %>29 storage area MUST be declared as an array
%;** %>29 of pointers to 'void' as follows
%;** %>29 void *MessageStorage[size]
%;**         size%Parsize %>27 - is the number of elements in the storage
%;** %>29 area
%;**     Returns     :
%;**         ---%RetVal %>27 - Returns:
%;** %>29 != (OS_EVENT *)0  is a pointer to the event
%;** %>29 control clock (OS_EVENT) associated with
%;** %>29 the created queue
%;** %>29 == (OS_EVENT *)0  if no event control
%;** %>29 blocks were available or an error was
%;** %>29 detected
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine