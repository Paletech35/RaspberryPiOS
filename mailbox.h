extern volatile unsigned int mailbox[36];
unsigned int mailbox_call(unsigned char c);

#define MBTAG_SETWH         0x40003
#define MBTAG_SETVWH        0x48004
#define MBTAG_SETVOFFSET    0x48009
#define MBTAG_SETDEPTH      0x48005
#define MBTAG_SETPIXELORDER 0x48006

#define MBTAG_GETFB    0x40001
#define MBTAG_GETPITCH 0x40008

#define MBTAG_EDGE 0x0
