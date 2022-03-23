#!/usr/bin/env python3

import os
import pathlib
import platform
import shutil
import subprocess
import sys

tools_dir = pathlib.Path(os.path.dirname(sys.argv[0])).resolve()
bin_dir = (tools_dir / ".." / "bin").resolve()
boot_disk = (bin_dir / "boot.vhdx").resolve()
boot_disk_mount = (bin_dir / "boot_mnt").resolve()
create_script_name = (bin_dir / "mkbootdisk.txt").resolve()
detach_script_name = (bin_dir / "detachbootdisk.txt").resolve()
create_script = (
                    f"create vdisk file=\"{boot_disk}\" maximum=200 type=expandable\n" +
                     "attach vdisk noerr\n" +
                     "convert gpt\n" +
                     "create part efi\n" +
                     "format fs=fat32 label=BEEFOS quick\n" +
                    f"assign mount={boot_disk_mount}\n"
                )
detach_script = (
                    f"sel vdisk file=\"{boot_disk}\"\n" +
                     "sel part 2\n" +
                    f"remove mount=\"{boot_disk_mount}\""
                     "detach vdisk noerr\n"
                )

boot_files = [
    ((bin_dir / "boot.efi"), (boot_disk_mount / "EFI" / "boot" / "bootx64.efi")),
    ((tools_dir / "OpenShell.efi"), (boot_disk_mount / "shellx64.efi")),
]

def detach():
    if not detach_script_name.exists():
        print(f"Creating diskpart script {detach_script_name} with contents\n{detach_script}")
        f = open(detach_script_name, "wb+")
        f.write(bytes(detach_script, encoding="utf-8"))
        f.close()
    print(f"Running diskpart /S {detach_script_name}")
    subprocess.run(f"diskpart /S {detach_script_name}")
    print(f"Removing directory {boot_disk_mount}")
    shutil.rmtree(boot_disk_mount)

def mkdir(dir: pathlib.Path):
    if not dir.is_dir():
        if dir.exists():
            shutil.rmtree(dir)
        print(f"Directory {dir} doesn't exist, creating it")
        os.makedirs(dir)

keep_mounted = False
for arg in sys.argv:
    if arg in [ "--no-detach", "--keep-mount", "-k" ]:
        keep_mounted = True
        print("Keeping disk mounted on exit")

mkdir(bin_dir)
mkdir(boot_disk_mount)

if boot_disk.exists():
    print(f"Deleting {boot_disk}")
    detach()
    os.remove(boot_disk)

print(f"Creating {boot_disk}")
if not create_script_name.exists():
    print(f"Creating diskpart script {create_script_name} with contents\n{create_script}")
    f = open(create_script_name, "wb+")
    f.write(bytes(create_script, encoding="utf-8"))
    f.close()

print(f"Running diskpart /S {create_script_name}")
subprocess.run(f"diskpart /S {create_script_name}")

print(f"Copying BeefOS files...")
for f in boot_files:
    print(f"Copying {f[0]} to {f[1]}")
    if not f[1].parent.is_dir():
        print(f"Creating directory {f[1].parent}")
        if f[1].parent.exists():
            os.remove(f[1].parent)
        os.makedirs(f[1].parent)
    shutil.copy(f[0], f[1])

if not keep_mounted:
    detach()
else:
    print(f"Leaving boot disk mounted. Run \"diskpart /S {detach_script_name}\" or enter the following commands in diskpart:\n{detach_script}")

print(f"Done. Successfully created boot disk {boot_disk}")

