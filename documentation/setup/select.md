# Overview

Time to set up the Eurorack-blocks environment!

We support a lot of different environment, wether you are using macOS, Windows or Linux,
or are using C++, Max or Faust.

Making a smooth installation was harder to achieve, because of the cardinality of possible
configurations. We've tried to best to give you a effortless user experience.
If you have any error, make sure to browse our troubleshootin section (coming soon),
or to [open a new issue](https://github.com/ohmtech-rdi/eurorack-blocks/issues/new) to
tell us what went wrong, so we can help you.


## macOS

If you are a macOS user, please choose below the ecosystem you wish to install.

- [C++ with Xcode](./macos-cpp-xcode.md)
- [C++ with Visual Studio Code](./macos-cpp-vscode.md)
- [C++ with command line only](./macos-cpp-cli.md)
- [Max/MSP](./macos-max.md)
- [Faust](./macos-faust.md)

If you want to do C++ but are not sure what to choose, we would advise Xcode as this
gives the best debugging experience.
On the other hand Visual Studio Code allows to debug the firmware running on the target
hardware using a special adapter.
But you can always change your mind later anyway, or you can even install both at
the same time.


## Windows

If you are a Windows user, please choose below the ecosystem you wish to install:

- [C++ with Visual Studio Code](./windows-cpp-vscode.md)
- [C++ with command line only](./windows-cpp-cli.md)
- [Max/MSP](./windows-max.md)
- [Faust](./windows-faust.md)


## Linux

If you are a Linux user, please choose below the ecosystem you wish to install:

- C++ with Visual Studio Code
- C++ with command line only
- Faust


## Upgrading Eurorack-blocks

Eurorack-blocks doesn't produce (yet) releases. We use "rolling updates", as a way to have
a lightweight process for users to get the latest features very quickly.

To upgrade Eurorack-blocks to the latest version you just need to get the latest code using
`git` and setting up erbb again.

For example if you are using Visual Studio Code, you would just do the following:

```{code-block} shell-session
MyMac:~/eurorack-blocks $ git pull
MyMac:~/eurorack-blocks $ erbb setup --with-vscode-support
```
