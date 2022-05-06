//#include <stdio.h>
//#include <time.h>
//#include <stdlib.h>
#include "kernel.h"
#include "graphics.h"

#define SLEEP delay(30000)
#define CLS clearScreen(0)


#define ROWS 23
#define COLS 80





// Conway's Game of Life, C. github.com/ferrara44
int life;
int fertility;
char world1[COLS][ROWS];
char world2[COLS][ROWS];
char menu;


static unsigned long int next = 1;

int rand(void) // RAND_MAX assumed to be 32767
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}


void seed(){ // Generates the world based on the selected fertility level
	for (int j=0;j<ROWS;j++){
		for(int i=0;i<COLS;i++){
			life=(rand()%10);
			if (life<fertility) world1[i][j]='o';
			else world1[i][j]=' ';
		}
	}
}

void printWorld(char world[COLS][ROWS]){ //Prints the next world on screen
	for (int j = 0; j < ROWS; j++){
		for(int i = 0 ;i < COLS; i++){
			drawChar(world[i][j], 8 * i, 8 * j, 0xFFFFFF, 0);
		}
		//printf("\n");
	}
	
}

void evaluate(int b, int c, char world_a[COLS][ROWS], char world_b[COLS][ROWS]){ // Checks how many living neighbors this tile currently has.
	int neighbors = 0;
	// Iterate through the nine squares around the current cell.
	// ----------------------------------------------
	// |(b - 1, c - 1)|(b + 0, c - 1)|(b + 1, c - 1)|
	// ----------------------------------------------
	// |(b - 1, c + 0)|(b + 0, c + 0)|(b + 1, c + 0)|
	// ----------------------------------------------
	// |(b - 1, c + 1)|(b + 0, c + 1)|(b + 1, c + 1)|
	// ----------------------------------------------
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((i == 0 && j == 0)				// If we're looking at the current cell
				|| b + i >= COLS				// or the cell we're looking at is outside of the world
				|| b + i < 0
				|| c + j >= ROWS
				|| c + j < 0) 
			{
				continue;						// Skip it
			}
			// If the cell is alive, (world_a[b + i][c + j] == 'o') will return 1,
			// otherwise the expression will return 0.
			// You could also write it as:
			if (world_a[b + i][c + j] == 'o') neighbors++;
		}
	}
	
	// Rules of the Game of Life

	// Let x = three neighbors, y = two neighbors, z = alive, and !z = dead.	(definition of variables and not alive == dead)
	// The rules are therefore a cell is alive if and only if
	// (three neighbors and dead) or (alive and (two or three neighbors))		(definition of the rules of Game of Life)
	// (x && !z) || (z && (x || y))												(just rewrote it using variables)
	// == (x && !z) || (x && z) || (y && z)										(distributive property of and/or)
	// == (x && (!z || z)) || (y && z)											(distributive property of and/or)
	// == x || (y && z)															(!z || z) == true and x && true == x
	// == three neighbors || (two neighbors && alive)
	if (neighbors == 3 || (neighbors == 2 && world_a[b][c] == 'o')) {
		world_b[b][c] = 'o';
	} else {
		world_b[b][c] = ' ';
	}
}

void step(char world_a[COLS][ROWS], char world_b[COLS][ROWS]){ // Iterates through every tile.
	for (int j = 0; j < ROWS; j++){
		for (int i = 0; i < COLS; i++){
			evaluate(i, j, world_a, world_b);
		}
	}
}

int gameoflife(){

	drawString("game of life booting", 0, 0, 0xFFFFFF, 0x0);
	delay(100000);
	

	fertility = 4;
	
	char buffer[100] = "";
	
	
	seed();
	printWorld(world1);
	CLS;

	int turn = 0;
	int generation;
	
	for(generation = 0; generation < 300; generation++) {
		SLEEP;
		CLS;
		if (turn == 0){
			step(world1, world2);
			printWorld(world2);
			turn = 1;
		} else if (turn == 1){
			step(world2, world1);
			printWorld(world1);
			turn = 0;
		}
		SLEEP;
	}
}

