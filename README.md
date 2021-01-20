# BeefOS
A basic operating system made purely for the sake of making an operating system. Currently features simple text printing routines and basic string manipulation.

Usually you can just download the kernel (beefkern) or the GRUB boot disk (beefos.iso) from the Releases page. Then you can run it in QEMU like so:

``` bash
# For just booting the kernel
qemu-system-i386 -kernel beefkern

# Or with the boot disk
qemu-system-i386 beefos.iso
```

And it should look something like this:

![QEMU will display some text and a diagonal line which iterates through the available colors][qemu]

[qemu]: QEMU-test-0.0.1.png

## Build instructions
You'll need a cross toolchain set up as per [this OSDev article](https://wiki.osdev.org/GCC_Cross-Compiler).

If you would like the Makefile to use a different version of the GRUB sources, set the `GRUB_DIR` variable when you run `make`.

Then it should be as simple as doing the following commands:
```bash
source buildenv
# This will fetch GRUB and build everything,
# except currently I'm still working on the kernel
# being recognized properly so expect an error related to chk-kern-mboot
make
make test # Loads the ISO in QEMU
```

To make a bootable USB stick, do something like this (really you just need to be root, have the variables set, and do `make usb`):
```bash
sudo source buildenv; make usb
```
