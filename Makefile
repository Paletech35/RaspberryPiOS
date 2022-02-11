CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
HFILES = $(wildcard *.h)
SFILES = $(wildcard *.S)
OFILES += $(SFILES:.S=.o)
GCCPATH = /home/connor/opt/cross/bin

all: kernel.img

kernel.img: $(OFILES) $(HFILES) linker.ld
	$(GCCPATH)/arm-none-eabi-gcc -T linker.ld -o os.elf -O2 -ffreestanding -nostdlib -Wl,-z,max-page-size=0x1000 $(OFILES) -lgcc
	$(GCCPATH)/arm-none-eabi-objcopy os.elf -O binary kernel.img

%.o: %.S
	$(GCCPATH)/arm-none-eabi-gcc -mcpu=arm1176jzf-s -ffreestanding -c $< -o $@

%.o: %.c
	$(GCCPATH)/arm-none-eabi-gcc -O2 -mcpu=arm1176jzf-s -ffreestanding -std=gnu99 -c $< -o $@

clean:
	rm *.o
