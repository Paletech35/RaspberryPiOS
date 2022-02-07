#ifndef MEM_H
#define MEM_H

#include "kernel.h"

#define HEAP_SIZE 0x100000

typedef struct page{
	unsigned int allocated: 1;
	unsigned int kernel: 1;
	unsigned int kernel_heap: 1;
	unsigned int spare: 5;
}page_t;

typedef struct page_list_item{
	page_t * page_data;
	struct page_list_item * flink;
	struct page_list_item * blink;
} page_list_item_t;

typedef struct page_list{
	page_list_item_t * head;
	page_list_item_t * tail;
	unsigned int size;
} page_list_t;

//heap stuff

typedef struct heap_segment{
	struct heap_segment *flink;
	struct heap_segment *blink;
	unsigned int size;
	unsigned int allocated;
}heap_segment_t;

void mem_init(atag_t * atags);
void * kmalloc(unsigned int bytes);
void kfree(heap_segment_t * segment);

#endif
