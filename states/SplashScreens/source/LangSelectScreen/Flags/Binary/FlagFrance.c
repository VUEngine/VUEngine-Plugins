#include <SplashScreensConfig.h>
#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 1)

//{{BLOCK(FlagFrance)

//======================================================================
//
//	FlagFrance, 40x32@2,
//	+ 11 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 5x4
//	Total size: 176 + 40 = 216
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned int FlagFranceTiles[44] __attribute__((aligned(4)))=
{
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x55540000,0x55545554,0x55545554,
	0x00000000,0x55550000,0xF555F555,0xF555F555,0x00000000,0x55550000,0xFFFFFFFF,0xFFFFFFFF,
	0x00000000,0x55550000,0xAAAFAAAF,0xAAAFAAAF,0x00000000,0x15550000,0x1AAA1AAA,0x1AAA1AAA,
	0x55545554,0x55545554,0x55545554,0x55545554,0xF555F555,0xF555F555,0xF555F555,0xF555F555,
	0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xAAAFAAAF,0xAAAFAAAF,0xAAAFAAAF,0xAAAFAAAF,
	0x1AAA1AAA,0x1AAA1AAA,0x1AAA1AAA,0x1AAA1AAA,
};

const unsigned short FlagFranceMap[20] __attribute__((aligned(4)))=
{
	0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,
	0x0009,0x000A,0x0006,0x0007,0x0008,0x0009,0x000A,0x1001,
	0x1002,0x3003,0x1004,0x1005,
};

//}}BLOCK(FlagFrance)

#endif
