#include <stddef.h>
#include <stdint.h>
#include "io.h"
#include "graphics.h"
#include "terminal.h"
#include "printf.h"
#include "mem.h"
#include "timer.h"
#include "irq_handler.h"
#include "gameoflife.h"

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
	
	terminal_init();
	terminal_main();
	//for (int x = 0; x < 100; x++){
	//	for (int y = 0; y < 100; y++){
	//		pixel(x, y, 0xFFFFFF);
	//	}
	//}
	
	//mem_init((atag_t *)atags);
	//interrupts_init();
	
	//drawString((unsigned char *)0x0, 0, 400, 0xFF00, 0xFF00FF);
	
	//timer_init();
	//drawString("Timer inited", 1000, 100, 0xFF00FF, 0xFF00);
	//timer_set(300000);
	
	//drawString((unsigned char *)0x0, 0, 409, 0xFF00, 0xFF00FF);
	
 	//gameoflife();
 	
	while (1)
		uart_putc(uart_getc());
}
