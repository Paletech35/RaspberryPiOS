.section ".text"

.global move_to_zero

exception_vector:
	ldr	pc, res_abs_addr
	ldr	pc, undef_abs_addr
	ldr	pc, swi_abs_addr
	ldr	pc, prefetch_abort_abs_addr
	ldr	pc, data_abort_abs_addr
	nop
	ldr	pc, irq_abs_addr
	ldr	pc, fiq_abs_addr

res_abs_addr:			.word reset_handler
undef_abs_addr:			.word undefined_instruction_handler
swi_abs_addr:			.word software_interrupt_handler
prefetch_abort_abs_addr:	.word prefetch_abort_handler
data_abort_abs_addr:		.word data_abort_handler
irq_abs_addr:			.word irq_handler_wrapper
fiq_abs_addr:			.word fiq_handler


move_to_zero:
    push    {r4, r5, r6, r7, r8, r9}
    ldr     r0, =exception_vector 
    mov     r1, #0x0000
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8}
    pop     {r4, r5, r6, r7, r8, r9}
    blx     lr

@save registers for IRQ
.macro save_reg
	sub sp, sp, #64
	str r0, [sp, #4 * 0]
	str r1, [sp, #4 * 1]
	str r2, [sp, #4 * 2]
	str r3, [sp, #4 * 3]
	str r4, [sp, #4 * 4]
	str r5, [sp, #4 * 5]
	str r6, [sp, #4 * 6]
	str r7, [sp, #4 * 7]
	str r8, [sp, #4 * 8]
	str r9, [sp, #4 * 9]
	str r10, [sp, #4 * 10]
	str r11, [sp, #4 * 11]
	str r12, [sp, #4 * 12]
	str r13, [sp, #4 * 13]
	str r14, [sp, #4 * 14]
.endm

@load registers for IRQ
.macro load_reg
	ldr r0, [sp, #4 * 0]
	ldr r1, [sp, #4 * 1]
	ldr r2, [sp, #4 * 2]
	ldr r3, [sp, #4 * 3]
	ldr r4, [sp, #4 * 4]
	ldr r5, [sp, #4 * 5]
	ldr r6, [sp, #4 * 6]
	ldr r7, [sp, #4 * 7]
	ldr r8, [sp, #4 * 8]
	ldr r9, [sp, #4 * 9]
	ldr r10, [sp, #4 * 10]
	ldr r11, [sp, #4 * 11]
	ldr r12, [sp, #4 * 12]
	ldr r13, [sp, #4 * 13]
	ldr r14, [sp, #4 * 14]
	add sp, sp, #64
.endm

irq_handler_wrapper:
	sub	lr, lr, #4
	srsdb	sp!, #0x13
	cpsid	if, #0x13
	save_reg
	and	r1, sp, #4
	sub	sp, sp, r1
	push	{r1}
	bl	irq_handler
	pop	{r1}
	add	sp, sp, r1
	load_reg
	rfeia	sp!
