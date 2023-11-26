/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <VIPManager.h>
#include <BgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 AutomaticPauseLogoTiles[];
extern uint16 AutomaticPauseLogoMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec AutomaticPauseLogoCharset =
{
	// number of chars, depending on allocation type:
	// kCharSetNotShared, kCharSetShared: number of chars of a single animation frame (cols * rows)
	// kCharSetSharedMulti: sum of all chars
	76,

	// sharing scheme
	// [kCharSetNotShared, kCharSetShared, kCharSetSharedMulti]
	kCharSetShared,

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

	// number of frames, depending on charset's allocation type:
	// kCharSetNotShared, kCharSetShared: 1
	// kCharSetSharedMulti: total number of frames
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

BgmapSpriteROMSpec AutomaticPauseLogoSprite =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&AutomaticPauseLogoTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
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

BgmapSpriteROMSpec* const AutomaticPauseLogoSprites[] =
{
	&AutomaticPauseLogoSprite,
	NULL
};

EntityROMSpec AutomaticPauseLogoEntity =
{
	// class allocator
	__TYPE(Entity),

	// children
	NULL,

	// behaviors
	NULL,

	// extra
	NULL,

	// sprites
	(SpriteSpec**)AutomaticPauseLogoSprites,

	// use z displacement in projection
	false,
			
	// wireframes
	(WireframeSpec**)NULL,

	// collision shapes
	(ShapeSpec*)NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNone,

	// physical specification
	(PhysicalSpecification*)NULL,
};
