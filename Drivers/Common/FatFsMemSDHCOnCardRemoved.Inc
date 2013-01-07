%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnCardRemoved)
%;**     Description :
%;**         This event is called after a card is removed. The card
%;**         identification number is retrieved and it is passed to the
%;**         event. If card detection pin is not available, the
%;**         SelectCard method calls this event after a try to select the
%;**         removed card.
%include Common\GeneralParameters.inc(27)
%;**       * UserDataPtr%ParUserDataPtr %>27 - Pointer to the user data
%;** %>29 structure.
%;**         Id%ParId %>27 - Card identification number of the removed
%;** %>29 card.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine