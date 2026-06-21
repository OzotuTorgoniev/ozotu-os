CC=gcc
LD=ld

CFLAGS=\
-std=gnu11 \
-ffreestanding \
-fno-stack-protector \
-fno-pic \
-m64 \
-Wall \
-Wextra

all: dist/ozotu.iso

build:
	mkdir -p build
	mkdir -p dist

build/start.o: build
	nasm -f elf64 kernel/start.asm -o build/start.o

build/kernel.o: build
	$(CC) $(CFLAGS) -c kernel/kernel.c -o build/kernel.o

build/kernel.elf: build/start.o build/kernel.o
	$(LD) \
		-nostdlib \
		-z max-page-size=0x1000 \
		-T linker.ld \
		build/start.o \
		build/kernel.o \
		-o build/kernel.elf

dist/ozotu.iso: build/kernel.elf limine.conf
	rm -rf iso_root
	mkdir -p iso_root/EFI/BOOT

	cp build/kernel.elf iso_root/
	cp limine.conf iso_root/

	cp limine/limine-bios.sys iso_root/limine.sys
	cp limine/limine-bios-cd.bin iso_root/
	cp limine/limine-uefi-cd.bin iso_root/
	cp limine/BOOTX64.EFI iso_root/EFI/BOOT/

	xorriso -as mkisofs \
		-b limine-bios-cd.bin \
		-no-emul-boot \
		-boot-load-size 4 \
		-boot-info-table \
		--efi-boot limine-uefi-cd.bin \
		-efi-boot-part \
		--efi-boot-image \
		-o dist/ozotu.iso \
		iso_root

run:
	qemu-system-x86_64 \
		-machine q35 \
		-m 512M \
		-bios /usr/share/OVMF/OVMF_CODE.fd \
		-cdrom dist/ozotu.iso

clean:
	rm -rf build
	rm -rf dist
	rm -rf iso_root
