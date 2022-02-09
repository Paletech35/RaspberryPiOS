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
swi_abs_addr:			.word swi_handler
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

irq_handler_wrapper:
	sub	lr, lr, #4
	srsdb	sp!, #0x13
	cpsid	if, #0x13
	push    {r0-r3, r12, lr}
	and	r1, sp, #4
	sub	sp, sp, r1
	push	{r1}
	bl	irq_handler
	pop	{r1}
	add	sp, sp, r1
	pop     {r0-r3, r12, lr}
	rfeia	sp!
