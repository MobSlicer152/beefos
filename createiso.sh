#!/bin/sh

if [[ !-x xorriso ]]; then
	printf "This script requires xorriso.\n"

if [[ -e isosrc ]]; then
	rm -r isosrc
fi

mkdir -p isosrc/boot/grub

printf "Copying kernel and GRUB config."
cp grub.cfg isosrc/boot/grub
printf "."
cp build/beefkern isosrc/boot
printf ".\n"

grub-mkrescue isosrc -o beefos.iso
