readme.txt
----------


I2C_MasterTransferBlocking:

 I2C_MasterClearStatusFlags(base, kClearFlags);
   ok     result = I2C_MasterStart(base 0x40066000, xfer->slaveAddress 0x1c, direction); // write
        
 /* Clear interrupt pending flag. */
   ok         base->S = kI2C_IntPendingFlag;
 
    /* Setup the I2C peripheral to transmit data. */
    base->C1 |= I2C_C1_TX_MASK;

   
   
   ok         base->D = ((xfer->subaddress) >> (8 * xfer->subaddressSize));
   ok       base->S = kI2C_IntPendingFlag;  
   
   ok       result = I2C_MasterRepeatedStart(base, xfer->slaveAddress, kI2C_Read);
   ok         result = I2C_MasterReadBlocking(base, xfer->data, xfer->dataSize, xfer->flags);
    // flags 0      