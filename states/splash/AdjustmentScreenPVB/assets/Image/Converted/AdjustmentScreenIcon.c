
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

//
//	AdjustmentScreenIcon
//	* 4 tiles, reduced by non-unique and flipped tiles, not compressed
//	* 2x2 map, not compressed
//	Size: 68 + 8 = 76 byte
//

//——————————————————————————————————————————————————————————————————————————————————————————————————————————


const uint32 AdjustmentScreenIconTiles[] __attribute__((aligned(4))) =
{
	0x00000000,
	0xAFEBFFFC,0xAFEBAFEB,0xABABAFEB,0xEBAFEBAF,0xFAAB3FFF,0xEAABEAAB,0xEBEBEBEB,0xFAABEBEB,
	0xEAAFEBAF,0xFABFFABF,0xFEFFFABF,0xFFFCFEFF,0xEBEBEAAB,0xEBEBEBEB,0xEAABEAAB,0x3FFFFAAB,
};

const uint16 AdjustmentScreenIconMap[] __attribute__((aligned(4))) =
{
	0x0000,0x0001,0x0002,0x0003,
};
