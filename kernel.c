#include <stddef.h>
#include <stdint.h>
#include "io.h"
#include "graphics.h"
#include "terminal.h"
#include "printf.h"
#include "mem.h"
#include "timer.h"
#include "irq_handler.h"

void delay(unsigned int count)
{
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		 : "=r"(count): [count]"0"(count) : "cc");
}

void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{
	// initialize UART for Raspi1
	uart_init();
	initialise_fb();
	init_printf(0, g_putc);
	
	for (int x = 0; x < 100; x++){
		for (int y = 0; y < 100; y++){
			pixel(x, y, 0xFFFFFF);
		}
	}
	
	mem_init((atag_t *)atags);
	interrupts_init();
	timer_init();
	timer_set(3000000);
 
	while (1)
		uart_putc(uart_getc());
}
