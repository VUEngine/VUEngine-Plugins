
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//
//	AdjustmentScreenIcon
//	* 8 tiles, reduced by non-unique and flipped tiles, not compressed
//	* 3x3 map, not compressed
//	Size: 132 + 18 = 150 byte
//

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const uint32 AdjustmentScreenIconTiles[] __attribute__((aligned(4))) =
{
	0x00000000,
	0x00000000,0x00000000,0xB000C000,0x9B006C00,0x0FF00000,0xAAAB2AAC,0xA55AAAAA,0xAAAA5555,
	0x00000000,0x00000000,0x000A0002,0x00A60029,0x9AB09AC0,0x6AAC9AAC,0xAAACAAAC,0xAA80AAA0,
	0xAAAAAAA5,0x5555A96A,0xA55AA55A,0x5AA59696,0x0AA602A6,0x2AA92AA6,0x2AAA2AAA,0x02AA0AAA,
	0xA8006A00,0x8000A000,0x00000000,0x00000000,0x5AA56AA9,0xAAAA9696,0x2AA8AAAA,0x00000AA0,
};

const uint16 AdjustmentScreenIconMap[] __attribute__((aligned(4))) =
{
	0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
	0x2006,
};
