/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <Entity.h>
#include <VIPManager.h>
#include <BgmapSprite.h>


//=========================================================================================================
// DECLARATIONS
//=========================================================================================================

extern uint32 FlagItalyTiles[];
extern uint16 FlagItalyMap[];


//=========================================================================================================
// DEFINITIONS
//=========================================================================================================

CharSetROMSpec FlagItalyCharset =
{
	// Number of chars in function of the number of frames to load at the same time

	10,

	// Whether it is shared or not
	true,
	
	// Whether the tiles are optimized or not
	false,

	// Tiles array
	FlagItalyTiles,

	// Frame offsets array
	NULL,
};

TextureROMSpec FlagItalyTexture =
{
	// Pointer to the char spec that the texture uses
	(CharSetSpec*)&FlagItalyCharset,

	// Pointer to the map array that defines how to use the tiles from the char set
	FlagItalyMap,

	// Horizontal size in tiles of the texture (max. 64)
	5,

	// Vertical size in tiles of the texture (max. 64)
	4,

	// Padding added to the size for affine/hbias transformations (cols, rows)
	{0, 0},

	// Number of frames that the texture supports
	1,

	// Palette index to use by the graphical data (0 - 3)
	0,

	// Flag to recyble the texture with a different map
	false,

	// Flag to vertically flip the image
	false,

	// Flag to horizontally flip the image
	false,
};

BgmapSpriteROMSpec FlagItalySpriteSpec =
{
	{
		// Component
		{
			// Allocator
			__TYPE(BgmapSprite),

			// Component type
			kSpriteComponent
		},

		// Spec for the texture to display
		(TextureSpec*)&FlagItalyTexture,

		// Transparency mode (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// Displacement
		{0, 0, 0, 0},
	},

	// The display mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// Pointer to affine/hbias manipulation function
	NULL,

	// Flag to indicate in which display to show the texture (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ComponentSpec* const FlagItalyEntityComponentSpecs[] = 
{
	(ComponentSpec*)&FlagItalySpriteSpec,
	NULL
};

EntityROMSpec FlagItalyEntitySpec =
{
	// Class allocator	
	__TYPE(Entity),

	// Component specs
	(ComponentSpec**)FlagItalyEntityComponentSpecs,

	// Children specs
	NULL,

	// Extra info
	NULL,

	// Size
	// If 0, it is computed from the visual components if any
	{0, 0, 0},

	// Entity's in-game type
	kTypeNone
};
