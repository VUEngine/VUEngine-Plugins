//---------------------------------------------------------------------------------------------------------
//
//  FlagSweden
//  * 6 tiles, reduced by non-unique and flipped tiles, not compressed
//  * 5x4 map, not compressed
//  Size: 100 + 40 = 140
//
//---------------------------------------------------------------------------------------------------------

const uint32 FlagSwedenTiles[25] __attribute__((aligned(4))) =
{
    0x00000000,
    0x00000000,0x55540000,0x55545554,0x55545554,0x00000000,0x55550000,0xA555A555,0xA555A555,
    0x00000000,0x55550000,0x55555555,0x55555555,0x55545554,0x55545554,0x55545554,0xAAA4AAA4,
    0xA555A555,0xA555A555,0xA555A555,0xAAAAAAAA,0x55555555,0x55555555,0x55555555,0xAAAAAAAA,
};

const uint16 FlagSwedenMap[20] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x2001,0x0002,0x2000,0x0003,0x0004,0x2004,
    0x0005,0x2003,0x1003,0x1004,0x3004,0x3005,0x3003,0x1000,
    0x1001,0x3001,0x3002,0x3000,
};