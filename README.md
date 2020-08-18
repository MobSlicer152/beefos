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
qemu-system-i386 -kernel build/beefkern.img
```

Or, the `createiso.sh` script automatically builds the kernel and boot image.
