readme.txt
----------
Project for the FRDM-K22F with FatFS and FreeRTOS, see
https://mcuoneclipse.com/2020/05/20/fatfs-minini-shell-and-freertos-for-the-nxp-k22fn512/

Open Points:
- ioctl does not work properly yet?
- better multi-drive handling in shell
- reduced number of drives (sd, usb)
- test all commands in shell
- configuration items (file print buffer size, ...)
- add mkfs to shell
- USB MSD integration

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
