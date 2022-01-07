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

extern uint32 PompousFontShadowTiles[];


//---------------------------------------------------------------------------------------------------------
//                                               DEFINITIONS                                               
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec PompousSFontCharSet =
{
	// number of chars
	256,

	// allocation type
	__NOT_ANIMATED,

	// char spec
	PompousFontShadowTiles,

	// pointer to the frames offsets
	NULL,
};

FontROMSpec PompousSFont =
{
	// font charset spec pointer
	(CharSetSpec*)&PompousSFontCharSet,

	// character number at which the font starts, allows you to skip the control characters for example
	0,

	// number of characters in this font
	128,

	// number of characters per line in charset
	32,

	// size of a single character (in chars) ({width, height})
	{1, 2},

	// font's name
	"PompousS",
};