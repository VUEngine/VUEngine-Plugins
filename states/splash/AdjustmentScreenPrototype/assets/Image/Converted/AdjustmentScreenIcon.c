//---------------------------------------------------------------------------------------------------------
//
//  AdjustmentScreenIcon
//  * 4 tiles, reduced by non-unique and flipped tiles, not compressed
//  * 2x2 map, not compressed
//  Size: 68 + 8 = 76
//
//---------------------------------------------------------------------------------------------------------

const uint32 AdjustmentScreenIconTiles[17] __attribute__((aligned(4))) =
{
    0x00000000,
    0xC3C3FFFC,0xC3C3C3C3,0xC303C3C3,0xC30FC30F,0xF0003FFF,0xC000C000,0xC3C3C3C3,0xF003C003,
    0xC00FC30F,0xC03FC03F,0xC0FFC03F,0xFFFCC0FF,0xC3C3C003,0xC3C3C3C3,0xC000C000,0x3FFFF000,
};

const uint16 AdjustmentScreenIconMap[4] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,
};
