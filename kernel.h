void delay(unsigned int count);

typedef enum{
	NONE = 0x00000000,
	CORE = 0x54410001,
	MEM = 0x54410002,
	VTEXT = 0x54410003,
	RDISK = 0x54410004,
	INITRD2 = 0x54410005,
	SERIAL = 0x54410006,
	REV = 0x54410007,
	VLFB = 0x54410008,
	CMDLINE = 0x54410009,
}atag_data_t;

typedef struct {
    unsigned int flags;
    unsigned int pagesize;
    unsigned int rootdev;
} core_t;

typedef struct {
    unsigned int size;
    unsigned int start;
} mem_t;

typedef struct {
    unsigned char width;
    unsigned char height;
    unsigned short video_page;
    unsigned char video_mode;
    unsigned char video_cols;
    unsigned short video_ega_bx;
    unsigned char video_lines;
    unsigned char video_isvga;
    unsigned short video_points;
} vtext_t;

typedef struct {
    unsigned int flags;
    unsigned int size;
    unsigned int start;
} rdisk_t;

typedef struct {
    unsigned int start;
    unsigned int size;
} initrd2_t;

typedef struct {
    unsigned int low;
    unsigned int high;
} serial_t;

typedef struct {
    unsigned int rev;
} rev_t;

typedef struct {
    unsigned short lfb_width;
    unsigned short lfb_height;
    unsigned short lfb_depth;
    unsigned short lfb_linelength;
    unsigned int lfb_base;
    unsigned int lfb_size;
    unsigned char red_size;
    unsigned char red_pos;
    unsigned char green_size;
    unsigned char green_pos;
    unsigned char blue_size;
    unsigned char blue_pos;
    unsigned char rsvd_size;
    unsigned char rsvd_pos;
} vlfb_t;

typedef struct {
    char cmdline[1];
} cmdline_t;

typedef struct atag {
    unsigned int size;
    atag_data_t tag;
    union {
        core_t core;
        mem_t mem;
        vtext_t vtext;
        rdisk_t rdisk;
        initrd2_t initrd2;
        serial_t serial;
        rev_t rev;
        vlfb_t vlfb;
        cmdline_t cmdline;
    };
} atag_t;
