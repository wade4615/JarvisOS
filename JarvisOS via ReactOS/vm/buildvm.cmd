qemu-img create -f qcow2 jarvisos.img 1200M
qemu-system-i386 -L . -m 256 -cdrom ..\output-MinGW-i386\bootcd.iso -hda jarvisos.img -boot d -smp 2
