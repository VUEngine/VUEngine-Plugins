///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                              THIS FILE WAS AUTO-GENERATED - DO NOT EDIT                               //
///////////////////////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Printing.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE VirtualBoyFontTiles[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec VIRTUAL_BOY_EXT_FONT_CH =
{
	// number of chars
	1344,

	// allocation type
	__NOT_ANIMATED,

	// char spec
	VirtualBoyFontTiles,
};

FontROMSpec VIRTUAL_BOY_EXT_FONT =
{
	// font charset spec pointer
	(CharSetSpec*)&VIRTUAL_BOY_EXT_FONT_CH,

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