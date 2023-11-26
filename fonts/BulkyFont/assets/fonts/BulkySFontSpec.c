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

extern uint32 BulkyFontShadowTiles[];


//---------------------------------------------------------------------------------------------------------
//                                               DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec BulkySFontCharSet =
{
	// number of chars
	256,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	BulkyFontShadowTiles,

	// pointer to the frames offsets
	NULL,
};

FontROMSpec BulkySFont =
{
	// font charset spec pointer
	(CharSetSpec*)&BulkySFontCharSet,

	// character number at which the font starts, allows you to skip the control characters for example
	32,

	// number of characters in this font
	64,

	// number of characters per line in charset
	16,

	// size of a single character (in chars) ({width, height})
	{2, 2},

	// font's name
	"BulkyS",
};