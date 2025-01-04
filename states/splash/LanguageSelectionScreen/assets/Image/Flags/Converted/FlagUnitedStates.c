
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//
//	FlagUnitedStates
//	* 13 tiles, reduced by non-unique and flipped tiles, not compressed
//	* 5x4 map, not compressed
//	Size: 212 + 40 = 252 byte
//

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const uint32 FlagUnitedStatesTiles[] __attribute__((aligned(4))) =
{
	0x00000000,
	0x00000000,0x55540000,0xD5D45554,0x5D545554,0x00000000,0x55550000,0xD5D55555,0x5D5D5555,
	0x00000000,0x55550000,0xFFD5AA95,0xAA9DFFD5,0x00000000,0x55550000,0xFFFFAAAA,0xAAAAFFFF,
	0x00000000,0x15550000,0x1FFF1AAA,0x1AAA1FFF,0xD5D45554,0x5D545554,0xD5D45554,0x5D545554,
	0xD5D55555,0x5D5D5555,0xD5D55555,0x5D5D5555,0xFFD5AA95,0xAA9DFFD5,0xFFD5AA95,0xAA9DFFD5,
	0xFFFFAAAA,0xAAAAFFFF,0xFFFFAAAA,0xAAAAFFFF,0x1FFF1AAA,0x1AAA1FFF,0x1FFF1AAA,0x1AAA1FFF,
	0xFFF45554,0xAAA4FFF4,0xFFF4AAA4,0xAAA4FFF4,0xFFFF5555,0xAAAAFFFF,0xFFFFAAAA,0xAAAAFFFF,
	0xFFFFAA95,0xAAAAFFFF,0xFFFFAAAA,0xAAAAFFFF,
};

const uint16 FlagUnitedStatesMap[] __attribute__((aligned(4))) =
{
	0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
	0x0008,0x0009,0x000A,0x000B,0x000C,0x0008,0x0009,0x3004,
	0x3003,0x3003,0x3003,0x1004,
};
