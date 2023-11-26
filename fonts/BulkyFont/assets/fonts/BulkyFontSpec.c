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

extern uint32 BulkyFontTiles[];


//---------------------------------------------------------------------------------------------------------
//                                               DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec BulkyFontCharSet =
{
	// number of chars
	256,

	// sharing scheme
	kCharSetShared,

	// char spec
	BulkyFontTiles,

	// pointer to the frames offsets
	NULL,
};

FontROMSpec BulkyFont =
{
	// font charset spec pointer
	(CharSetSpec*)&BulkyFontCharSet,

	// character number at which the font starts, allows you to skip the control characters for example
	32,

	// number of characters in this font
	64,

	// number of characters per line in charset
	16,

	// size of a single character (in chars) ({width, height})
	{2, 2},

	// font's name
	"Bulky",
};