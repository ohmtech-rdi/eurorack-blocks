# Xcode `erbb` and `erbui` Syntax Highlighting Support

This folder contains a plug-in to bring syntax highlighting of the `eurorack-blocks`
meta-build-system and UI domain specific languages into Xcode.


## Adding Syntax Highlighting for Xcode

`eurorack-blocks` contains plug-ins to bring syntax highlighting for the `erbb` and  `erbui`
domain specific languages into Xcode.

> Note: For Xcode 11, see the specific installation procedure below.

To install, run the `install.py` script.

    $ cd build-system/xcode
    $ ./install.py

The script will copy the required files into your user Xcode folder:

```
~/Library/Developer/Xcode/Plug-ins/Erbb.ideplugin
~/Library/Developer/Xcode/Specifications/Erbb.xclangspec
~/Library/Developer/Xcode/Plug-ins/Erbui.ideplugin
~/Library/Developer/Xcode/Specifications/Erbui.xclangspec
```

Then restart Xcode.


## Adding Syntax Highlighting for Xcode 11

This section is only relevant to Xcode 11.

Since some parts will modify your installation of Xcode, this is probably better to do it manually.

- Copy `Erbb.ideplugin` and `Erbui.ideplugin` to `~/Library/Developer/Xcode/Plug-ins/`
- Copy `Erbb.xclangspec` and `Erbui.xclangspec` to `/Applications/Xcode.app/Contents/SharedFrameworks/SourceModel.framework/Versions/A/Resources/LanguageSpecifications`
- Copy `Xcode.SourceCodeLanguage.Erbb.plist` and `Xcode.SourceCodeLanguage.Erbui.plist` to `/Applications/Xcode.app/Contents/SharedFrameworks/SourceModel.framework/Versions/A/Resources/LanguageMetadata`

Using the command line (use `sudo` if permissions are denied):

```
cp -r Erbb.ideplugin ~/Library/Developer/Xcode/Plug-ins/
cp Erbb.xclangspec /Applications/Xcode.app/Contents/SharedFrameworks/SourceModel.framework/Versions/A/Resources/LanguageSpecifications
cp Xcode.SourceCodeLanguage.Erbb.plist /Applications/Xcode.app/Contents/SharedFrameworks/SourceModel.framework/Versions/A/Resources/LanguageMetadata

cp -r Erbui.ideplugin ~/Library/Developer/Xcode/Plug-ins/
cp Erbui.xclangspec /Applications/Xcode.app/Contents/SharedFrameworks/SourceModel.framework/Versions/A/Resources/LanguageSpecifications
cp Xcode.SourceCodeLanguage.Erbui.plist /Applications/Xcode.app/Contents/SharedFrameworks/SourceModel.framework/Versions/A/Resources/LanguageMetadata
```

Then restart Xcode.

> Credits for the solution goes to the [Xcode GraphQL syntax highlighting project](https://github.com/apollographql/xcode-graphql).


## Adding Support for New Versions of Xcode

If the bundle is recognized, Xcode will issue a warning when starting for the bundle to be
non-Xcode standard, but Ask it to Load the Bundle. (the bundle does not contain any code anyway).

If the bundle cannot be loaded, this is most likely because it needs to have the exact Xcode
unique identifier in its compatible UUID list.

To do so:

- Open `Erbb.ideplugin/Contents/Info.plist` into a text editor,
- Locate the array of UUID for key `DVTPlugInCompatibilityUUIDs`,
- Add the UUID of your Xcode version (see below).

Repeat the procedure for the `erbui` plug-in:

- Open `Erbui.ideplugin/Contents/Info.plist` into a text editor,
- Locate the array of UUID for key `DVTPlugInCompatibilityUUIDs`,
- Add the UUID of your Xcode version (see below).


To get the UUID of your Xcode version, type in the Terminal:

    defaults read /Applications/Xcode.app/Contents/Info DVTPlugInCompatibilityUUID

Where `Xcode.app` is the Xcode version you use.

Finally, please submit a Pull Request to the `eurorack-blocks` repository with the following properties:

- Branch name: `erbb-erbui-xcode-XXX-support` where `XXX` is the Xcode version for which the UUID is missing,
- One commit with message: `Add Xcode XXX support`,
- Make sure that your branch is on top of the current `main` branch.
