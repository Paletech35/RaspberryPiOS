#include "io.h"

volatile unsigned int __attribute__((aligned(16))) mailbox[36];

unsigned int mailbox_call(unsigned char c){
	unsigned int r = ((unsigned int)((long) &mailbox) &~ 0xF) | (c & 0xF);
	while (mmio_read(MBOX_STATUS) & MBOX_FULL);
	mmio_write(MBOX_WRITE, r);
	while (1) {
        while (mmio_read(MBOX_STATUS) & MBOX_EMPTY);
        if (r == mmio_read(MBOX_READ)) return mailbox[1]==MBOX_RESPONSE;
           
    }
    return 0;
}
