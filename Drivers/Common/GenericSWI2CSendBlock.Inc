%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendBlock)
%;**     Description :
%;**         When working as a MASTER, this method writes 7 bits of slave
%;**         address plus R/W bit = 0 to the I2C bus and then writes the
%;**         block of characters to the bus. If the component is disabled
%;**         (by the "Disable" method or initialization), the block is
%;**         moved to the output buffer if the 'Output buffer size'
%;**         property is different from zero. The content of the output
%;**         buffer is sent immediately with the stop condition at the
%;**         end when the component is enabled by the "Enable" method.
%;**         After the output buffer transmission, the whole output
%;**         buffer is cleared. The slave address must be specified
%;**         before by the "SelectSlave" method or in component
%;**         initialization section of 'Slave address init' property.
%;**         When working as a SLAVE, this method writes block of
%;**         characters to the bus. If the ERR_NOTAVAIL error code is
%;**         returned, the whole block is successfully sent to a master
%;**         but the master device responds by an acknowledgment instead
%;**         of no acknowledgment sent at the end of the last block byte
%;**         transfer. 'OnError' event is called in this case.
%include Common\GeneralParameters.inc(27)
%;**       * Ptr%ParPtr %>27 - A pointer to the block of data to send
%;**         Siz%ParSiz %>27 - The size of the block
%;**       * Snt%ParSnt %>27 - A pointer to the number of data that are
%;** %>29 sent (copied to buffer)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, possible codes:
%;** %>29 ERR_OK - OK
%;** %>29 ERR_SPEED - This device does not work in
%;** %>29 the active speed mode
%;** %>29 ERR_BUSY - The slave device is busy, it
%;** %>29 does not respond by the acknowledgment
%;** %>29 (MASTER mode only)
%;** %>29 ERR_TXFULL - Output buffer is full (MASTER
%;** %>29 mode only)
%;** %>29 ERR_NOTAVAIL - The master device sends
%;** %>29 acknowledgment instead of no acknowledgment
%;** %>29 after the last byte transfer (SLAVE mode
%;** %>29 only)
%;** %>29 ERR_DISABLED - Device is disabled
%;** %>29 ERR_BUSOFF - Clock timeout elapsed (SLAVE
%;** %>29 mode only)
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine