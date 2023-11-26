///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                              THIS FILE WAS AUTO-GENERATED - DO NOT EDIT                               //
///////////////////////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------------------------------
//                                                INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Printing.h>


//---------------------------------------------------------------------------------------------------------
//                                              DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 VirtualBoyFontTiles[];


//---------------------------------------------------------------------------------------------------------
//                                               DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec VirtualBoyFontCharSet =
{
	// number of chars
	576,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	VirtualBoyFontTiles,

	// pointer to the frames offsets
	NULL,
};

FontROMSpec VirtualBoyFont =
{
	// font charset spec pointer
	(CharSetSpec*)&VirtualBoyFontCharSet,

	// character number at which the font starts, allows you to skip the control characters for example
	32,

	// number of characters in this font
	96,

	// number of characters per line in charset
	16,

	// size of a single character (in chars) ({width, height})
	{2, 3},

	// font's name
	"VirtualBoy",
};