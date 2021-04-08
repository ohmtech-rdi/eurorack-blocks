# Test

Every blocks with has an associated software implementation has a test,
a  minimal implementation to test correctness and  show usage of the block on the software side.


## Configuring

    $ python configure.py

This will create an `artifacts` folder with everything needed to build all the tests.


## Building

    $ python build.py
    ninja: Entering directory `/Users/raf/dev/eurorack-blocks/audio-in-daisy/test/artifacts/out/Release'
    [10/10] LINK test
    OBJCOPY
    ...

This will create as many binary files to upload to the Daisy seed. It is the `<block>.bin` files
output in the `artifacts/out/Release` build directory, where `<block>` is the block
being tested.


## Deploying

    $ python deploy.py --target audio-in-daisy
    Enter the system bootloader by holding the BOOT button down,
    and then pressing, and releasing the RESET button.
    Press Enter to continue...
    Flashing...
    dfu-util 0.9
    [...]
    Downloading to address = 0x08000000, size = 36484
    Download   [=========================] 100%        36484 bytes
    Download done.
    File downloaded successfully
    dfu-util: Error during download get_status
    Run command exited with 74

The option `--target` specifies which firmware block to download to the Daisy Seed. 

Follow the onscreen instructions and this will download the `<block>.bin` firmware to the
Daisy Seed when it is connected to USB, where `<block>` is the block being deployed.

The error 74 reported from `dfu-util` can be safely
ignored.

Alternatively, if `dfu-util` does not work properly on your computer,
one may use the [Daisy Web Programmer](https://electro-smith.github.io/Programmer/)
in the [Chrome](https://support.google.com/chrome/answer/95346) browser instead.
