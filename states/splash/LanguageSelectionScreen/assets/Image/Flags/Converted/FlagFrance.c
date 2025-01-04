
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//
//	FlagFrance
//	* 10 tiles, reduced by non-unique and flipped tiles, not compressed
//	* 5x4 map, not compressed
//	Size: 164 + 40 = 204 byte
//

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const uint32 FlagFranceTiles[] __attribute__((aligned(4))) =
{
	0x00000000,
	0x00000000,0x55540000,0x55545554,0x55545554,0x00000000,0x55550000,0xF555F555,0xF555F555,
	0x00000000,0x55550000,0xFFFFFFFF,0xFFFFFFFF,0x00000000,0x55550000,0xAAAFAAAF,0xAAAFAAAF,
	0x00000000,0x15550000,0x1AAA1AAA,0x1AAA1AAA,0x55545554,0x55545554,0x55545554,0x55545554,
	0xF555F555,0xF555F555,0xF555F555,0xF555F555,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
	0xAAAFAAAF,0xAAAFAAAF,0xAAAFAAAF,0xAAAFAAAF,0x1AAA1AAA,0x1AAA1AAA,0x1AAA1AAA,0x1AAA1AAA,
};

const uint16 FlagFranceMap[] __attribute__((aligned(4))) =
{
	0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
	0x0008,0x0009,0x0005,0x0006,0x0007,0x0008,0x0009,0x1000,
	0x1001,0x3002,0x1003,0x1004,
};
