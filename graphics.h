void initialise_fb();
void pixel(int x, int y, unsigned int col);
void drawChar(unsigned char c, int x, int y, unsigned int col, unsigned int bgcol);
void drawString(unsigned char *s, int x, int y, unsigned int col, unsigned int bgcol);
void clearScreen(unsigned int col);
void g_putc(void* p, char c);
extern unsigned int width;
extern unsigned int height;
extern unsigned int pitch;
