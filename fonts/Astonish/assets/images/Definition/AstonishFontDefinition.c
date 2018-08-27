/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE AstonishFontTiles[];
extern BYTE AstonishFontShadowTiles[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/**
 * Astonish font
 *
 * @ingroup vuengine-plugins-fonts
 */

/* Regular */

CharSetROMDef ASTONISH_FONT_CH =
{
	// number of chars
	256,

	// allocation type
	__NOT_ANIMATED,

	// char definition
	AstonishFontTiles,
};

FontROMDef ASTONISH_FONT =
{
	// font charset definition pointer
	(CharSetDefinition*)&ASTONISH_FONT_CH,

	// character number at which the font starts, allows you to skip the control characters for example
	0,

	// number of characters in this font
	128,

	// size of a single character (in chars) ({width, height})
	{1, 2},

	// font's name
	"Astonish",
};

CharSetROMDef ASTONISH_EXTENDED_FONT_CH =
{
	// number of chars
	512,

	// allocation type
	__NOT_ANIMATED,

	// char definition
	AstonishFontTiles,
};

FontROMDef ASTONISH_EXTENDED_FONT =
{
	// font charset definition pointer
	(CharSetDefinition*)&ASTONISH_EXTENDED_FONT_CH,

	// character number at which the font starts, allows you to skip the control characters for example
	0,

	// number of characters in this font
	256,

	// size of a single character (in chars) ({width, height})
	{1, 2},

	// font's name
	"AstonishExt",
};

/* With Dropshadow */

CharSetROMDef ASTONISH_FONT_SHADOW_CH =
{
	// number of chars
	256,

	// allocation type
	__NOT_ANIMATED,

	// char definition
	AstonishFontShadowTiles,
};

FontROMDef ASTONISH_FONT_SHADOW =
{
	// font charset definition pointer
	(CharSetDefinition*)&ASTONISH_FONT_SHADOW_CH,

	// character number at which the font starts, allows you to skip the control characters for example
	0,

	// number of characters in this font
	128,

	// size of a single character (in chars) ({width, height})
	{1, 2},

	// font's name
	"AstonishS",
};

CharSetROMDef ASTONISH_EXTENDED_FONT_SHADOW_CH =
{
	// number of chars
	512,

	// allocation type
	__NOT_ANIMATED,

	// char definition
	AstonishFontShadowTiles,
};

FontROMDef ASTONISH_EXTENDED_FONT_SHADOW =
{
	// font charset definition pointer
	(CharSetDefinition*)&ASTONISH_EXTENDED_FONT_SHADOW_CH,

	// character number at which the font starts, allows you to skip the control characters for example
	0,

	// number of characters in this font
	256,

	// size of a single character (in chars) ({width, height})
	{1, 2},

	// font's name
	"AstonishSExt",
};