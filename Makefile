CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
HFILES = $(wildcard *.h)
GCCPATH = /home/connor/opt/cross/bin

kernel7.img: boot.o $(OFILES) $(HFILES) clean
	$(GCCPATH)/arm-none-eabi-gcc -T linker.ld -o os.elf -O2 -ffreestanding -nostdinc -nostdlib boot.o $(OFILES)
	$(GCCPATH)/arm-none-eabi-objcopy os.elf -O binary kernel7.img

boot.o: boot.S
	$(GCCPATH)/arm-none-eabi-gcc -mcpu=arm1176jzf-s -fpic -ffreestanding -c boot.S -o boot.o

%.o: %.c
	$(GCCPATH)/arm-none-eabi-gcc -O2 mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -c $< -O $@

clean
	-rm *.o
