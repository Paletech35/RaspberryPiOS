#ifndef IRQ_H
#define IRQ_H

#define IRQ_IS_BASIC(x) ((x >= 64 ))
#define IRQ_IS_GPU2(x) ((x >= 32 && x < 64 ))
#define IRQ_IS_GPU1(x) ((x < 32 ))
#define IRQ_IS_PENDING(regs, num) ((IRQ_IS_BASIC(num) && ((1 << (num-64)) & regs->irq_basic_pending)) || (IRQ_IS_GPU2(num) && ((1 << (num-32)) & regs->irq_gpu_pending2)) || (IRQ_IS_GPU1(num) && ((1 << (num)) & regs->irq_gpu_pending1)))

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
} interrupt_registers_t;

typedef enum {
    SYSTEM_TIMER_1 = 1,
    USB_CONTROLER = 9,
    ARM_TIMER = 64
} irq_number_t;

typedef void (*interrupt_handler_f)(void);
static interrupt_handler_f handlers[72];

typedef void (*interrupt_clearer_f)(void);
static interrupt_clearer_f clearers[72];

void register_irq_handler(irq_number_t irq_num, interrupt_handler_f handler, interrupt_clearer_f clearer);

void interrupts_init();

#endif
