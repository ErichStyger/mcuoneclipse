# Hello World

This is a project created with the
[xpack/hello-world-template-xpack](https://github.com/xpack/hello-world-template-xpack) GitHub project.

The project not only demonstrates the xPack Managed Builds,
but also provides a functional starting point for real applications.

## Build configurations

The project borrows the structure from Eclipse CDT projects,
with two condfigurations, **Debug** and **Release**.

## Out of source tree builds

Having two build configurations, each with its own build folder,
the builds inherently cannot run in the source tree and require
separate build folders.

The two build folders are:

- `build/debug`
- `build/release`

## Project structure

The code is split into separate `src` and `include` folders.

The project also demonstrates a simple library, located in the separate
`libs/adder` folder.

The project tries to avoid placing files in the root folder, thus
build specific files are located in the `meta` folder.

## `xpm install`

As usual with npm and xpm projects, to facilitate running the tests
on Continuous Integration environments there is a way to automate
installing the required tools,
like build tools, defined as `devDependencies`.

This mechanism is also useful during normal development, so it is
recommended to use the existing binary xPacks as build tools, by
listing them in the `devDependencies`.

Even more, it is possible to define dependencies specific to
build configurations, which allows, for example, to run the builds
with different versions of the same toolchain.

The command can be invoked by running it in a terminal:

```sh
cd <project>
xpm install
```

The same functionality can be obttained in VS Code, as menu
**Terminal** → **Run Task...** which simply executes the command.

## Actions

The project has several actions for each build configuration:

- `prepare`: create the build folders
- `build`: update the build folders to cope with possible changes in
  the project structure, and run the actual build
- `clean`: remove all binary objects and temporary files; do not delete
  build folder
- `execute`: run the application

There are also some top actions, which perform the corresponding actions
on both configurations.

- `prepare-all`
- `build-all`
- `clean-all`
- `execute-all`
- `test`

The `test` action performs the prepare/build/execute, and can be used
to test the project in CI environments.

The full test suite can be invoked with a simple command:

```sh
xpm run test
```

## IntelliSense

The project is VS Code friendly, and when using the VS Code xPack
Managed Build Tools extension the `.vscode/c_cpp_properties.json` file
is managed automatically.

The best way to configure IntelliSense is to use a
`compile_commands.json` file, since this fully automates the process.

An example of such a file is:

```json
{
  "configurations": [
    {
      "name": "Debug",
      "configurationProvider": "ms-vscode.cmake-tools",
      "compileCommands": "${workspaceFolder}/build/debug/compile_commands.json"
    },
    {
      "name": "Release",
      "configurationProvider": "ms-vscode.cmake-tools",
      "compileCommands": "${workspaceFolder}/build/release/compile_commands.json"
    }
  ],
  "version": 4
}
```

This file is automatically created and updated by the xPack extension, so
the user should not be very concerned with it.

However, only modern tools (like CMake and meson) can generate this file.

If the project uses other tools, like autotools & make, the
`c_cpp_properties.json` file must be edited and specific details (like
the include folders an preprocessor definitions) must be provided
for each build configuration.

An example of such a file is:

```json
{
  "configurations": [
    {
      "name": "Debug",
      "configurationProvider": "ms-vscode.makefile-tools",
      "includePath": [
        "${workspaceFolder}/include",
        "${workspaceFolder}/libs/adder/include"
      ],
      "defines": [
        "DEBUG"
      ]
    },
    {
      "name": "Release",
      "configurationProvider": "ms-vscode.makefile-tools",
      "includePath": [
        "${workspaceFolder}/include",
        "${workspaceFolder}/libs/adder/include"
      ],
      "defines": [
        "NDEBUG"
      ]
    }
  ],
  "version": 4
}
```
