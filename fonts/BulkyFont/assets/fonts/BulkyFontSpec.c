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

extern BYTE BulkyFontTiles[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec BULKY_FONT_CH =
{
	// number of chars
	256,

	// allocation type
	__NOT_ANIMATED,

	// char spec
	BulkyFontTiles,
};

FontROMSpec BULKY_FONT =
{
	// font charset spec pointer
	(CharSetSpec*)&BULKY_FONT_CH,

	// character number at which the font starts, allows you to skip the control characters for example
	32,

	// number of characters in this font
	64,

	// size of a single character (in chars) ({width, height})
	{2, 2},

	// font's name
	"Bulky",
};