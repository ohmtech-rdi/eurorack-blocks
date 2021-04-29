# Xcode ERBUI Syntax Highlighting Support

This folder contains a plug-in to bring syntax highlighting of the `eurorack-blocks` UI
domain specific language into Xcode.


## Adding Syntax Highlighting for Xcode

`eurorack-blocks` contains a plug-in to bring syntax highlighting of the `erbui`
domain specific language into Xcode.

> Note: The plug-in does only work in Xcode 10, as Xcode 11 changed its plug-in format.

To install, run the `install.py` script.

    $ erb/build-system/xcode/install.py

The script will copy the required files into your user Xcode folder:

```
~/Library/Developer/Xcode/Plug-ins/Erbui.ideplugin
~/Library/Developer/Xcode/Specifications/Erbui.xclangspec
```

Then restart Xcode.

If the bundle is recognized, Xcode will issue a warning when starting for the bundle to be
non-Xcode standard, but Ask it to Load the Bundle. (the bundle does not contain any code anyway).

If the bundle cannot be loaded, this is most likely because it needs to have the exact Xcode
unique identifier in its compatible UUID list.

To do so:

- Open `Erbui.ideplugin/Contents/Info.plist` into a text editor,
- Locate the array of UUID for key `DVTPlugInCompatibilityUUIDs`,
- Add the UUID of your Xcode version (see below).

To get the UUID of your Xcode version, type in the Terminal:

    defaults read /Applications/Xcode.app/Contents/Info DVTPlugInCompatibilityUUID

Where `Xcode.app` is the Xcode version you use.

Finally, please submit a Pull Request to the `eurorack-blocks` repository with the following properties:

- Branch name: `erbui-xcode-XXX-support` where `XXX` is the Xcode version for which the UUID is missing,
- One commit with message: `Add Xcode XXX support`,
- Make sure that your branch is on top of the current `main` branch.
