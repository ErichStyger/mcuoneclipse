# Overview of FAT file system update operations

The FAT file system is operated by operations such as updating directory entries, updating the file allocation table and sending data to the cluster. Note that the procedure for these operations differs slightly between operating systems.

## Create

For macos

1. write file blocks to unassigned clusters
2. update File allocation table
3. update dir entry. The clusters written in step 1 are specified

For Windows 11

1. update dir entry. The cluster to which the file belongs is set to 0.
2. update dir entry. The cluster to be assigned is specified. Not yet allocated.
3. write the file block to the cluster specified in step 2.
4. update File allocation table

## Update

For macos

1. write file blocks to unassigned clusters
2. update File allocation table
3. update dir entry. The cluster to which the file belongs is set to 0.
4. update dir entry. The clusters written in step 1 are specified.

For Windows 11

1. update dir entry. The cluster to which the file belongs is set to 0.
2. update File allocation table
3. update dir entry. A new cluster is specified.
4. write the file block to the cluster specified in step 3
5. update File allocation table.

## Rename

For macos

1. update dir entry. The old filename is flagged for deletion and a new file entry is added at the same time. Clusters have the same.

For Windows 11

1. The file name of the directory entry is changed.

## Move

1. update the origin dir entry. Attach deletion flag to filename.
2. add files to the destination directory entry. Clusters have the same.

## Delete

1. update dir entry. Assign a delete flag to the filename
2. update File allocation table.

## About Directory Entries

About directory entries Directory entries are data structures that hold information on files and directories held in the file system. Each directory is assigned a unique cluster number. A directory entry holds the names and cluster numbers of the files and directories belonging to the directory.The FAT file system can scan all directories starting from the root directory. Directory entries other than the root hold the cluster number of the parent directory. Note that only references to the root directory are specified with cluster number 0.
