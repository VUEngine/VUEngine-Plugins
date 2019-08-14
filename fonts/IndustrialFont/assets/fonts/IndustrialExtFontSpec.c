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

extern BYTE IndustrialFontTiles[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec INDUSTRIAL_EXT_FONT_CH =
{
	// number of chars
	256,

	// allocation type
	__NOT_ANIMATED,

	// char spec
	IndustrialFontTiles,
};

FontROMSpec INDUSTRIAL_EXT_FONT =
{
	// font charset spec pointer
	(CharSetSpec*)&INDUSTRIAL_EXT_FONT_CH,

	// character number at which the font starts, allows you to skip the control characters for example
	0,

	// number of characters in this font
	256,

	// size of a single character (in chars) ({width, height})
	{1, 1},

	// font's name
	"IndustrialExt",
};