# Define the compiler and the linker. The names might be different if you're using a cross-compiler.
CC=gcc
LD=ld

# Define the assembler.
AS=nasm

# Specify the assembler, compiler, and linker flags.
# -g: Include debug information in the binary.
# -ffreestanding: Tell the compiler that standard library may not exist on the target system.
# -nostdlib: Don't use the standard system startup files or libraries when linking.
# -nostartfiles: Don't use the standard system startup files when linking.
ASFLAGS=-felf32
CFLAGS=-m32 -g -ffreestanding -Wall -Wextra
LDFLAGS=-melf_i386 -nostdlib -nostartfiles

# Specify the names of the output kernel binary and the object files.
KERNEL_BIN=boot/mykernel.bin
OBJS=src/arch/x86/boot.o src/kernel/main.o src/kernel/kernel.o

# The first rule is the one executed when no parameters are fed to the Makefile.
all: $(KERNEL_BIN)

# Rule to create the kernel binary. It depends on the object files.
$(KERNEL_BIN): $(OBJS)
	$(LD) $(LDFLAGS) -T src/link.ld -o $@ $^

# Rule to compile C files.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to assemble assembly files.
%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

# Phony targets for cleaning up and debugging the Makefile.
.PHONY: clean
clean:
	rm -f $(KERNEL_BIN) $(OBJS)

.PHONY: debug
debug:
	@echo "Kernel binary: $(KERNEL_BIN)"
	@echo "Object files: $(OBJS)"
