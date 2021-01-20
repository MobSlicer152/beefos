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

You also need to have the GRUB 2 sources set up somewhere and point the `buildenv` script to them.

Then it should be as simple as doing the following commands:
```bash
source buildenv

make

# Use whatever emulator, I just prefer QEMU
qemu-system-i386 build/beefos.iso
# You can also boot the kernel directly in QEMU:
qemu-system-i386 build/beefkern
```

To make a bootable USB stick, do something like this:
```bash
sudo mount /dev/<the partition you want the boot files on> /mnt

sudo grub-install --root-directory=/mnt /dev/<drive the partition belongs to> --target=i386-pc

sudo cp build/beefkern /mnt/boot
```

Note: you have to build the kernel first.
