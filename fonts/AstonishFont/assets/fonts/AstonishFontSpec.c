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

extern uint32 AstonishFontTiles[];


//---------------------------------------------------------------------------------------------------------
//                                               DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec AstonishFontCharSet =
{
	// number of chars
	256,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	AstonishFontTiles,

	// pointer to the frames offsets
	NULL,
};

FontROMSpec AstonishFont =
{
	// font charset spec pointer
	(CharSetSpec*)&AstonishFontCharSet,

	// character number at which the font starts, allows you to skip the control characters for example
	0,

	// number of characters in this font
	128,

	// number of characters per line in charset
	32,

	// size of a single character (in chars) ({width, height})
	{1, 2},

	// font's name
	"Astonish",
};