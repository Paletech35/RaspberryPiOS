#define MMIO_BASE 0x20000000

#define VCMBOX         MMIO_BASE + 0XB880
#define MBOX_READ      VCMBOX + 0x0
#define MBOX_POLL      VCMBOX + 0x10
#define MBOX_SENDER    VCMBOX + 0x14
#define MBOX_STATUS    VCMBOX + 0x18
#define MBOX_CONFIG    VCMBOX + 0x1C
#define MBOX_WRITE     VCMBOX + 0x20

#define MBOX_RESPONSE  0x80000000
#define MBOX_FULL      0x80000000
#define MBOX_EMPTY     0x40000000

#define GPFSEL0    MMIO_BASE + 0x200000
#define GPSET0     MMIO_BASE + 0x20001C
#define GPCLR0     MMIO_BASE + 0x200028
#define GPPUPPDN0  MMIO_BASE + 0x2000E4


#define GPIO_BASE  MMIO_BASE +0x200000

#define GPPUD      GPIO_BASE + 0x94
#define GPPUDCLK0  GPIO_BASE + 0x98
 
#define UART_BASE  GPIO_BASE + 0x1000

#define UART_DR      UART_BASE + 0x00
#define UART_RSRECR  UART_BASE + 0x04
#define UART_FR      UART_BASE + 0x18
#define UART_ILPR    UART_BASE + 0x20
#define UART_IBRD    UART_BASE + 0x24
#define UART_FBRD    UART_BASE + 0x28
#define UART_LCRH    UART_BASE + 0x2C
#define UART_CR      UART_BASE + 0x30
#define UART_IFLS    UART_BASE + 0x34
#define UART_IMSC    UART_BASE + 0x38
#define UART_RIS     UART_BASE + 0x3C
#define UART_MIS     UART_BASE + 0x40
#define UART_ICR     UART_BASE + 0x44
#define UART_DMACR   UART_BASE + 0x48
#define UART_ITCR    UART_BASE + 0x80
#define UART_ITIP    UART_BASE + 0x84
#define UART_ITOP    UART_BASE + 0x88
#define UART_TDR     UART_BASE + 0x8C

#define INTERRUPTS_BASE MMIO_BASE + 0xB000
 
void mmio_write(long reg, unsigned int val);
unsigned int mmio_read(long reg);
void uart_init();
void uart_putc(unsigned char c);
unsigned char uart_getc();
void uart_puts(const char *str);
void uart_putnum(unsigned int num);
void putc(void* p, char c);
