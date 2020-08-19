# BeefOS
A basic operating system made purely for the sake of making an operating system. Currently features simple text printing routines and basic string manipulation.

## Build instructions
You'll need a cross-compiler set up to compile for i686-elf, as per [this](https://wiki.osdev.org/GCC_Cross-Compiler) OSDev wiki article.

Then it should be as simple as doing the following commands:
```bash
source buildenv

cmake -S. -Bbuild

make -C build

# Use whatever emulator, I just prefer QEMU
qemu-system-i386 build/beefos.iso
# You can also boot the kernel directly:
qemu-system-i386 build/beefkern
```

Or, the `createiso.sh` script automatically builds the kernel and boot image.

To make a bootable USB stick, do something like this:
```bash
sudo mount /dev/<the partition you want the boot files on> /mnt

sudo grub-install --root-directory=/mnt /dev/<drive the partition belongs to> --target=i386-pc

sudo cp build/beefkern /mnt/boot
```

Note: you have to build the kernel first.

The font used in the GRUB theme background is [Space Mono](https://fonts.google.com/specimen/Space+Mono). The theme itself is from https://github.com/vinceliuice/grub2-themes.
