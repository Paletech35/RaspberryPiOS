#include <stddef.h>
#include <stdint.h>
#include "io.h"
#include "graphics.h"
#include "terminal.h"
#include "printf.h"

void delay(int32_t count)
{
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		 : "=r"(count): [count]"0"(count) : "cc");
}

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	// initialize UART for Raspi1
	uart_init();
	init_printf(0, putc);
	uart_puts("Hello, kernel World!\r\n");
	
	int test = 10;
	printf("Hey there! %d \r\n", test);
	
	initialise_fb();
	
	for (int x = 0; x < 100; x++){
		for (int y = 0; y < 100; y++){
			pixel(x, y, 0xFFFFFF);
		}
	}
	
	drawString("Hello, \nkernel World!\r\n", 10, 10, 0xFF0000, 0x00FFFF);
	
	drawString("This string goes off the edge of the screen", 1000, 100, 0xFF0000, 0x00FFFF);
	
	terminal_init();
	terminal_write_line("This is a line, written in the terminal");
	terminal_draw;
 
	while (1)
		uart_putc(uart_getc());
}
