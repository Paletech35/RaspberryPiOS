#include "mem.h"
#include "kernel.h"

extern unsigned char __end;
static unsigned int page_count;

static page_t * pages;
page_list_t free_pages;

page_t * page_list_get(page_list_t  list, unsigned int index){
	page_list_item_t * currPage = list.head;
	for (int i = 0; i < index; i++){
		currPage = currPage->flink;
	}
	return currPage->page_data;
}

void page_list_append(page_list_t  list, page_t * page){
	if (list.size != 0){
		static volatile page_list_item_t new;
		new.page_data = page;
		new.blink = list.tail;
		new.flink = list.head;
		list.tail->flink = &new;
		list.head->blink = &new;
		list.tail = &new;
		list.size++;
	} else {
		static volatile page_list_item_t new;
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
		static volatile page_list_item_t new;
		new.page_data = page;
		new.blink = list.tail;
		new.flink = list.head;
		list.head->blink = &new;
		list.tail->flink = &new;
		list.head = &new;
		list.size++;
	} else {
		static volatile page_list_item_t new;
		new.page_data = page;
		new.blink = &new;
		new.flink = &new;
		list.head = &new;
		list.tail = &new;
		list.size++;
	}
}

void mem_init(atag_t *atags){
	unsigned int memsize;
	atag_t *tag;
	tag = atags;
	while (tag->tag != NONE){
		if (tag->tag == MEM){
			memsize = tag->mem.size;
		}
		tag = ((unsigned int *)tag) + tag->size;
	}
	page_count = memsize / 4096;
	unsigned int page_array_size = page_count * sizeof(page_t);
	pages = (page_t*)&__end;
	unsigned int remaining = page_array_size;
	unsigned int * pages_temp = pages;
	while (remaining--){
		*pages_temp++ = 0;
	}
	int i;
	for (i = 0; i < page_count; i++){
		if (i < ((unsigned int)&__end) / 4096){
			pages[i].allocated = 1;
			pages[i].kernel = 1;
		} else {
			pages[i].allocated = 0;
			pages[i].kernel = 0;
			page_list_append(free_pages, &pages[i]);
		}
	}
	
}
