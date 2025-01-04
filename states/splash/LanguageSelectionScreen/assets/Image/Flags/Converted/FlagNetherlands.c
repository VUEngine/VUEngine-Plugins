
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//
//	FlagNetherlands
//	* 8 tiles, reduced by non-unique and flipped tiles, not compressed
//	* 5x4 map, not compressed
//	Size: 132 + 40 = 172 byte
//

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


const uint32 FlagNetherlandsTiles[] __attribute__((aligned(4))) =
{
	0x00000000,
	0x00000000,0x55540000,0xAAA4AAA4,0xAAA4AAA4,0x00000000,0x55550000,0xAAAAAAAA,0xAAAAAAAA,
	0xAAA4AAA4,0xAAA4AAA4,0xFFF4FFF4,0xFFF4FFF4,0xAAAAAAAA,0xAAAAAAAA,0xFFFFFFFF,0xFFFFFFFF,
	0xFFF4FFF4,0xFFF4FFF4,0x55545554,0x55545554,0xFFFFFFFF,0xFFFFFFFF,0x55555555,0x55555555,
	0x55545554,0x55545554,0x00005554,0x00000000,0x55555555,0x55555555,0x00005555,0x00000000,
};

const uint16 FlagNetherlandsMap[] __attribute__((aligned(4))) =
{
	0x0000,0x0001,0x0001,0x0001,0x2000,0x0002,0x0003,0x0003,
	0x0003,0x2002,0x0004,0x0005,0x0005,0x0005,0x2004,0x0006,
	0x0007,0x0007,0x0007,0x2006,
};
