#include <stddef.h>
#include <stdint.h>
#include "io.h"
#include "graphics.h"

 
// Loop <delay> times in a way that the compiler won't optimize away
void delay(int32_t count)
{
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		 : "=r"(count): [count]"0"(count) : "cc");
}
 


 

 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
 

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	// initialize UART for Raspi1
	uart_init();
	uart_puts("Hello, kernel World!\r\n");
	
	initialise_fb();
	
	for (int x = 0; x < 100; x++){
		for (int y = 0; y < 100; y++){
			pixel(x, y, 0xFFFFFF);
		}
	}
	
	drawString("Hello, \nkernel World!\r\n", 10, 10, 0xFF0000, 0x00FFFF);
 
	while (1)
		uart_putc(uart_getc());
}
