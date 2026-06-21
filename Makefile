CC=gcc
LD=ld

CFLAGS=\
-std=gnu11 \
-ffreestanding \
-fno-stack-protector \
-fno-pic \
-m64 \
-mcmodel=kernel \
-Wall \
-Wextra \
-Ikernel

# All *.c from kernel
C_SOURCES := $(shell find kernel -name "*.c")

# Convert:
# kernel/graphics/framebuffer.c
# ->
# build/graphics/framebuffer.o
C_OBJECTS := $(patsubst kernel/%.c,build/%.o,$(C_SOURCES))

ASM_OBJECT := build/start.o

all: dist/ozotu.iso

build:
	mkdir -p build
	mkdir -p dist

# Boot ASM

$(ASM_OBJECT): kernel/boot/start.asm | build
	nasm -f elf64 $< -o $@

build/%.o: kernel/%.c | build
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link

build/kernel.elf: $(ASM_OBJECT) $(C_OBJECTS)
	$(LD) \
		-nostdlib \
		-z max-page-size=0x1000 \
		-T linker.ld \
		$(ASM_OBJECT) \
		$(C_OBJECTS) \
		-o $@

# ISO

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

run: dist/ozotu.iso
	qemu-system-x86_64 \
		-machine q35 \
		-m 512M \
		-bios /usr/share/OVMF/OVMF_CODE.fd \
		-cdrom dist/ozotu.iso \
		-full-screen

clean:
	rm -rf build
	rm -rf dist
	rm -rf iso_root

.PHONY: all run clean
