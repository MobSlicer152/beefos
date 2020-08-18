#!/bin/sh

if [ !-x xorriso ]; then
	printf "This script requires xorriso.\n"
fi

if [ -e isosrc ]; then
	rm -r isosrc
fi

if [ !-e $BUILDDIR/beefkern ]; then
	cmake --build $BUILDDIR
fi

mkdir -p isosrc/boot/grub

printf "Copying kernel and GRUB config."
cp grub.cfg isosrc/boot/grub
printf "."
cp $BUILDDIR/beefkern isosrc/boot
printf ".\n"

grub-mkrescue isosrc -o beefos.iso
