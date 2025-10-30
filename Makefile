# === Configuration ===
TARGET = kernel.bin
ASM = nasm
CC = i686-linux-gnu-gcc
LD = i686-linux-gnu-ld

SRC_DIR = src
BUILD_DIR = build

CFLAGS = -m32 -ffreestanding -fno-pic -fno-stack-protector \
         -nostdlib -nostartfiles -nodefaultlibs -I$(SRC_DIR)
LDFLAGS = -m elf_i386 -T link.ld

ISO_DIR = iso
ISO_FILE = kernel.iso

# Collect all C files automatically
C_SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJS = $(BUILD_DIR)/boot.o $(OBJ_FILES)

# === Build Rules ===
all: $(TARGET)

# Assemble bootloader
$(BUILD_DIR)/boot.o: boot.asm | $(BUILD_DIR)
	$(ASM) -f elf32 $< -o $@

# Compile each .c file into build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link everything
$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Run kernel in QEMU via GRUB ISO
run: $(TARGET)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(TARGET) $(ISO_DIR)/boot/kernel.bin
	echo 'menuentry "Delta" { multiboot2 /boot/kernel.bin }' > $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_FILE) $(ISO_DIR)
	qemu-system-i386 -m 256M -cdrom $(ISO_FILE) -d int,cpu_reset -no-reboot -no-shutdown

# Ensure build dir exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Clean GRUB ISO artifacts
clean-iso:
	rm -rf $(ISO_DIR) $(ISO_FILE)

# Clean everything
distclean: clean clean-iso
