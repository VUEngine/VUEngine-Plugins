//======================================================================
//
//	FlagItaly, 40x32@2, 
//	+ 10 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 5x4 
//	Total size: 160 + 40 = 200
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const uint32 FlagItalyTiles[40] __attribute__((aligned(4)))=
{
	0x00000000,0x55540000,0xAAA4AAA4,0xAAA4AAA4,
	0x00000000,0x55550000,0xFAAAFAAA,0xFAAAFAAA,0x00000000,0x55550000,0xFFFFFFFF,0xFFFFFFFF,
	0x00000000,0x55550000,0x555F555F,0x555F555F,0x00000000,0x15550000,0x15551555,0x15551555,
	0xAAA4AAA4,0xAAA4AAA4,0xAAA4AAA4,0xAAA4AAA4,0xFAAAFAAA,0xFAAAFAAA,0xFAAAFAAA,0xFAAAFAAA,
	0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x555F555F,0x555F555F,0x555F555F,0x555F555F,
	0x15551555,0x15551555,0x15551555,0x15551555,
};

const uint16 FlagItalyMap[20] __attribute__((aligned(4)))=
{
	0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
	0x0008,0x0009,0x0005,0x0006,0x0007,0x0008,0x0009,0x1000,
	0x1001,0x3002,0x1003,0x1004,
};