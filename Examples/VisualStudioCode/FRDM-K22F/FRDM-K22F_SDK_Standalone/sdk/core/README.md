> [!CAUTION]
> __Please move to our new SDK project [mcuxsdk](https://github.com/nxp-mcuxpresso/mcuxsdk-manifests). We have stopped updating this mcux-sdk project, the repo will be archived in 6 months.__

# MCUXpresso SDK: mcux-sdk

![NXP_logo](docs/nxp_logo_small.png)[EN](./README.md)|[中文](./README_CN.md)
[![Version](https://img.shields.io/github/v/release/NXPMicro/mcux-sdk)](https://github.com/NXPmicro/mcux-sdk/releases/latest)
[![Contributors](https://img.shields.io/github/contributors/NXPMicro/mcux-sdk)](https://github.com/NXPmicro/mcux-sdk/graphs/contributors)
[![Issues](https://img.shields.io/github/issues/NXPMicro/mcux-sdk)](https://github.com/NXPmicro/mcux-sdk/issues)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](https://github.com/NXPmicro/mcux-sdk/pulls)

MCUXpresso SDK is a comprehensive software enablement package designed to simplify and accelerate application development with Arm® Cortex®-M-based devices from NXP, including its general purpose, crossover and Bluetooth™-enabled MCUs. This project provides an alternative way for user to achieve the source code of MCUXpresso SDK besides SDK builder and MCUXpresso IDE.

The whole MCUXpresso SDK delivery is composed of separate project/repo deliveries. The idea we split the whole SDK delivery to separate projects/repos is inspired by [Zephyr](https://github.com/zephyrproject-rtos/zephyr), and the projects are split following below rules:
* Fundamental project for device/board enablement with shared drivers and components.
* RTOS projects
* Middleware projects
* Examples project built on above deliveries

In this way we want to benefit user from below aspects:
1. Avoid huge size in a single repository.
2. Provide flexibility for user to select needed projects to build their application.
3. Provide ability for user to fetch needed project version to build their application.

We also uses [Zephyr west tool](https://docs.zephyrproject.org/latest/guides/west/index.html) to do multi-repository management, it allows user to self create ```west.yml``` to select needed projects for downstream use. 

## Overview
This mcux-sdk project/repo provides the fundamental support for all NXP hot parts:

* Arm® CMSIS-CORE startup and device header files and CMSIS-DSP standard libraries
* Open-source peripheral drivers that provide stateless, high-performance, easy-to-use APIs
* Drivers for communication peripherals also include high-level transactional APIs for high-performance data transfers 
* High-quality software: all drivers and startup code are MISRA-C: 2012 compliant and checked with Coverity® static analysis tools

**The project can work solely**, if you only want to get the fundamental support for SoC(s) or board(s), you just use the original Git way to clone and checkout the project.

**The project is also the main repository to achieve the whole SDK delivery**, it contains the [west.yml](https://github.com/NXPmicro/mcux-sdk/blob/main/west.yml) which keeps description and revision for other projects in the overall MCUXpresso delivery. Not all MCUXpresso SDK middleware are available in this MCUXpresso SDK Github delivery, checking west.yml for each release you will see the available middleware included in the release. The superset of available middlewares is listed as below for your information:
- RTOS
  - [FreeRTOS-Kernel](https://github.com/nxp-mcuxpresso/FreeRTOS-Kernel)
- Middleware
  - [Sdmmc](https://github.com/nxp-mcuxpresso/mcux-sdk-middleware-sdmmc)
  - [Multicore(erpc, rpmsg-lite)](https://github.com/nxp-mcuxpresso/mcux-sdk-middleware-multicore)
  - [eIQ(deepviewrt, glow, tensorflow-lite)](https://github.com/nxp-mcuxpresso/mcux-sdk-middleware-eiq)
  - [Fatfs](https://github.com/nxp-mcuxpresso/fatfs)
  - [Usb](https://github.com/nxp-mcuxpresso/mcux-sdk-middleware-usb)
  - [Mbedtls](https://github.com/nxp-mcuxpresso/mbedtls)
  - [Wifi](https://github.com/NXP/wifi_nxp)
  - [Lwip](https://github.com/nxp-mcuxpresso/lwip)
  - [Littlefs](https://github.com/nxp-mcuxpresso/littlefs)
  - [Edgefast_bluetooth(full feature)](https://github.com/nxp-mcuxpresso/mcux-sdk-middleware-edgefast-bluetooth)
  - [Wireless Ethermind(full feature)](https://github.com/NXP/mcux-sdk-middleware-ethermind)
  - [Ieee_802.15.4](https://github.com/NXP/mcux-sdk-middleware-ieee_802.15.4)
  - [Bluetooth-controller](https://github.com/NXP/mcux-sdk-middleware-bluetooth-controller)
  - [Bluetooth-host](https://github.com/NXP/mcux-sdk-middleware-bluetooth-host)
  - [Connectivity-framework](https://github.com/NXP/mcux-sdk-middleware-connectivity-framework)
  - [Maestro framework](https://github.com/nxp-mcuxpresso/maestro)
  - [Mcuboot_opensource](https://github.com/nxp-zephyr/mcuboot)
  - [EAP SDK](https://github.com/nxp-mcuxpresso/EAP)
  - [VIT](https://github.com/nxp-mcuxpresso/VIT)
  - [VoiceSeeker](https://github.com/nxp-mcuxpresso/VoiceSeeker)
  - [NatureDSP](https://github.com/nxp-mcuxpresso/NatureDSP)
  - [Wpa_supplicant-rtos](https://github.com/nxp-mcuxpresso/wpa_supplicant-rtos)
  - [Secure-subsystem](https://github.com/nxp-mcuxpresso/mcux-secure-subsystem)
  - [XCVR](https://github.com/nxp-mcuxpresso/mcux-sdk-middleware-xcvr)

### How to get the whole SDK delivery
You need to have both Git and West installed in order to get a new delivery of the whole SDK or update the existing SDK deliveries. Follow below guide according to your scenario:
* Clone/check-out a new delivery of whole SDK
  
  Execute below commands to achieve the whole SDK delivery at revision ```${revision}``` and place it in a folder named ```mcuxsdk```
  ```
    west init -m https://github.com/NXPmicro/mcux-sdk --mr ${revision} mcuxsdk
    cd mcuxsdk
    west update
    ```
    Replace ```${revision}``` with any SDK revision(branch/tag/commit SHA) you wish to achieve. This can be ```main``` if you want the latest state, or any commit SHA or tag. 

* Update existing west cloned SDK whole delivery
    
    Assume you have followed previous commands to clone/check-out whole SDK delivery to the west workspace mcuxsdk, then the main repository of SDK is located in mcuxsdk/core. If you would like to update/check-out to another revision, you need to first update the main repository to the expected revision, then update the west workspace:
    
    When you would like to update SDK full delivery in the latest branch of main repository, follow below commands:

     ```
    cd mcuxsdk/core
    git pull
    west update
    ```

    If the ```${revision}``` is different revision from that used in main repository, such as different branch, different tag or different commit SHA, you could follow below commands:
    ```
    cd mcuxsdk/core
    git fetch
    git checkout ${revision}
    west update
    ```

## Releases

There are two types of release in the project. The MCUXpresso SDK release and GitHub Main SDK release. Below description uses **MCUX release** short for MCUXpresso SDK release, use **Main release** short for GitHub Main SDK release. **Note currently we only have MCUX releases.**

### MCUX Release
The MCUX release launches once a new release is available on [SDK Builder](http://mcuxpresso.nxp.com/). Users previously using [SDK Builder](http://mcuxpresso.nxp.com/) could easily find the exact same code base MCUX release with same 2.x.y version of SDK archive package, software examples build/run quality are guaranteed in the release. **MCUX releases will be prefixed with 'MCUX_'**, and every release will be merged into main branch to ensure main branch has all released boards/socs support.

The "MCUX_" releases are categorized into mainline releases and NPI release.
* For mainline releases, usually it's planned twice a year to do a global feature update for NXP hot parts. The x in 2.x.y version increments each time a mainline release goes out.
* For NPI release, it aims to support a new soc product recently launched in the market. It is built with verified features in previous mainline release. The release name is suffixed with NPI name to identify it's an NPI release.

Each MCUX release is made on previous mainline release tag/NPI release tag, thus user could easily check the difference between two releases using ````git diff```` command.

### Main Release
The Main release is a regular release made in main branch. It releases the latest code base and feature set on main branch, which is expected to include all the previous 'MCUX_' release content and new enablement on main branch for NXP hot parts. **Main releases will be prefixed with 'MAIN_'**.

Below figure takes 2.9.0 and 2.10.0 release as an example to show the relationship between MCUX release and Main release.
![Release Introduction](docs/Getting_Started/images/github_release_introduction.png)


## Supported development tools and systems
* Tools
    * MCUXpresso IDE
    * GCC ARM Embedded

    For version of the tool used, please check the release notes for each release.
* Systems

    See [Supported development systems](docs/supported_development_systems.md) for the list of boards/socs currently support in this project.

## Getting Started
See [Getting Start Guide](docs/Getting_Started.md) to start explore the project.

## License
Most of software in the project is open-source and licensed under BSD-3-Clause, see [COPYING_BSD-3](COPYING-BSD-3). Whole license information for the project could be found in [SW-Content-Register.txt](SW-Content-Register.txt)

## Contribution
Contributions are greatly welcomed! For detail guideline of contribution please check [Contribution Guide](CONTRIBUTING.md).

