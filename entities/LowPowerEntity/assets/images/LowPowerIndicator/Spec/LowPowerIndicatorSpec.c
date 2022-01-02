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

#ifdef __LOW_POWER_ENTITY_USE_GUI_BGMAP_ANIMATED_SPRITE
#include <GuiBgmapAnimatedSprite.h>
#else
#include <BgmapAnimatedSprite.h>
#endif
#include <LowPowerEntity.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 LowPowerIndicatorTiles[];
extern uint16 LowPowerIndicatorMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec LowPowerIndicatorHideAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{
		0,
	},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Hide",
};

AnimationFunctionROMSpec LowPowerIndicatorFlashAnimation =
{
	// number of frames of this animation function
	12,

	// frames to play in animation
	{
		0, 0, 0, 0, 3, 2, 1, 1, 1, 1, 2, 3,
	},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Flash",
};

AnimationDescriptionROMSpec LowPowerIndicatorAnimation =
{
	// animation functions
	{
		(AnimationFunction*)&LowPowerIndicatorHideAnimation,
		(AnimationFunction*)&LowPowerIndicatorFlashAnimation,
		NULL,
	}
};

CharSetROMSpec LowPowerIndicatorCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	2,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	LowPowerIndicatorTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec LowPowerIndicatorTexture =
{
	// charset spec
	(CharSetSpec*)&LowPowerIndicatorCharset,

	// bgmap spec
	LowPowerIndicatorMap,

	// cols (max 64)
	2,

	// rows (max 64)
	1,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
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

BgmapSpriteROMSpec LowPowerIndicatorSprite =
{
	{
		// sprite's type
#ifdef __LOW_POWER_ENTITY_USE_GUI_BGMAP_ANIMATED_SPRITE
		__TYPE(GuiBgmapAnimatedSprite),
#else
		__TYPE(BgmapAnimatedSprite),
#endif

		// texture spec
		(TextureSpec*)&LowPowerIndicatorTexture,

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

BgmapSpriteROMSpec* const LowPowerIndicatorSprites[] =
{
	&LowPowerIndicatorSprite,
	NULL
};

LowPowerEntityROMSpec LowPowerIndicatorEntity =
{
	{
		// class allocator
		__TYPE(LowPowerEntity),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)LowPowerIndicatorSprites,

		// use z displacement in projection
		false,

		// collision shapes
		(ShapeSpec*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeNone,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the item
	(AnimationDescription*)&LowPowerIndicatorAnimation,

	// initial animation
	"Hide",
};
