//======================================================================
//
//	FlagSpain, 40x32@2, 
//	+ 4 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 5x4 
//	Total size: 64 + 40 = 104
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const uint32 FlagSpainTiles[16] __attribute__((aligned(4)))=
{
	0x00000000,0x55540000,0xAAA4AAA4,0xAAA4AAA4,
	0x00000000,0x55550000,0xAAAAAAAA,0xAAAAAAAA,0xAAA4AAA4,0xFFF4FFF4,0xFFF4FFF4,0xFFF4FFF4,
	0xAAAAAAAA,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
};

const uint16 FlagSpainMap[20] __attribute__((aligned(4)))=
{
	0x0000,0x0001,0x0001,0x0001,0x2000,0x0002,0x0003,0x0003,
	0x0003,0x2002,0x1002,0x3003,0x3003,0x3003,0x3002,0x1000,
	0x3001,0x3001,0x3001,0x3000,
};
