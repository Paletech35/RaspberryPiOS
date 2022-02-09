#include "timer.h"
#include "io.h"
#include "printf.h"
#include "irq_handler.h"
#include <stdint.h>
#include "graphics.h"

int count = 0;
unsigned char * err_msg = "timer irq called!";

static timer_registers_t * timer_regs;

void timer_set(uint32_t usecs) {
        timer_regs->timer1 = timer_regs->counter_low + usecs;
}

static void timer_irq_handler() {
    //printf("timeout :)\n");
    drawString(err_msg, 100, 100, 0xFF00FF, 0xFF00);
    timer_set(3000000);
}

static void timer_irq_clearer() {
    timer_regs->control.timer1_matched = 1;
}

void timer_init(){
	timer_regs = (timer_registers_t *)TIMER_BASE;
	register_irq_handler(SYSTEM_TIMER_1, timer_irq_handler, timer_irq_clearer);
}
