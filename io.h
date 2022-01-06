#define MMIO_BASE 0x20000000

#define VCMBOX         MMIO_BASE + 0XB880
#define MBOX_READ      VCMBOX + 0x0
#define MBOX_POLL      VCMBOX + 0x10
#define MBOX_SENDER    VCMBOX + 0x14
#define MBOX_STATUS    VCMBOX + 0x18
#define MBOX_CONFIG    VCMBOX + 0x1C
#define MBOX_WRITE     VCMBOX + 0x20
#define MBOX_RESPONSE  VCMBOX + 0x80000000
#define MBOX_FULL      VCMBOX + 0x80000000
#define MBOX_EMPTY     VCMBOX + 0x40000000

#define GPFSEL0    MMIO_BASE + 0x200000
#define GPSET0     MMIO_BASE + 0x20001C
#define GPCLR0     MMIO_BASE + 0x200028
#define GPPUPPDN0  MMIO_BASE + 0x2000E4

void mmio_write(long reg, unsigned int val);
unsigned int mmio_read(long reg);
