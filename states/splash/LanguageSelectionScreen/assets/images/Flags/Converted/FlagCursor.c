//---------------------------------------------------------------------------------------------------------
//
//  FlagCursor
//  • 40×32 pixels
//  • 4 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 5×4 map, not compressed
//  Size: 68 + 40 = 108
//
//---------------------------------------------------------------------------------------------------------

const uint32 FlagCursorTiles[17] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x0003FFFF,0x00030003,
    0x00030003,0x00000000,0x0000FFFF,0x00000000,0x00000000,0x00030003,0x00030003,0x00030003,
    0x00030003,
};

const uint16 FlagCursorMap[20] __attribute__((aligned(4))) =
{
    0x0001,0x0002,0x0002,0x0002,0x2001,0x0003,0x0000,0x0000,
    0x0000,0x2003,0x0003,0x0000,0x0000,0x0000,0x2003,0x1001,
    0x3002,0x3002,0x3002,0x3001,
};
