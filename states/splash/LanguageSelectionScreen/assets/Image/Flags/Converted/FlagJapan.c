//---------------------------------------------------------------------------------------------------------
//
//	FlagJapan
//	* 5 tiles, reduced by non-unique and flipped tiles, not compressed
//	* 5x4 map, not compressed
//	Size: 84 + 40 = 124 byte
//
//---------------------------------------------------------------------------------------------------------

const uint32 FlagJapanTiles[] __attribute__((aligned(4))) =
{
	0x00000000,
	0x00000000,0x55540000,0xFFF4FFF4,0xFFF4FFF4,0x00000000,0x55550000,0xFFFFFFFF,0xFFFFFFFF,
	0xFFF4FFF4,0xFFF4FFF4,0xFFF4FFF4,0xFFF4FFF4,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xBFFFBFFF,
	0xFFFFFFFF,0xFAAFFFFF,0xAAAAAAAA,0xAAAAAAAA,
};

const uint16 FlagJapanMap[] __attribute__((aligned(4))) =
{
	0x0000,0x0001,0x0001,0x0001,0x2000,0x0002,0x0003,0x0004,
	0x2003,0x2002,0x0002,0x1003,0x3004,0x3003,0x2002,0x1000,
	0x3001,0x3001,0x3001,0x3000,
};
