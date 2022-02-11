.section "vectable"
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
