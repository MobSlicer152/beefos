#!/bin/sh

source ./buildenv

if [ ! -x /usr/bin/xorriso ]; then
	printf "This script requires xorriso.\n"
fi

if [ -e isosrc ]; then
	rm -r isosrc
fi

if [ ! -e $BUILDDIR ]; then
	cmake -S. -Bbuild
fi

if [ ! -e $BUILDDIR/beefkern ]; then
	cmake --build $BUILDDIR
fi

mkdir -p isosrc/boot/grub/themes

printf "Copying kernel and GRUB config."
cp src/grub.cfg isosrc/boot/grub
printf "."
cp $BUILDDIR/beefkern isosrc/boot
printf ".\n"
cp -r grub-theme isosrc/boot/grub/themes/Tela

grub-mkrescue isosrc -o build/beefos.iso

rm -r isosrc
