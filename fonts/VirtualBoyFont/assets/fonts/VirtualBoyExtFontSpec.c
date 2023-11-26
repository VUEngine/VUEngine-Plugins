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

CharSetROMSpec VirtualBoyExtFontCharSet =
{
	// number of chars
	1344,

	// sharing scheme
	kCharSetShared,

	// char spec
	VirtualBoyFontTiles,

	// pointer to the frames offsets
	NULL,
};

FontROMSpec VirtualBoyExtFont =
{
	// font charset spec pointer
	(CharSetSpec*)&VirtualBoyExtFontCharSet,

	// character number at which the font starts, allows you to skip the control characters for example
	32,

	// number of characters in this font
	224,

	// number of characters per line in charset
	16,

	// size of a single character (in chars) ({width, height})
	{2, 3},

	// font's name
	"VirtualBoyExt",
};