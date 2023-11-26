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

extern uint32 FlagUnitedKingdomTiles[];
extern uint16 FlagUnitedKingdomMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec FlagUnitedKingdomCharset =
{
	// number of chars, depending on allocation type:
	// kCharSetNotShared, kCharSetShared: number of chars of a single animation frame (cols * rows)
	// kCharSetSharedMulti: sum of all chars
	10,

	// sharing scheme
	// [kCharSetNotShared, kCharSetShared, kCharSetSharedMulti]
	kCharSetShared,

	// char spec
	FlagUnitedKingdomTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec FlagUnitedKingdomTexture =
{
	// charset spec
	(CharSetSpec*)&FlagUnitedKingdomCharset,

	// bgmap spec
	FlagUnitedKingdomMap,

	// cols (max 64)
	5,

	// rows (max 64)
	4,

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

BgmapSpriteROMSpec FlagUnitedKingdomSprite =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&FlagUnitedKingdomTexture,

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

BgmapSpriteROMSpec* const FlagUnitedKingdomSprites[] =
{
	&FlagUnitedKingdomSprite,
	NULL
};

EntityROMSpec FlagUnitedKingdomEntity =
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
	(SpriteSpec**)FlagUnitedKingdomSprites,

	// use z displacement in projection
	false,

	// wireframes
	(WireframeSpec**)NULL,

	// collision shapes
	NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNone,

	// physical specification
	NULL,
};
