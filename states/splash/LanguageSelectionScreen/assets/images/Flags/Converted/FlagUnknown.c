//---------------------------------------------------------------------------------------------------------
//
//  FlagUnknown
//  * 6 tiles, reduced by non-unique and flipped tiles, not compressed
//  * 5x4 map, not compressed
//  Size: 100 + 40 = 140
//
//---------------------------------------------------------------------------------------------------------

const uint32 FlagUnknownTiles[25] __attribute__((aligned(4))) =
{
    0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x55540000,0x00040004,0x00040004,
    0x00000000,0x55550000,0x00000000,0x00000000,0x00040004,0x00040004,0x00040004,0x00040004,
    0x00000000,0x00000000,0x0AA00000,0x28002828,0x02800A00,0x02800000,0x00000000,0x00000000,
};

const uint16 FlagUnknownMap[20] __attribute__((aligned(4))) =
{
    0x0001,0x0002,0x0002,0x0002,0x2001,0x0003,0x0000,0x0004,
    0x0000,0x2003,0x0003,0x0000,0x0005,0x0000,0x2003,0x1001,
    0x3002,0x3002,0x3002,0x3001,
};
