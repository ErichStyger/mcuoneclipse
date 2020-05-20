readme.txt
----------

Open Points:
- ioctl does not work properly?
- better multi-drive handling in shell
- reduced number of drives (sd, usb)
- test all commands in shell
- USB MSD integration
- configuration items (file print buffer size, ...)
- test with FF_USE_LFN == 1
- add default change drive (in detect drive?)
- add chdrive to shell
- add mkfs to shell

#if (FF_FS_RPATH >= 2U)
    error = f_chdrive((char const *)&driverNumberBuffer[0U]);
    if (error)
    {
        PRINTF("Change drive failed.\r\n");
        return -1;
    }
#endif

#if FF_USE_MKFS
    PRINTF("\r\nMake file system......The time may be long if the card capacity is big.\r\n");
    if (f_mkfs(driverNumberBuffer, FM_ANY, 0U, work, sizeof work))
    {
        PRINTF("Make file system failed.\r\n");
        return -1;
    }
#endif /* FF_USE_MKFS */
