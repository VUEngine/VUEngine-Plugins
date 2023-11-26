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

extern uint32 IndustrialFontTiles[];


//---------------------------------------------------------------------------------------------------------
//                                               DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec IndustrialFontCharSet =
{
	// number of chars
	128,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	IndustrialFontTiles,

	// pointer to the frames offsets
	NULL,
};

FontROMSpec IndustrialFont =
{
	// font charset spec pointer
	(CharSetSpec*)&IndustrialFontCharSet,

	// character number at which the font starts, allows you to skip the control characters for example
	0,

	// number of characters in this font
	128,

	// number of characters per line in charset
	32,

	// size of a single character (in chars) ({width, height})
	{1, 1},

	// font's name
	"Industrial",
};