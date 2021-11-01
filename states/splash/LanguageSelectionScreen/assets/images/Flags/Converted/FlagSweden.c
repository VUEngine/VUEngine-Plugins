//======================================================================
//
//	FlagSweden, 40x32@2, 
//	+ 6 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 5x4 
//	Total size: 96 + 40 = 136
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const uint32 FlagSwedenTiles[24] __attribute__((aligned(4)))=
{
	0x00000000,0x55540000,0x55545554,0x55545554,
	0x00000000,0x55550000,0xA555A555,0xA555A555,0x00000000,0x55550000,0x55555555,0x55555555,
	0x55545554,0x55545554,0x55545554,0xAAA4AAA4,0xA555A555,0xA555A555,0xA555A555,0xAAAAAAAA,
	0x55555555,0x55555555,0x55555555,0xAAAAAAAA,
};

const uint16 FlagSwedenMap[20] __attribute__((aligned(4)))=
{
	0x0000,0x0001,0x2001,0x0002,0x2000,0x0003,0x0004,0x2004,
	0x0005,0x2003,0x1003,0x1004,0x3004,0x3005,0x3003,0x1000,
	0x1001,0x3001,0x3002,0x3000,
};
