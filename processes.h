#ifndef PROCESSES_H
#define PROCESSES_H

#define NEW_ID next_id++;

typedef struct {
	unsigned int r0;
	unsigned int r1;
	unsigned int r2;
	unsigned int r3;
	unsigned int r4;
	unsigned int r5;
	unsigned int r6;
	unsigned int r7;
	unsigned int r8;
	unsigned int r9;
	unsigned int r10;
	unsigned int r11;
	unsigned int cpsr;
	unsigned int sp;
	unsigned int lr;
}state_t;

typedef struct process_control_block{
	state_t * state;
	void* stack_page;
	unsigned int id;
	struct process_control_block * flink;
	struct process_control_block * blink;
	char name[20];
}pcb_t;

#endif
