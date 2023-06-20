# C++ on macOS with Xcode


## Requirements

First, please note that macOS 10.11 (Big Sur) or later is recommended.

```{note}
macOS 10.15 (Catalina) has limited support. Some tools do not always work
properly, so macOS 11 (Big Sur) or later is recommended.
```

Before we can setup Eurorack-blocks, we will need to have on your system:

- [`git`](https://git-scm.com/download)
- [Python 3](https://www.python.org/downloads/)
- [Xcode version 11 or later](https://developer.apple.com/xcode/)
- [VCV Rack version 2](https://vcvrack.com/Rack)

If you are a developer, there is a chance that most of them are installed already.

In all cases, please make sure that the Python in use is not the one from Xcode.
You can verify this by typing `which python3` in the Terminal and looking for the mention
of `Xcode` in the returned path. If this command didn't return anything, then you do not
have Python installed, and please use the link above to install it.

Experienced developers might already have one (or multiple!) versions of Python installed.
For Eurorack-blocks, please use at least Python 3.7.

```{note}
Please use the copy button on the top right corner of the following code blocks
to copy/paste the commands in your terminal.
```


## Cloning

First, clone the repository. This will create a `eurorack-blocks` directory **into the current working directory**, with all dependencies.

```{code-block} shell-session
MyMac:~ $ git clone --recurse-submodules https://github.com/ohmtech-rdi/eurorack-blocks.git
```

Will typically output:

```{code-block} shell-session
Cloning into 'eurorack-blocks'...
remote: Enumerating objects: 14327, done.
...
Submodule path 'submodules/libDaisy/tests/googletest': checked out 'f5e592d8ee5ffb1d9af5be7f715ce3576b8bf9c4'
Submodule path 'submodules/vcv-rack-sdk': checked out '91fd742827c04d36ba9b0e5e179571e393682326'
```


## Setting up

First change the current directory to `eurorack-blocks`:

```{code-block} shell-session
MyMac:~ $ cd eurorack-blocks
```

Then install by running the script below:

```{code-block} shell-session
MyMac:~/eurorack-blocks $ ./build-system/install.py
```

This will add the `erbb` script to your `PATH`, but the `PATH` will be set only for new terminals.
You can either close your current terminal and open a new one, or source the `erbb` environment
explicitly into your current shell session:

```{code-block} shell-session
MyMac:~/eurorack-blocks $ source ./build-system/init.sh
```

Then:

```{code-block} shell-session
MyMac:~/eurorack-blocks $ erbb setup --with-xcode-support
```

This will take a bit of time depending on your Internet connection.

`erbb setup` by itself is installing dependencies internally without modifying anything on
your system. If you delete the `eurorack-blocks` folder, boom, everything is gone.

The additional options, usually starting with `--with` do change your system. For example
here we install the syntax highlighting for the custom languages that Eurorack-blocks use,
but this is pretty harmless.

If you want to see exactly what it does and copy, navigate to `build-system/setup/__init__.py`,
and look at the `install_xcode_support` function.

You can now start to use `eurorack-blocks` 🎉



