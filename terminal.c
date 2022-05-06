#include "graphics.h"
#include "gameoflife.h"
#include <stdbool.h>
#include "io.h"

void terminal_putc(char c);

int terminalWidth;
int terminalHeight;
unsigned char terminalData[200];
int chars;
int currRow;
int currCol;



bool strcmp(unsigned char *s1, unsigned char *s2){
	int i = 0;
	bool mismatch = false;
	while (!mismatch){
		if (s1[i] == '\0' & s2[i] == '\0') return true;
		mismatch = !(s1[i] == s2[i]);
	}
	return false;
}

void terminal_write_line(unsigned char *s){
	drawString(s, 0, currRow++ * 8, 0xFFFFFF, 0x0);
	currRow = currRow > terminalHeight ? 0 : currRow;
}

void terminal_main(){
	while(true){
		unsigned char letter = uart_getc();
		terminal_putc(letter);
	}
	
}

void terminal_init(){
	terminalWidth = (int)(width / 8);
	terminalHeight = (int)(height / 8);
	//char terminalData[terminalHeight + 1][terminalWidth + 1] = {0};
	currRow = 0;
	currCol = 0;
	chars = 0;
}
/*
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
}*/
void terminal_execute(unsigned char *cmd){
	if (strcmp(cmd, "life\0")) {
		terminal_write_line("Command recognized. Running...");
		gameoflife();
	}
	else {
		terminal_write_line("Error: command not recognized");
		terminal_write_line(cmd);
	}
}

void terminal_putc(char c){
	if (c == 'p'){
			drawChar(c, currCol++ * 8, currRow * 8, 0xFF0000, 0x0);
			terminal_execute(terminalData);
			drawChar(c, currCol++ * 8, currRow * 8, 0xFF0000, 0x0);
			for (int i = 0; i < 200; i++){
				terminalData[i] = '\0';
			}
			chars = 0;
	} else {
	
			drawChar(c, currCol++ * 8, currRow * 8, 0xFFFFFF, 0x0);
			currCol = currCol > terminalWidth ? 0 : currCol;
			if (currCol == 0) currRow++;
			currRow = currRow > terminalHeight ? 0 : currRow;
			terminalData[chars++] = c;
	}
}



/*
void terminal_draw(){
	int rowsDrawn = 0;
	int ptr = currRow + 2; //loop past buffer row, start on 'first' row
	while (rowsDrawn < termainalHeight){
		drawString(terminalData[ptr], 0, 8 * rowsDrawn++, 0xFFFFFF, 0);
		
	}
}*/
