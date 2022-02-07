#include <stddef.h>
#include "mem.h"
#include "kernel.h"

extern unsigned char __end;
static unsigned int page_count;

static page_t * pages;
page_list_t free_pages;

heap_segment_t * heap_start;

page_t * page_list_get(page_list_t  list, unsigned int index){
	page_list_item_t * currPage = list.head;
	for (int i = 0; i < index; i++){
		currPage = currPage->flink;
	}
	return currPage->page_data;
}

void page_list_append(page_list_t  list, page_t * page){
	if (list.size != 0){
		static page_list_item_t new;
		new.page_data = page;
		new.blink = list.tail;
		new.flink = list.head;
		list.tail->flink = &new;
		list.head->blink = &new;
		list.tail = &new;
		list.size++;
	} else {
		static page_list_item_t new;
		new.page_data = page;
		new.blink = &new;
		new.flink = &new;
		list.head = &new;
		list.tail = &new;
		list.size++;
	}
}

void page_list_prepend(page_list_t  list, page_t * page){
	if (list.size != 0){
		static page_list_item_t new;
		new.page_data = page;
		new.blink = list.tail;
		new.flink = list.head;
		list.head->blink = &new;
		list.tail->flink = &new;
		list.head = &new;
		list.size++;
	} else {
		static page_list_item_t new;
		new.page_data = page;
		new.blink = &new;
		new.flink = &new;
		list.head = &new;
		list.tail = &new;
		list.size++;
	}
}

page_t * page_list_pop(page_list_t list){

	page_t * page = list.head->page_data;
	
	page_list_item_t *first = list.head->flink;
	page_list_item_t *last = list.head->flink;
	
	first->blink = last;
	last->flink = first;
	
	list.head = first;
	
	list.size--;
	
	return page;
}

void mem_init(atag_t *atags){
	unsigned int memsize;
	atag_t *tag;
	tag = atags;
	while (tag->tag != NONE){
		if (tag->tag == MEM){
			memsize = tag->mem.size;
		}
		tag += tag->size;
	}
	page_count = memsize >> 12;
	unsigned int page_array_size = page_count * sizeof(page_t);
	pages = (page_t*)&__end;
	
	unsigned int remaining = page_array_size;
	unsigned char * pages_temp = (unsigned char *)pages;
	while (remaining--){ // Zero out the space for the pages array
		*pages_temp++ = 0;
	}
	for (int i = 0; i < page_count; i++){
		if (i < ((unsigned int)&__end) >> 12){
			pages[i].allocated = 1;
			pages[i].kernel = 1;
		} else if (i < ((((unsigned int)&__end) >> 12) + HEAP_SIZE)){
			pages[i].allocated = 1;
			pages[i].kernel_heap = 1;
		} else {
			pages[i].allocated = 0;
			page_list_append(free_pages, &pages[i]);
		}
	}
	
	heap_start = (heap_segment_t*)((unsigned int)&__end + page_array_size);
	heap_start->flink = NULL;
	heap_start->blink = NULL;
	heap_start->size = HEAP_SIZE;
	
}

void * alloc_page(){
	if (free_pages.size == 0) return 0;
	
	page_t * page;
	page = page_list_pop(free_pages);
	page->kernel = 1;
	page->allocated = 1;
	
	void * page_mem = (void*)((page - pages) << 12);
	
	return page_mem;
}

void * free_page(void* ptr){
	page_t * page;
	
	page = (pages + ((unsigned int)ptr >> 12));
	page_list_append(free_pages, page);
	page->allocated = 0;
	
}

void * kmalloc(unsigned int bytes){
	int smallest_spare = 0xFFFFFFFF >> 1;
	heap_segment_t * best = NULL;
	
	int spare;
	
	bytes += sizeof(heap_segment_t);
	if (bytes % 16){
		bytes += (16 - (bytes % 16));
	}
	
	for (heap_segment_t * segment_ptr = heap_start; segment_ptr != NULL; segment_ptr = segment_ptr-> flink){
	spare = segment_ptr->size - bytes;
		if (spare >= 0 && spare <= smallest_spare && !segment_ptr->allocated){
			best = segment_ptr;
			smallest_spare = spare;
			if (!smallest_spare) goto perfect;
		}
	}
	perfect:if (!best) return NULL;
	
	if (smallest_spare >= (0x10 + sizeof(heap_segment_t))){
		heap_segment_t * segment_ptr = best->flink;
		heap_segment_t * new_addr = (heap_segment_t *)((unsigned int)(best) + bytes);
		best->flink = new_addr;
		new_addr->blink = best;
		new_addr->flink = segment_ptr;
		segment_ptr->blink = new_addr;
		
		new_addr->size = best->size - bytes;
		best->size = bytes;
		
	}
	best->allocated = 1;
	return best + 1;
}

void kfree(heap_segment_t * segment){
	segment--;
	segment->allocated = 0;
	
	while (segment->blink != NULL && !segment->blink->allocated){
		segment->blink->size += segment->size;
		segment->blink->flink = segment-> flink;
		segment->flink->blink = segment->blink;
		
		segment = segment->blink;
	}
	
	while (segment->flink != NULL && !segment->flink->allocated){
		segment->size += segment->flink->size;
		segment->flink = segment->flink->flink;
		segment->flink->blink = segment;
	}
}








