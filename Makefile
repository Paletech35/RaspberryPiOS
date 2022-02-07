CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
HFILES = $(wildcard *.h)
SFILES = $(wildcard *.S)
OFILES += $(SFILES:.S=.o)
GCCPATH = /home/connor/opt/cross/bin

all: kernel7.img

kernel7.img: $(OFILES) $(HFILES)
	$(GCCPATH)/arm-none-eabi-gcc -T linker.ld -o os.elf -O2 -ffreestanding -nostdlib $(OFILES) -lgcc
	$(GCCPATH)/arm-none-eabi-objcopy os.elf -O binary kernel7.img

%.o: %.S
	$(GCCPATH)/arm-none-eabi-gcc -mcpu=arm1176jzf-s -fpic -ffreestanding -c $< -o $@

%.o: %.c
	$(GCCPATH)/arm-none-eabi-gcc -O2 -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -c $< -o $@

clean:
	rm *.o
