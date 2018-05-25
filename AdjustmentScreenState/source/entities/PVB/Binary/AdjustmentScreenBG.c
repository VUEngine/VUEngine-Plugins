#include <AdjustmentScreenState.h>
#if(__ADJUSTMENT_SCREEN_VARIANT == 1)

//{{BLOCK(AdjustmentScreenBG)

//======================================================================
//
//	AdjustmentScreenBG, 112x112@2,
//	+ 37 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 14x14
//	Total size: 592 + 392 = 984
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned int AdjustmentScreenBGTiles[148] __attribute__((aligned(4)))=
{
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00003000,
	0x00000000,0x00003000,0x00003330,0x00003333,0x00003000,0x00003333,0x00003333,0x00003333,
	0x00003333,0x00003333,0x00003333,0x00003333,0x00000003,0x00003333,0x00003333,0x00003333,
	0x00000000,0x00000003,0x00000333,0x00003333,0x00000000,0x00000000,0x00000000,0x00000003,
	0x00000000,0x00003000,0x00003300,0x00003330,0x00003330,0x00003333,0x00003333,0x00003333,
	0x00000333,0x00003333,0x00003333,0x00003333,0x00000000,0x00000003,0x00000033,0x00000333,
	0x00003000,0x00003300,0x00003300,0x00003330,0x00000003,0x00000033,0x00000033,0x00000333,
	0x00003330,0x00003330,0x00003330,0x00002222,0x00003333,0x00003333,0x00003333,0x00002222,

	0x00000333,0x00000333,0x00000333,0x00002222,0x00002222,0x00002222,0x00002222,0x00002222,
	0x00002222,0x00002220,0x00002220,0x00002220,0x00002222,0x00000222,0x00000222,0x00000222,
	0x00002220,0x00002200,0x00002200,0x00002000,0x00000222,0x00000022,0x00000022,0x00000002,
	0x00002000,0x00000000,0x00000000,0x00000000,0x00002222,0x00003333,0x00003333,0x00003330,
	0x00002222,0x00003333,0x00003333,0x00003333,0x00002222,0x00003333,0x00003333,0x00000333,
	0x00000002,0x00000000,0x00000000,0x00000000,0x00003330,0x00003300,0x00003000,0x00000000,
	0x00000333,0x00000033,0x00000003,0x00000000,0x00003333,0x00003333,0x00003333,0x00003330,
	0x00003333,0x00003333,0x00003333,0x00000333,0x00003000,0x00000000,0x00000000,0x00000000,

	0x00003333,0x00003330,0x00003000,0x00000000,0x00003333,0x00003333,0x00003333,0x00003000,
	0x00003333,0x00003333,0x00003333,0x00000003,0x00003333,0x00000333,0x00000003,0x00000000,
	0x00000003,0x00000000,0x00000000,0x00000000,
};

const unsigned short AdjustmentScreenBGMap[196] __attribute__((aligned(4)))=
{
	0x0000,0x0000,0x0000,0x0001,0x0002,0x0003,0x0004,0x0004,
	0x0005,0x0006,0x0007,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0008,0x0009,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,
	0x000A,0x000B,0x0000,0x0000,0x0000,0x0008,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,
	0x000B,0x0000,0x0001,0x0009,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x000A,0x0007,
	0x000C,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,

	0x0004,0x0004,0x0004,0x0004,0x0004,0x000D,0x000E,0x000F,
	0x000F,0x000F,0x000F,0x000F,0x000F,0x000F,0x000F,0x000F,
	0x000F,0x000F,0x000F,0x0010,0x0011,0x0011,0x0011,0x0011,
	0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,
	0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,
	0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,
	0x0012,0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,
	0x0011,0x0011,0x0011,0x0011,0x0011,0x0013,0x0014,0x0011,

	0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,0x0011,
	0x0011,0x0011,0x0011,0x0015,0x0016,0x0017,0x0018,0x0018,
	0x0018,0x0018,0x0018,0x0018,0x0018,0x0018,0x0018,0x0018,
	0x0019,0x001A,0x0000,0x001B,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x001C,0x0000,
	0x0000,0x0000,0x001B,0x001D,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x001E,0x001C,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x001F,0x0020,0x0021,0x0004,0x0004,0x0022,0x0023,

	0x0024,0x0000,0x0000,0x0000,
};

//}}BLOCK(AdjustmentScreenBG)


#endif
