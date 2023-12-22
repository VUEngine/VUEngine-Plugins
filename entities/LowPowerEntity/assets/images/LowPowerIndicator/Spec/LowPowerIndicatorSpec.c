/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------


#include <LowPowerEntity.h>
#include <VIPManager.h>
#ifdef __LOW_POWER_ENTITY_USE_GUI_BGMAP_ANIMATED_SPRITE
#include <GuiBgmapAnimatedSprite.h>
#else
#include <BgmapAnimatedSprite.h>
#endif


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 LowPowerIndicatorTiles[];
extern uint16 LowPowerIndicatorMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec LowPowerIndicatorHideAnimationSpec =
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

AnimationFunctionROMSpec LowPowerIndicatorFlashAnimationSpec =
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

AnimationFunctionROMSpec* const LowPowerIndicatorAnimationSpecs[] =
{
	&LowPowerIndicatorHideAnimationSpec,
	&LowPowerIndicatorFlashAnimationSpec,
	NULL,
};

CharSetROMSpec LowPowerIndicatorCharsetSpec =
{
	// number of chars in function of the number of frames to load at the same time

	2,

	// whether it is shared or not
	false,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	LowPowerIndicatorTiles,

	// pointer to the frames offsets
	NULL
};

TextureROMSpec LowPowerIndicatorTextureSpec =
{
	// charset spec
	(CharSetSpec*)&LowPowerIndicatorCharsetSpec,

	// bgmap spec
	LowPowerIndicatorMap,

	// cols (max 64)
	2,

	// rows (max 64)
	1,

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

BgmapSpriteROMSpec LowPowerIndicatorSpriteSpec =
{
	{
		// sprite's type
#ifdef __LOW_POWER_ENTITY_USE_GUI_BGMAP_ANIMATED_SPRITE
		__TYPE(GuiBgmapAnimatedSprite),
#else
		__TYPE(BgmapAnimatedSprite),
#endif

		// texture spec
		(TextureSpec*)&LowPowerIndicatorTextureSpec,

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

BgmapSpriteROMSpec* const LowPowerIndicatorSpriteSpecs[] =
{
	&LowPowerIndicatorSpriteSpec,
	NULL
};

LowPowerEntityROMSpec LowPowerIndicatorEntitySpec =
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
		(SpriteSpec**)LowPowerIndicatorSpriteSpecs,

		// use z displacement in projection
		false,
			
		// wireframes
		(WireframeSpec**)NULL,

		// collision shapes
		(ColliderSpec*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeNone,

		// physical specification
		(PhysicalProperties*)NULL,
	},

	// pointer to the animation spec for the item
	(const AnimationFunction**)LowPowerIndicatorAnimationSpecs,

	// initial animation
	"Hide",
};
