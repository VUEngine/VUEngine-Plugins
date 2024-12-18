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

extern uint32 FlagSpainTiles[];
extern uint16 FlagSpainMap[];


//=========================================================================================================
// DEFINITIONS
//=========================================================================================================

CharSetROMSpec FlagSpainCharset =
{
	// number of chars in function of the number of frames to load at the same time

	4,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	FlagSpainTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec FlagSpainTexture =
{
	// charset spec
	(CharSetSpec*)&FlagSpainCharset,

	// bgmap spec
	FlagSpainMap,

	// cols (max 64)
	5,

	// rows (max 64)
	4,

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

BgmapSpriteROMSpec FlagSpainSpriteSpec =
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
		(TextureSpec*)&FlagSpainTexture,

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

@COMP_ARRAY_START:FlagSpainSpriteSpecs
	&FlagSpainSpriteSpec,
	
@COMP_ARRAY_END:FlagSpainSpriteSpecs

ComponentSpec** FlagSpainEntitySpecComponentSpecs[] = 
{
	@COMPONENTS:FlagSpainEntitySpec@
};

EntityROMSpec FlagSpainEntitySpec =
{
	// class allocator
	__TYPE(Entity),

	// children
	NULL,

	@BEHAVIORS:NULL@,

	// extra
	NULL,

	@SPRITES:(SpriteSpec**)FlagSpainSpriteSpecs@,

	// use z displacement in projection
	false,

	@WIREFRAMES:(WireframeSpec**)NULL@,

	@COLLIDERS:NULL@,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNone,

	@PHYSICS:NULL@,
};
