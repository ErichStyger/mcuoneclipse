# Raspberry Pi Pico littlefs USB Flash Memory Interface

This project demonstrates a method for mounting littlefs via USB to facilitate easy retrieval of sensor data and other information stored on microcontrollers from a standard PC.

Littlefs is widely used as a reliable file system for microcontrollers. However, since this file system is not supported by ordinary host PCs, special software and procedures are required for file read and write operations. The core idea of this project is to add an intermediate conversion layer to the USB Mass Storage Class device driver of the microcontroller, mimicking littlefs as a FAT file system. This allows littlefs to be manipulated from the host PC as if it were a USB flash drive with a common FAT file system.

## Demo Overview

The demo operates as follows:

- Each time the BOOTSEL button is clicked, the number of clicks is added to the `SENSOR.TXT` file in the littlefs file system.
- When the Pico is connected to the host PC via USB, it will be mounted as a USB flash drive with a FAT12 file system.
- As a USB flash drive, you can create, read, update, and delete files in littlefs. However, moving directories is not supported.
- Holding down the BOOTSEL button for 3 seconds will format the littlefs file system.

## Build and Installation

The build requires updating the [littlefs](https://github.com/littlefs-project/littlefs) git submodule and instructing CMake how to retrieve the [pico-sdk](https://github.com/raspberrypi/pico-sdk).

```bash
git submodule update --init

mkdir build; cd build
PICO_SDK_FETCH_FROM_GIT=1 cmake ..
make
```

In this instruction, the `PICO_SDK_FETCH_FROM_GIT` environment variable is specified when CMake is run, instructing it to clone the pico-sdk from github. If you want to specify a pico-sdk that has already been deployed locally, specify it in the `PICO_SDK_PATH` environment variable.

After successful compilation, `littlefs-usb.uf2` will be generated. Simply drag and drop it onto your Raspberry Pi Pico to install and run the application.

## Limitations

The current implementation has several limitations:

- Renaming a directory does not result in the expected behaviour: Renaming a directory does not move the directory and its contents, but creates a new directory.
- Large files are slow: It can handle files up to the maximum size of FAT12, but is very slow to read.
- Limited number of files on a directory: The number of files that can be stored in a single directory is limited to a maximum of 16. This is an implementation limitation that may be relaxed in the future.
- No file update detection: The host PC cannot notice when the microcontroller updates a file. Remounting will reflect the update.
- Unrefactored Source Code: The source code has not undergone refactoring.

## Mimicking Process

FAT12 is a very simple file system and can be easily mimicked. Depending on the location of the block device requested by the USB host, the microcontroller assembles and returns the appropriate FAT12 block.

- Block 0: Returns static FAT12 boot block.
- Block 1: Returns the file allocation table (FAT).
- Block 2: Returns the root directory's directory entry.
- Block 3 and later: Returns littlefs file blocks or directory entries.

Upon USB connection, all files in the littlefs file system are searched to build a cache of FAT directory entries. Read requests from the USB host determine the type (file or directory) of the requested object based on the cache. Requests for directories are sent directly from the cache, while requests for files open the corresponding file in littlefs and send its content. Write requests involve updating the cache and reflecting changes in littlefs. The cache is updated based on the differences in directory entries.

See `FAT_OPERATION.md` for details on the sequence of disk operations.

## Testing

The tests directory contains code to verify the API's behavior. After building and installing the test code on the Pico, the unit tests are executed directly on the device, and results are sent via UART.

```bash
make tests
```

To run the tests, transfer the `tests/tests.uf2` file to your Pico. For a more comprehensive debugging experience, connect the [Raspberry Pi Debug Probe](https://www.raspberrypi.com/documentation/microcontrollers/debug-probe.html) to the SWD Debug and UART Serial interfaces of the Pico. Use the following command to install and run the tests:

```bash
make run_tests
```
