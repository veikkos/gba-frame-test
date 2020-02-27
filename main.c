#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 160

#define MEM_IO   0x04000000
#define MEM_PAL  0x05000000
#define MEM_VRAM 0x06000000
#define MEM_OAM  0x07000000

#define REG_DISPLAY        (*((volatile uint32 *)(MEM_IO)))
#define REG_DISPLAY_VCOUNT (*((volatile uint32 *)(MEM_IO + 0x0006)))

#define OBJECT_ATTR0_Y_MASK 0x0FF
#define OBJECT_ATTR1_X_MASK 0x1FF

#define NUMBER_OF_BLOCKS (SCREEN_HEIGHT / 32)

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef uint16 rgb15;
typedef struct obj_attrs {
  uint16 attr0;
  uint16 attr1;
  uint16 attr2;
  uint16 pad;
} __attribute__((packed, aligned(4))) obj_attrs;
typedef uint32    tile_4bpp[8];
typedef tile_4bpp tile_block[512];

#define oam_mem            ((volatile obj_attrs *)MEM_OAM)
#define tile_mem           ((volatile tile_block *)MEM_VRAM)
#define object_palette_mem ((volatile rgb15 *)(MEM_PAL + 0x200))

static inline rgb15 RGB15(int r, int g, int b)
{
  return r | (g << 5) | (b << 10);
}

static inline void set_object_position(volatile obj_attrs *object, int x,
                                       int y)
{
  object->attr0 = (object->attr0 & ~OBJECT_ATTR0_Y_MASK) |
    (y & OBJECT_ATTR0_Y_MASK);
  object->attr1 = (object->attr1 & ~OBJECT_ATTR1_X_MASK) |
    (x & OBJECT_ATTR1_X_MASK);
}

int main(void)
{
  volatile uint16 *paddle_tile_mem = (uint16 *)tile_mem[4][1];
  for (int i = 0; i < 4 * (sizeof(tile_4bpp) / 2); ++i)
    paddle_tile_mem[i] = 0x1111;

  object_palette_mem[1] = RGB15(0x1F, 0x1F, 0x1F);

  for (int i = 0; i < NUMBER_OF_BLOCKS; ++i) {
    volatile obj_attrs *paddle_attrs = &oam_mem[i];
    paddle_attrs->attr0 = 0x8000;
    paddle_attrs->attr1 = 0x4000;
    paddle_attrs->attr2 = 1;
  }

  REG_DISPLAY = 0x1000 | 0x0040;

  while (1) {
    while(REG_DISPLAY_VCOUNT >= 160);
    while(REG_DISPLAY_VCOUNT <  160);

    static int horizontal_offset = 0;

    for (int i = 0; i < NUMBER_OF_BLOCKS; ++i) {
      volatile obj_attrs *paddle_attrs = &oam_mem[i];
      set_object_position(paddle_attrs, horizontal_offset % SCREEN_WIDTH, i * 32);
    }

    horizontal_offset += 8;
  }

  return 0;
}
