USING UFFS WITH KINETIS NFC_LDD PROCESSOR EXPERT COMPONENT + FREERTOS
======================================================================
Marc Lindahl	8/23/13


NFC_LDD setup
--------------
Set up ECC.
Make sure to set target settings, data area to max available and still have ECC working.
Need at least 12 bytes of spare area (we tell the driver it's data area) for tag and bad block marker.
(sizeof uffs_TagStoreSt = 11)

when initializing NFC_LDD, we set the UserData pointer to our uffs_Device structure,
and we set our uffs_Device->addr->_private to the returned LDD_TDeviceData struct.

need OnDone, don't need OnError.  OnDone has overall error code that's all we need.

Driver notes
------------
driver must track bad block marker and sealed marker, as they must be checked when returning from
ReadPageWithLayout.
