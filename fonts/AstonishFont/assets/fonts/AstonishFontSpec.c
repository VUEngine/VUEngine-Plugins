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

extern BYTE AstonishFontTiles[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec ASTONISH_FONT_CH =
{
	// number of chars
	256,

	// allocation type
	__NOT_ANIMATED,

	// char spec
	AstonishFontTiles,
};

FontROMSpec ASTONISH_FONT =
{
	// font charset spec pointer
	(CharSetSpec*)&ASTONISH_FONT_CH,

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