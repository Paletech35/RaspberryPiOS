#include "io.h"
#include "mailbox.h"

unsigned int add_setwh(int width, int height, int *ptr);
void add_setvwh(int width, int height, int *ptr);
void add_setvoffset(int x, int y, int *ptr);
void add_setdepth(int depth, int *ptr);
void add_setpixelorder(int *ptr);
unsigned int add_getfb(int *ptr);
unsigned int add_getpitch(int *ptr);


unsigned int width, height, pitch;
unsigned char *fb;

void initialise_fb(){
 int length = 0;
 int ptr = 2;
 
 mailbox[0] = 35*4;
 mailbox[1] = MBTAG_EDGE;
 
 unsigned int whloc = add_setwh(1920, 1080, &ptr);
 add_setvwh(1920, 1080, &ptr);
 add_setvoffset(0, 0, &ptr);
 add_setdepth(32, &ptr);
 add_setpixelorder(&ptr);
 unsigned int fbstart = add_getfb(&ptr);
 unsigned int pitchloc = add_getpitch(&ptr);
 
 mailbox[ptr] = MBTAG_EDGE;
 
 if (mailbox_call(8) && mailbox[fbstart] != 0 && mailbox[pitchloc] == 32){
 width = mailbox[whloc++];
 height = mailbox[whloc];
 pitch = mailbox[pitchloc];
 mailbox[fbstart] &= 0x3FFFFFFF;
 fb = (unsigned char *)((long)mailbox[fbstart]);
 }

}

void pixel(int x, int y, unsigned char *col){
 int addr = y * pitch + x * 4;
 for (int i = 0; i < 4; i++){
 *((unsigned int*)(fb + addr)) = *(col + i);
 }
}


unsigned int add_setwh(int width, int height, int *ptr){
mailbox[*ptr++] = MBTAG_SETWH;
mailbox[*ptr++] = 8;
mailbox[*ptr++] = 8;
mailbox[*ptr++] = width;
mailbox[*ptr++] = height;
return *ptr - 2;
}

void add_setvwh(int width, int height, int *ptr){
mailbox[*ptr++] = MBTAG_SETVWH;
mailbox[*ptr++] = 8;
mailbox[*ptr++] = 8;
mailbox[*ptr++] = width;
mailbox[*ptr++] = height;
}

void add_setvoffset(int x, int y, int *ptr){
mailbox[*ptr++] = MBTAG_SETVOFFSET;
mailbox[*ptr++] = 8;
mailbox[*ptr++] = 8;
mailbox[*ptr++] = x;
mailbox[*ptr++] = y;
}
void add_setdepth(int depth, int *ptr){
mailbox[*ptr++] = MBTAG_SETDEPTH;
mailbox[*ptr++] = 4;
mailbox[*ptr++] = 4;
mailbox[*ptr++] = depth;
}

void add_setpixelorder(int *ptr){
mailbox[*ptr++] = MBTAG_SETPIXELORDER;
mailbox[*ptr++] = 4;
mailbox[*ptr++] = 4;
mailbox[*ptr++] = 1;
}

unsigned int add_getfb(int *ptr){
mailbox[*ptr++] = MBTAG_GETFB;
mailbox[*ptr++] = 8;
mailbox[*ptr++] = 8;
mailbox[*ptr++] = 4096;
mailbox[*ptr++] = 0;
return *ptr - 2;
}

unsigned int add_getpitch(int *ptr){
mailbox[*ptr++] = MBTAG_GETPITCH;
mailbox[*ptr++] = 4;
mailbox[*ptr++] = 4;
mailbox[*ptr++] = 0;
return *ptr - 1;
}
