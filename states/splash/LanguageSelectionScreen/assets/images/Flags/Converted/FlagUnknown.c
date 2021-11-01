//======================================================================
//
//	FlagUnknown, 40x32@2, 
//	+ 6 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 5x4 
//	Total size: 96 + 40 = 136
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const uint32 FlagUnknownTiles[24] __attribute__((aligned(4)))=
{
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x55540000,0x00040004,0x00040004,
	0x00000000,0x55550000,0x00000000,0x00000000,0x00040004,0x00040004,0x00040004,0x00040004,
	0x00000000,0x00000000,0x0AA00000,0x28002828,0x02800A00,0x02800000,0x00000000,0x00000000,
};

const uint16 FlagUnknownMap[20] __attribute__((aligned(4)))=
{
	0x0001,0x0002,0x0002,0x0002,0x2001,0x0003,0x0000,0x0004,
	0x0000,0x2003,0x0003,0x0000,0x0005,0x0000,0x2003,0x1001,
	0x3002,0x3002,0x3002,0x3001,
};
