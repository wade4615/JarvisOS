del *.o *.bin *.sys *.map *.exe
nasm -felf src/boot.asm -o obj/boot.o
gcc -c -m32 src/kernel.c -o obj/kernel.o -std=gnu99 -ffreestanding -O2
gcc -T src/linker.ld -o output/ntoskrnl.exe -ffreestanding -O2 -nostdlib -lgcc -Xlinker -Map=map/kernel.map obj/kernel.o obj/boot.o
objdump -x obj/boot.o > map/boot.o.map
objdump -x obj/kernel.o > map/kernel.o.map
objdump -x output/ntoskrnl.exe > map/ntoskrnl.exe.map





qemu-system-x86_64 -m 512 -enable-kvm -usb -device usb-host:productid=0x5574,vendorid=0x0781