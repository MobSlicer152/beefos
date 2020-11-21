#!/bin/sh

if [ $1 ] && [ $1 == "--clean-first" ]; then
	rm -r build
fi

if [ ! -x /usr/bin/xorriso ]; then
	printf "This script requires xorriso.\n"
fi

if [ -e isosrc ]; then
	rm -r isosrc
fi

if [ ! -e $BUILDDIR ]; then
	cmake -S. -B$BUILDDIR -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
fi

if [ ! -e $BUILDDIR/beefkern ]; then
	cmake --build $BUILDDIR
fi

mkdir -p isosrc/boot/grub/themes

if [ ! -e $BUILDDIR/beefkern ]; then
	rm -r isosrc
	exit
fi

printf "Copying kernel and GRUB config."
cp src/grub.cfg isosrc/boot/grub
printf "."
cp $BUILDDIR/beefkern isosrc/boot
printf ".\n"
cp -r grub-theme isosrc/boot/grub/themes/Tela

grub-mkrescue isosrc -o build/beefos.iso

mv build/compile_commands.json .

rm -r isosrc
