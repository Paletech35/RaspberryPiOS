#include "graphics.h"

int terminalWidth;
int terminalHeight;
//extern unsigned char terminalData[][];
int currRow;

extern void terminal_init(){
}
extern void terminal_write_line(unsigned char *s){

}
/*
void terminal_main(){
	terminal_init();
	
}

void terminal_init(){
	terminalWidth = (int)(width / 8);
	terminalHeight = (int)(height / 8);
	char terminalData[terminalHeight + 1][terminalWidth + 1] = {0};
	int currRow = 0;
}

void terminal_newline(){
	if (currRow++ > terminalHeight){
		currRow = 0;
	}
	for (int i = 0; i < terminalWidth; i++) terminalData[currRow][i] = 0;
}

void terminal_write_line(unsigned char *s){
	int offset = 0;
	
	terminal_newline();
	
	for (int i = 0; s[i] != '\0'; i++){
		switch (s[i]){
		case '\n':
			terminal_newline();
		case '\r':
			offset = 0;
			break;
		default:
			terminalData[currRow][offset++] = s[i];
			break;
		}
		if (offset >= terminalWidth) {offset = 0; terminal_newline();}
	}
}

void terminal_draw(){
	int rowsDrawn = 0;
	int ptr = currRow + 2; //loop past buffer row, start on 'first' row
	while (rowsDrawn < termainalHeight){
		drawString(terminalData[ptr], 0, 8 * rowsDrawn++, 0xFFFFFF, 0);
		
	}
}*/
