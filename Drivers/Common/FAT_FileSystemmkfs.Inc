%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (mkfs)
%;**     Description :
%;**         The f_mkfs fucntion creates a file system on the drive.
%include Common\GeneralParameters.inc(27)
%;**         drive%Pardrive %>27 - Logical drive number
%;**         PartitioningRule%ParPartitioningRule %>27 - When 0 is given,
%;** %>29 a partition table is created into the
%;** %>29 master boot record and a primary DOS
%;** %>29 partition is created and then an FAT volume
%;** %>29 is created on the partition. This is called
%;** %>29 FDISK format and used for harddisk and
%;** %>29 memory cards. When 1 is given, the FAT
%;** %>29 volume starts from the first sector on the
%;** %>29 drive without partition table. This is
%;** %>29 called SFD format and used for floppy disk
%;** %>29 and most optical disk
%;**         AllocSize%ParAllocSize %>27 - Size of the allocation unit.
%;** %>29 Force the allocation unit (cluster) size in
%;** %>29 unit of byte. The value must be power of 2
%;** %>29 and between the sector size and 128 times
%;** %>29 sector size. When invalid value is
%;** %>29 specified, the cluster size is determined
%;** %>29 depends on the volume size.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine