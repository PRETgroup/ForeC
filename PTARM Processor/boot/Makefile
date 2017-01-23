# Bootloader make file.
# By David Broman, 2012


AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

bootloader: bootloader.S header.tpl footer.tpl
#	Compile using armv4 architecture
	$(AS) -march=armv4  $< -o $@.o 
# 	Link the bootloader with link script.
	$(LD) -T bootloader.lds -N $@.o -o $@.elf 
# 	Disassemble the elf 
	$(OBJDUMP) -D $@.elf > $@.asm
# 	Extract the binary part of the code
	$(OBJCOPY) -Obinary $@.elf $@
#	Genereate VHDL code from the binary
	perl bin2hex.pl bootloader boot.tmp
	cat header.tpl > bootloader.vhdl
	cat boot.tmp >> bootloader.vhdl
	cat footer.tpl >> bootloader.vhdl
# 	Copy to the VHDL directory
	cp -f bootloader.vhdl ../syn/core/BootROM.vhdl

clean:
	rm -f bootloader *.o *.elf *.tmp *.vhdl *.asm

