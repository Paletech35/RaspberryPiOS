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
	
	unsigned char col[4] = {0, 255, 255, 0};
	
	pixel(1, 1, &col[0]);
	
 
	while (1)
		uart_putc(uart_getc());
}
