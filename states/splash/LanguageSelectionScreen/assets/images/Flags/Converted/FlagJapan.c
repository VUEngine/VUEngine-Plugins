//======================================================================
//
//	FlagJapan, 40x32@2, 
//	+ 5 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 5x4 
//	Total size: 80 + 40 = 120
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const uint32 FlagJapanTiles[20] __attribute__((aligned(4)))=
{
	0x00000000,0x55540000,0xFFF4FFF4,0xFFF4FFF4,
	0x00000000,0x55550000,0xFFFFFFFF,0xFFFFFFFF,0xFFF4FFF4,0xFFF4FFF4,0xFFF4FFF4,0xFFF4FFF4,
	0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xBFFFBFFF,0xFFFFFFFF,0xFAAFFFFF,0xAAAAAAAA,0xAAAAAAAA,
};

const uint16 FlagJapanMap[20] __attribute__((aligned(4)))=
{
	0x0000,0x0001,0x0001,0x0001,0x2000,0x0002,0x0003,0x0004,
	0x2003,0x2002,0x0002,0x1003,0x3004,0x3003,0x2002,0x1000,
	0x3001,0x3001,0x3001,0x3000,
};
