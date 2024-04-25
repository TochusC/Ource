void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);

void draw_char(unsigned char *vram, int xsize, unsigned char c, int color, int x, int y, int font_size);
void draw_word(unsigned char *vram, char *word, int xsize, unsigned char color, int x, int y, int font_size);

#define COL8_000000		0
#define COL8_FF0000		1
#define COL8_00FF00		2
#define COL8_FFFF00		3
#define COL8_0000FF		4
#define COL8_FF00FF		5
#define COL8_00FFFF		6
#define COL8_FFFFFF		7
#define COL8_C6C6C6		8
#define COL8_840000		9
#define COL8_008400		10
#define COL8_848400		11
#define COL8_000084		12
#define COL8_840084		13
#define COL8_008484		14
#define COL8_848484		15

void HariMain(void)
{
    char *vram;
    int xsize, ysize;

    vram = (char *) 0xa0000;
    xsize = 320;
    ysize = 200;

	init_palette(); /* �p���b�g��ݒ� */

    boxfill8(vram, xsize, COL8_008484,  0,         0,          xsize -  1, ysize - 29);
    boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 28, xsize -  1, ysize - 28);
    boxfill8(vram, xsize, COL8_FFFFFF,  0,         ysize - 27, xsize -  1, ysize - 27);
    boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 26, xsize -  1, ysize -  1);

    boxfill8(vram, xsize, COL8_FFFFFF,  3,         ysize - 24, 59,         ysize - 24);
    boxfill8(vram, xsize, COL8_FFFFFF,  2,         ysize - 24,  2,         ysize -  4);
    boxfill8(vram, xsize, COL8_848484,  3,         ysize -  4, 59,         ysize -  4);
    boxfill8(vram, xsize, COL8_848484, 59,         ysize - 23, 59,         ysize -  5);
    boxfill8(vram, xsize, COL8_000000,  2,         ysize -  3, 59,         ysize -  3);
    boxfill8(vram, xsize, COL8_000000, 60,         ysize - 24, 60,         ysize -  3);

    boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
    boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
    boxfill8(vram, xsize, COL8_FFFFFF, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
    boxfill8(vram, xsize, COL8_FFFFFF, xsize -  3, ysize - 24, xsize -  3, ysize -  3);

    draw_word(vram, "WELCOME TO OURSE", 320, COL8_FF0000,  20,  20, 3);
    draw_word(vram,  "WELCOME TO OURSE", 320, COL8_00FF00,  120,  60, 2);
    draw_word(vram,  "WELCOME TO OURSE", 320, COL8_0000FF, 10,  90, 2);

    for (;;) {
		io_hlt();
	}
}

void init_palette(void)
{
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,	/*  0:�� */
		0xff, 0x00, 0x00,	/*  1:���邢�� */
		0x00, 0xff, 0x00,	/*  2:���邢�� */
		0xff, 0xff, 0x00,	/*  3:���邢���F */
		0x00, 0x00, 0xff,	/*  4:���邢�� */
		0xff, 0x00, 0xff,	/*  5:���邢�� */
		0x00, 0xff, 0xff,	/*  6:���邢���F */
		0xff, 0xff, 0xff,	/*  7:�� */
		0xc6, 0xc6, 0xc6,	/*  8:���邢�D�F */
		0x84, 0x00, 0x00,	/*  9:�Â��� */
		0x00, 0x84, 0x00,	/* 10:�Â��� */
		0x84, 0x84, 0x00,	/* 11:�Â����F */
		0x00, 0x00, 0x84,	/* 12:�Â��� */
		0x84, 0x00, 0x84,	/* 13:�Â��� */
		0x00, 0x84, 0x84,	/* 14:�Â����F */
		0x84, 0x84, 0x84	/* 15:�Â��D�F */
	};
	set_palette(0, 15, table_rgb);
	return;

	/* static char ���߂́A�f�[�^�ɂ����g���Ȃ�����DB���ߑ��� */
}

void set_palette(int start, int end, unsigned char *rgb)
{
	int i, eflags;
	eflags = io_load_eflags();	/* ���荞�݋��t���O�̒l���L�^���� */
	io_cli(); 					/* ���t���O��0�ɂ��Ċ��荞�݋֎~�ɂ��� */
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++) {
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	io_store_eflags(eflags);	/* ���荞�݋��t���O�����ɖ߂� */
	return;
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
	int x, y;
	for (y = y0; y <= y1; y++) {
		for (x = x0; x <= x1; x++)
			vram[y * xsize + x] = c;
	}
	return;
}

const unsigned char font_data_array[26][5][7] = {
        // A
        {
                {0, 1, 1, 0, 0},
                {1, 0, 0, 1, 0},
                {1, 1, 1, 1, 0},
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0}
        },
        // B
        {
                {1, 1, 1, 0, 0},
                {1, 0, 0, 1, 0},
                {1, 1, 1, 0, 0},
                {1, 0, 0, 1, 0},
                {1, 1, 1, 0, 0}
        },
        // C
        {
                {0, 1, 1, 0, 0},
                {1, 0, 0, 1, 0},
                {1, 0, 0, 0, 0},
                {1, 0, 0, 1, 0},
                {0, 1, 1, 0, 0}
        },
        // D
        {
                {1, 1, 0, 0, 0},
                {1, 0, 1, 0, 0},
                {1, 0, 0, 1, 0},
                {1, 0, 1, 0, 0},
                {1, 1, 0, 0, 0}
        },
        // E
        {
                {1, 1, 1, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 1, 1, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 1, 1, 0, 0}
        },
        // F
        {
                {1, 1, 1, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 1, 1, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 0, 0, 0, 0}
        },
        // G
        {
                {0, 1, 1, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 0, 1, 1, 0},
                {1, 0, 0, 1, 0},
                {0, 1, 1, 0, 0}
        },
        // H
        {
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0},
                {1, 1, 1, 1, 0},
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0}
        },
        // I
        {
                {0, 1, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 1, 1, 0, 0}
        },
        // J
        {
                {0, 0, 1, 1, 0},
                {0, 0, 0, 1, 0},
                {0, 0, 0, 1, 0},
                {1, 0, 0, 1, 0},
                {0, 1, 1, 0, 0}
        },
        // K
        {
                {1, 0, 0, 1, 0},
                {1, 0, 1, 0, 0},
                {1, 1, 0, 0, 0},
                {1, 0, 1, 0, 0},
                {1, 0, 0, 1, 0}
        },
        // L
        {
                {1, 0, 0, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 1, 1, 0, 0}
        },
        // M
        {
                {1, 0, 0, 0, 1},
                {1, 1, 0, 1, 1},
                {1, 0, 1, 0, 1},
                {1, 0, 0, 0, 1},
                {1, 0, 0, 0, 1}
        },
        // N
        {
                {1, 0, 0, 1, 0},
                {1, 1, 0, 1, 0},
                {1, 0, 1, 1, 0},
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0}
        },
        // O
        {
                {0, 1, 1, 0, 0},
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0},
                {0, 1, 1, 0, 0}
        },
        // P
        {
                {1, 1, 1, 0, 0},
                {1, 0, 0, 1, 0},
                {1, 1, 1, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 0, 0, 0, 0}
        },
        // Q
        {
                {0, 1, 1, 0, 0},
                {1, 0, 0, 1, 0},
                {1, 0, 1, 1, 0},
                {1, 0, 0, 1, 0},
                {0, 1, 1, 1, 0}
        },
        // R
        {
                {1, 1, 1, 0, 0},
                {1, 0, 0, 1, 0},
                {1, 1, 1, 0, 0},
                {1, 0, 1, 0, 0},
                {1, 0, 0, 1, 0}
        },
        // S
        {
                {0, 1, 1, 1, 0},
                {1, 0, 0, 0, 0},
                {0, 1, 1, 0, 0},
                {0, 0, 0, 1, 0},
                {1, 1, 1, 0, 0}
        },
        // T
        {
                {1, 1, 1, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0}
        },
        // U
        {
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0},
                {0, 1, 1, 0, 0}
        },
        // V
        {
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0},
                {0, 1, 0, 1, 0},
                {0, 0, 1, 0, 0}
        },
        // W
        {
                {1, 0, 0, 0, 1},
                {1, 0, 1, 0, 1},
                {1, 0, 1, 0, 1},
                {0, 1, 0, 1, 0},
                {0, 1, 0, 1, 0}
        },
        // X
        {
                {1, 0, 0, 1, 0},
                {1, 0, 1, 0, 0},
                {0, 1, 0, 1, 0},
                {1, 0, 1, 0, 0},
                {1, 0, 0, 1, 0}
        },
        // Y
        {
                {1, 0, 0, 1, 0},
                {1, 0, 0, 1, 0},
                {0, 1, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0}
        },
        // Z
        {
                {1, 1, 1, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 1, 0, 0, 0},
                {1, 0, 0, 1, 0},
                {1, 1, 1, 1, 0}
        }
};


void draw_char(unsigned char *vram, int xsize, unsigned char c, int color, int x, int y, int font_size) {
    int char_index = c - 'A';

    char *font_data = font_data_array[char_index];

    int i, j;
    for (j = 0; j < 7; j++) {
        for ( i= 0; i < 5; i++) {
            if (font_data[i * 7 + j] == 1) {
                boxfill8(vram, xsize, color, x + j * font_size, y + i * font_size, x + j * font_size + font_size, y + i * font_size + font_size);
            }
        }
    }
}

void draw_word(unsigned char *vram, char *word, int xsize, unsigned char color, int x, int y, int font_size) {
    int i = 0;
    while (word[i] != '\0') {
        if (word[i] == ' ') {
            i++;
            continue;
        }
        draw_char(vram, xsize, word[i], color, x + i * 6 * font_size, y, font_size);
        i++;
    }
}
