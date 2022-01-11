#include "io.h"
#include "mailbox.h"
#include "font.h"

unsigned int width, height, pitch;
unsigned char *fb;

void initialise_fb(){
 int length = 0;
 int ptr = 2;
 /*
 
 mailbox[0] = 35*4;
 mailbox[1] = MBTAG_EDGE;
 
 unsigned int whloc = add_setwh(1920, 1080, &ptr);
 add_setvwh(1920, 1080, &ptr);
 add_setvoffset(0, 0, &ptr);
 add_setdepth(32, &ptr);
 add_setpixelorder(&ptr);
 unsigned int fbstart = add_getfb(&ptr);
 uart_putc((fbstart & 0xF0000000 >> 28) + 48);
 uart_putc((fbstart & 0x0F000000 >> 24) + 48);
 uart_putc((fbstart & 0x00F00000 >> 20) + 48);
 uart_putc((fbstart & 0x000F0000 >> 16) + 48);
 uart_putc((fbstart & 0x0000F000 >> 12) + 48);
 uart_putc((fbstart & 0x00000F00 >> 8) + 48);
 uart_putc((fbstart & 0x000000F0 >> 4) + 48);
 uart_putc((fbstart & 0x0000000F >> 0) + 48);
 unsigned int pitchloc = add_getpitch(&ptr);
 
 mailbox[ptr] = MBTAG_EDGE;*/
 mailbox[0] = 35*4; // Length of message in bytes
    mailbox[1] = MBTAG_EDGE;

    mailbox[2] = MBTAG_SETWH; // Tag identifier
    mailbox[3] = 8; // Value size in bytes
    mailbox[4] = 0;
    mailbox[5] = 1920; // Value(width)
    mailbox[6] = 1080; // Value(height)

    mailbox[7] = MBTAG_SETVWH;
    mailbox[8] = 8;
    mailbox[9] = 8;
    mailbox[10] = 1920;
    mailbox[11] = 1080;

    mailbox[12] = MBTAG_SETVOFFSET;
    mailbox[13] = 8;
    mailbox[14] = 8;
    mailbox[15] = 0; // Value(x)
    mailbox[16] = 0; // Value(y)

    mailbox[17] = MBTAG_SETDEPTH;
    mailbox[18] = 4;
    mailbox[19] = 4;
    mailbox[20] = 32; // Bits per pixel

    mailbox[21] = MBTAG_SETPIXELORDER;
    mailbox[22] = 4;
    mailbox[23] = 4;
    mailbox[24] = 1; // RGB

    mailbox[25] = MBTAG_GETFB;
    mailbox[26] = 8;
    mailbox[27] = 8;
    mailbox[28] = 4096; // FrameBufferInfo.pointer
    mailbox[29] = 0;    // FrameBufferInfo.size

    mailbox[30] = MBTAG_GETPITCH;
    mailbox[31] = 4;
    mailbox[32] = 4;
    mailbox[33] = 0; // Bytes per line

    mailbox[34] = MBTAG_EDGE;
 
 if (mailbox_call(8) && mailbox[28] != 0 && mailbox[20] == 32){
 	uart_puts("initialise_fb success");
 	
 	width = mailbox[10];
 	height = mailbox[11];
 	pitch = mailbox[33];
 	
 	mailbox[28] &= 0x3FFFFFFF;
 	fb = (unsigned char *)((long)mailbox[28]);
 	
 	uart_puts("Pitch: ");
 	uart_putnum(pitch);
 }
 else{uart_puts("initialise_fb failed");}

}

void pixel(int x, int y, unsigned int col){
 int addr = y * pitch + x * 4;
 *((unsigned int*)(fb + addr)) = col;
}

void drawChar(unsigned char c, int x, int y, unsigned int col, unsigned int bgcol){
	for (int row = 0; row < 8; row ++){
		for (int column = 0; column < 8; column++){
			if ((font[c][row] >> column) & 0x1){pixel(x + column, y + row, col);
			} else {
				pixel(x + column, y + row, bgcol);
			}
		}
	}
}
void drawString(unsigned char *s, int x, int y, unsigned int col, unsigned int bgcol){
	int offset = 0;
	for (int i = 0; s[i] != '\0'; i++){
		switch (s[i]){
		case '\n':
			y += 8;
		case '\r':
			offset = 0;
			break;
		default:
			drawChar(s[i], x + offset++ * 8, y, col, bgcol);
			break;
		}
	}
}
