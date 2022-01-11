#include <stdint.h>
#include <stddef.h>
#include "io.h"
#include "kernel.h"
void mmio_write(long reg, unsigned int val){
	*(volatile unsigned int *)reg = val;
}

unsigned int mmio_read(long reg){
	return *(volatile unsigned int *)reg;
}

void uart_init()
{
	
 
	// Disable UART0.
	mmio_write(UART_CR, 0x00000000);
	// Setup the GPIO pin 14 && 15.
 
	// Disable pull up/down for all GPIO pins & delay for 150 cycles.
	mmio_write(GPPUD, 0x00000000);
	delay(150);
 
	// Disable pull up/down for pin 14,15 & delay for 150 cycles.
	mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);
 
	// Write 0 to GPPUDCLK0 to make it take effect.
	mmio_write(GPPUDCLK0, 0x00000000);
 
	// Clear pending interrupts.
	mmio_write(UART_ICR, 0x7FF);
 
	// Set integer & fractional part of baud rate.
	// Divider = UART_CLOCK/(16 * Baud)
	// Fraction part register = (Fractional part * 64) + 0.5
	// Baud = 115200.
 
	
 
	// Divider = 3000000 / (16 * 115200) = 1.627 = ~1.
	mmio_write(UART_IBRD, 1);
	// Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40.
	mmio_write(UART_FBRD, 40);
 
	// Enable FIFO & 8 bit data transmission (1 stop bit, no parity).
	mmio_write(UART_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
 
	// Mask all interrupts.
	mmio_write(UART_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
	                       (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));
 
	// Enable UART0, receive & transfer part of UART.
	mmio_write(UART_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

void uart_putc(unsigned char c)
{
	// Wait for UART to become ready to transmit.
	while ( mmio_read(UART_FR) & (1 << 5) ) { }
	mmio_write(UART_DR, c);
}
 
unsigned char uart_getc()
{
    // Wait for UART to have received something.
    while ( mmio_read(UART_FR) & (1 << 4) ) { }
    return mmio_read(UART_DR);
}
 
void uart_puts(const char* s)
{
	for (size_t i = 0; s[i] != '\0'; i ++)
		uart_putc((unsigned char)s[i]);
}

void uart_putnum(unsigned int num)
{
	for (int i = 7; i >= 0; i--){
		unsigned char c = num >> (i * 4);
		c &= 0xF;
		if (c >= 0xA){
			c += 7;
		}
		uart_putc(c + 0x30);
	}
}
