#include "io.h"
#include "printf.h"

#define IRQ_IS_BASIC(x) ((x >= 64 ))
#define IRQ_IS_GPU2(x) ((x >= 32 && x < 64 ))
#define IRQ_IS_GPU1(x) ((x < 32 ))
#define IRQ_IS_PENDING(regs, num) ((IRQ_IS_BASIC(num) && ((1 << (num-64)) & regs->irq_basic_pending)) || (IRQ_IS_GPU2(num) && ((1 << (num-32)) & regs->irq_gpu_pending2)) || (IRQ_IS_GPU1(num) && ((1 << (num)) & regs->irq_gpu_pending1)))

extern void move_to_zero(void);

typedef struct {
    unsigned int irq_basic_pending;
    unsigned int irq_gpu_pending1;
    unsigned int irq_gpu_pending2;
    unsigned int fiq_control;
    unsigned int irq_gpu_enable1;
    unsigned int irq_gpu_enable2;
    unsigned int irq_basic_enable;
    unsigned int irq_gpu_disable1;
    unsigned int irq_gpu_disable2;
    unsigned int irq_basic_disable;
} interrupt_registers;

typedef void (*interrupt_handler)(void);
static interrupt_handler handlers[72];

typedef void (*interrupt_clearer)(void);
static interrupt_clearer clearers[72];

typedef enum {
    SYSTEM_TIMER_1 = 1,
    USB_CONTROLER = 9,
    ARM_TIMER = 64
} irq_number_t;

void irq_handler(void) {
    printf("IRQ HANDLER\n");
    while(1);
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
void __attribute__ ((interrupt ("SWI"))) software_interrupt_handler(void) {
    printf("SWI HANDLER\n");
    while(1);
}
void __attribute__ ((interrupt ("FIQ"))) fiq_handler(void) {
    printf("FIQ HANDLER\n");
    while(1);
}

