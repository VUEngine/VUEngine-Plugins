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

extern uint32 AutomaticPauseLogoTiles[];
extern uint16 AutomaticPauseLogoMap[];


//=========================================================================================================
// DEFINITIONS
//=========================================================================================================

CharSetROMSpec AutomaticPauseLogoCharset =
{
	// number of chars in function of the number of frames to load at the same time
	76,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	AutomaticPauseLogoTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec AutomaticPauseLogoTexture =
{
	// charset spec
	(CharSetSpec*)&AutomaticPauseLogoCharset,

	// bgmap spec
	AutomaticPauseLogoMap,

	// cols (max 64)
	15,

	// rows (max 64)
	12,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames
	1,

	// palette number (0-3)
	0,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec AutomaticPauseLogoSpriteSpec =
{
	{
		// Component
		{
			// Allocator
			__TYPE(BgmapSprite),

			// Component type
			kSpriteComponent
		},

		// texture spec
		(TextureSpec*)&AutomaticPauseLogoTexture,

		// transparency (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

const ComponentSpec* AutomaticPauseLogoEntityComponentSpecs[] = 
{
	(ComponentSpec*)&AutomaticPauseLogoSpriteSpec,
	NULL
};

EntityROMSpec AutomaticPauseLogoEntitySpec =
{
	// Class allocator	
	__TYPE(Entity),

	// Component specs
	(ComponentSpec**)AutomaticPauseLogoEntityComponentSpecs,

	// Children specs
	NULL,

	// Extra info
	NULL,

	// Size
	// If 0, it is computed from the visual components if any
	{0, 0, 0},

	// In-game entity's type
	kTypeNone
};
