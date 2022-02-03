#ifndef MEM_H
#define MEM_H

#include "kernel.h"

typedef struct page{
	unsigned int allocated: 1;
	unsigned int kernel: 1;
	unsigned int spare: 6;
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

void mem_init(atag_t * atags);

#endif
