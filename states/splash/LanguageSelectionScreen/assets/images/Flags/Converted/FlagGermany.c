//---------------------------------------------------------------------------------------------------------
//
//  FlagGermany
//  • 40×32 pixels
//  • 8 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 5×4 map, not compressed
//  Size: 132 + 40 = 172
//
//---------------------------------------------------------------------------------------------------------

const uint32 FlagGermanyTiles[33] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x55540000,0x00040004,0x00040004,0x00000000,0x55550000,0x00000000,
    0x00000000,0x00040004,0x00040004,0xAAA4AAA4,0xAAA4AAA4,0x00000000,0x00000000,0xAAAAAAAA,
    0xAAAAAAAA,0xAAA4AAA4,0xAAA4AAA4,0xFFF4FFF4,0xFFF4FFF4,0xAAAAAAAA,0xAAAAAAAA,0xFFFFFFFF,
    0xFFFFFFFF,0xFFF4FFF4,0xFFF4FFF4,0x00005554,0x00000000,0xFFFFFFFF,0xFFFFFFFF,0x00005555,
    0x00000000,
};

const uint16 FlagGermanyMap[20] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0001,0x0001,0x2000,0x0002,0x0003,0x0003,
    0x0003,0x2002,0x0004,0x0005,0x0005,0x0005,0x2004,0x0006,
    0x0007,0x0007,0x0007,0x2006,
};
