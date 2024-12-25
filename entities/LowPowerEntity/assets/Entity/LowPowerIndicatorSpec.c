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


#include <LowPowerEntity.h>
#include <VIPManager.h>
#include <BgmapAnimatedSprite.h>


//=========================================================================================================
// DECLARATIONS
//=========================================================================================================

extern uint32 LowPowerIndicatorTiles[];
extern uint16 LowPowerIndicatorMap[];


//=========================================================================================================
// DEFINITIONS
//=========================================================================================================

AnimationFunctionROMSpec LowPowerIndicatorHideAnimationSpec =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		0,
	},

	// Number of cycles a frame of animation is displayed
	4,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"Hide",
};

AnimationFunctionROMSpec LowPowerIndicatorFlashAnimationSpec =
{
	// Number of frames that the texture supports of this animation function
	12,

	// Frames to play in animation
	{
		0, 0, 0, 0, 3, 2, 1, 1, 1, 1, 2, 3,
	},

	// Number of cycles a frame of animation is displayed
	4,

	// Whether to play it in loop or not
	true,

	// Callback on animation completion
	NULL,

	// Animation's name
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
	// Number of chars in function of the number of frames to load at the same time

	2,

	// Whether it is shared or not
	true,
	
	// Whether the tiles are optimized or not
	false,

	// Tiles array
	LowPowerIndicatorTiles,

	// Frame offsets array
	NULL
};

TextureROMSpec LowPowerIndicatorTextureSpec =
{
	// Pointer to the char spec that the texture uses
	(CharSetSpec*)&LowPowerIndicatorCharsetSpec,

	// Pointer to the map array that defines how to use the tiles from the char set
	LowPowerIndicatorMap,

	// Horizontal size in tiles of the texture (max. 64)
	2,

	// Vertical size in tiles of the texture (max. 64)
	1,

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

BgmapSpriteROMSpec LowPowerIndicatorSpriteSpec =
{
	{
		// Component
		{
			// Allocator
			__TYPE(BgmapAnimatedSprite),

			// Component type
			kSpriteComponent
		},

		// Spec for the texture to display
		(TextureSpec*)&LowPowerIndicatorTextureSpec,

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

ComponentSpec* const LowPowerIndicatorEntityComponentSpecs[] = 
{
	(ComponentSpec*)&LowPowerIndicatorSpriteSpec,
	NULL
};

LowPowerEntityROMSpec LowPowerIndicatorEntitySpec =
{
	// animated entity
	{
		// entity
		{
			// Class allocator			
			__TYPE(LowPowerEntity),

			// Component specs
			(ComponentSpec**)LowPowerIndicatorEntityComponentSpecs,

			// Children specs
			NULL,

			// Extra info
			NULL,

			// Size
			// If 0, it is computed from the visual components if any
			{0, 0, 0},

			// Entity's in-game type
			kTypeNone,

			
		},

		// Pointer to animation functions array
		(const AnimationFunction**)LowPowerIndicatorAnimationSpecs,

		// Animation to play automatically
		"Hide",
	}
};
