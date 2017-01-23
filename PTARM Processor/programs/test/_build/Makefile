
# Set the tools to use.
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

OBJ = _build/startup.o _build/test.o 

_build/%.o: _build/%.s 
	$(AS) -march=armv2a $< -o $@

_build/%.o: %.c 
	$(CC) -I"${PTARM_PATH}/include" -Wall -O0 -g -march=armv2a -mno-thumb-interwork -c $< -o $@
	$(CC) -I"${PTARM_PATH}/include" -Wall -O0 -g -E -CC -march=armv2a -mno-thumb-interwork -c $< -o $@.expanded.c

_build/test.bin: $(OBJ) 
# 	Link
	$(CC) -Wall -O0 -g -Xlinker -T -Xlinker _build/test.lds -Xlinker --fix-v4bx -nostartfiles $^ -o _build/test.elf
# 	Disassemble the elf 
	$(OBJDUMP) --disassemble --reloc --source --syms _build/test.elf > _build/test.asm
# 	Extract the binary part of the code
	$(OBJCOPY) -Obinary _build/test.elf $@
