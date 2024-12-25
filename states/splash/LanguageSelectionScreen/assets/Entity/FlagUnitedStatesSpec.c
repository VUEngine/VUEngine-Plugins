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

extern uint32 FlagUnitedStatesTiles[];
extern uint16 FlagUnitedStatesMap[];


//=========================================================================================================
// DEFINITIONS
//=========================================================================================================

CharSetROMSpec FlagUnitedStatesCharset =
{
	// Number of chars in function of the number of frames to load at the same time

	13,

	// Whether it is shared or not
	true,
	
	// Whether the tiles are optimized or not
	false,

	// Tiles array
	FlagUnitedStatesTiles,

	// Frame offsets array
	NULL,
};

TextureROMSpec FlagUnitedStatesTexture =
{
	// Pointer to the char spec that the texture uses
	(CharSetSpec*)&FlagUnitedStatesCharset,

	// Pointer to the map array that defines how to use the tiles from the char set
	FlagUnitedStatesMap,

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

BgmapSpriteROMSpec FlagUnitedStatesSpriteSpec =
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
		(TextureSpec*)&FlagUnitedStatesTexture,

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

ComponentSpec* const FlagUnitedStatesEntityComponentSpecs[] = 
{
	(ComponentSpec*)&FlagUnitedStatesSpriteSpec,
	NULL
};

EntityROMSpec FlagUnitedStatesEntitySpec =
{
	// Class allocator	
	__TYPE(Entity),

	// Component specs
	(ComponentSpec**)FlagUnitedStatesEntityComponentSpecs,

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
