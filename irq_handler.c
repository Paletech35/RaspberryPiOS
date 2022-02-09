#include "io.h"
#include "printf.h"
#include "irq_handler.h"
#include "graphics.h"



__inline__ void enable_interrupts(){
	__asm__ __volatile__("cpsie i");
}

__inline__ void disable_interrupts(){
	__asm__ __volatile__("cpsid i");
}

extern void move_to_zero();


static interrupt_registers_t * interrupt_regs;

void interrupts_init(){
	interrupt_regs = (interrupt_registers_t *)INTERRUPTS_PENDING;
	interrupt_regs->irq_basic_disable = 0xFFFFFFFF;
	interrupt_regs->irq_gpu_disable1  = 0xFFFFFFFF;
	interrupt_regs->irq_gpu_disable2  = 0xFFFFFFFF;
	
	move_to_zero();
	enable_interrupts();
}


void register_irq_handler(irq_number_t irq_num, interrupt_handler_f handler, interrupt_clearer_f clearer){
	unsigned int irq_pos;
	handlers[irq_num] = handler;
	clearers[irq_num] = clearer;
	
	
	if (IRQ_IS_BASIC(irq_num)) {
		irq_pos = irq_num - 64;
		interrupt_regs->irq_basic_enable |= (1 << irq_pos);
		
	} else if (IRQ_IS_GPU2(irq_num)) {
		irq_pos = irq_num - 32;
		interrupt_regs->irq_gpu_enable2 |= (1 << irq_pos);
		
	} else if (IRQ_IS_GPU1(irq_num)) {
		irq_pos = irq_num;
		interrupt_regs->irq_gpu_enable1 |= (1 << irq_pos);
	}
}

void irq_handler(void) {
    for (int i = 0; i < 72; i++){
    	if(IRQ_IS_PENDING(interrupt_regs, i) && (handlers[i] != 0)){
    		clearers[i]();
    		enable_interrupts();
    		handlers[i]();
    		disable_interrupts();
    		return;
    	}
    }
}

void __attribute__ ((interrupt ("ABORT"))) reset_handler(void) {
    printf("RESET HANDLER\n");
    while(1);
}
void __attribute__ ((interrupt ("ABORT"))) prefetch_abort_handler(void) {
    printf("PREFETCH ABORT HANDLER\n");
    while(1);
}
void __attribute__ ((interrupt ("ABORT"))) data_abort_handler(void) {
    printf("DATA ABORT HANDLER\n");
    while(1);
}
void __attribute__ ((interrupt ("UNDEF"))) undefined_instruction_handler(void) {
    printf("UNDEFINED INSTRUCTION HANDLER\n");
    while(1);
}
void __attribute__ ((interrupt ("SWI"))) swi_handler(void) {
    printf("SWI HANDLER\n");
    while(1);
}
void __attribute__ ((interrupt ("FIQ"))) fiq_handler(void) {
    printf("FIQ HANDLER\n");
    while(1);
}

