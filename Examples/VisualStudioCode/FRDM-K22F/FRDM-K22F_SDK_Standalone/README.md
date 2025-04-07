# Standalone Project using NXP SDK
This is a project using the NXP SDK, but in standalone mode.
Standalone means that it only has the necessary parts in the project, and does not use the 'full' SDK git repository.
That way the project is easily shareable with other users or in a classroom environment.

# PATH
It is assumed that the following tools are present in your system PATH:
- cmake
- ninja

# Environment Variables
The project uses the following environment variables:
- `SEGGER_PATH`: SEGGER J-Link installation folder
- `LINKSERVER_PATH`: NXP Linkserver installation folder
- `TOOLCHAIN_PATH`: ARM Cortex-M toolchain binary folder, usually with `bin`
- `TOOLCHAIN_PREFIX`: Same as above, without the `bin`

Example variables for Windows:
```
SEGGER_PATH=c:\Program Files\SEGGER\JLink
LINKSERVER_PATH=C:\NXP\LinkServer
TOOLCHAIN_PATH=C:\arm\toolchain\bin
TOOLCHAIN_PREFIX=C:\arm\toolchain
```
