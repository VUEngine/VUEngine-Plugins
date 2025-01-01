///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                              THIS FILE WAS AUTO-GENERATED - DO NOT EDIT                               //
///////////////////////////////////////////////////////////////////////////////////////////////////////////


//——————————————————————————————————————————————————————————————————————————————————————————————————————————

//                                                INCLUDES                                                 

//——————————————————————————————————————————————————————————————————————————————————————————————————————————


#include <BgmapSprite.h>
#include <Entity.h>
#include <Texture.h>



//——————————————————————————————————————————————————————————————————————————————————————————————————————————

//                                              DECLARATIONS                                               

//——————————————————————————————————————————————————————————————————————————————————————————————————————————


extern uint32 AlignmentCheckEntityAlignmentCheckLeftTiles[];
extern uint16 AlignmentCheckEntityAlignmentCheckLeftMap[];
extern uint32 AlignmentCheckEntityAlignmentCheckRightTiles[];
extern uint16 AlignmentCheckEntityAlignmentCheckRightMap[];



//——————————————————————————————————————————————————————————————————————————————————————————————————————————

//                                                 SPRITES                                                 

//——————————————————————————————————————————————————————————————————————————————————————————————————————————



CharSetROMSpec AlignmentCheckSprite1CharsetSpec =
{
	// Number of chars in function or the number of frames to load at the same time
	1,

	// Whether it is shared or not
	true,

	// Whether the tiles are optimized or not
	true,

	// Tiles array
	AlignmentCheckEntityAlignmentCheckLeftTiles,

	// Frame offsets array
	NULL,
};

TextureROMSpec AlignmentCheckSprite1TextureSpec =
{
	// Pointer to the char spec that the texture uses
	(CharSetSpec*)&AlignmentCheckSprite1CharsetSpec,

	// Pointer to the map array that defines how to use the tiles from the char set
	AlignmentCheckEntityAlignmentCheckLeftMap,

	// Horizontal size in tiles of the texture (max. 64)
	48,

	// Vertical size in tiles of the texture (max. 64)
	1,

	// padding for affine/hbias transformations
	{ 0, 0 },

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

BgmapSpriteROMSpec AlignmentCheckSprite1SpriteSpec =
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
		(TextureSpec*)&AlignmentCheckSprite1TextureSpec,

		// Transparency mode (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// Displacement added to the sprite's position
		{ 0, 0, 0, 0 },
	},

	// The display mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,
	
	// Pointer to affine/hbias manipulation function
	NULL,

	// Flag to indicate in which display to show the texture (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_LON,
};


CharSetROMSpec AlignmentCheckSprite2CharsetSpec =
{
	// Number of chars in function or the number of frames to load at the same time
	2,

	// Whether it is shared or not
	true,

	// Whether the tiles are optimized or not
	true,

	// Tiles array
	AlignmentCheckEntityAlignmentCheckRightTiles,

	// Frame offsets array
	NULL,
};

TextureROMSpec AlignmentCheckSprite2TextureSpec =
{
	// Pointer to the char spec that the texture uses
	(CharSetSpec*)&AlignmentCheckSprite2CharsetSpec,

	// Pointer to the map array that defines how to use the tiles from the char set
	AlignmentCheckEntityAlignmentCheckRightMap,

	// Horizontal size in tiles of the texture (max. 64)
	16,

	// Vertical size in tiles of the texture (max. 64)
	3,

	// padding for affine/hbias transformations
	{ 0, 0 },

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

BgmapSpriteROMSpec AlignmentCheckSprite2SpriteSpec =
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
		(TextureSpec*)&AlignmentCheckSprite2TextureSpec,

		// Transparency mode (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// Displacement added to the sprite's position
		{ 0, 0, 0, 0 },
	},

	// The display mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,
	
	// Pointer to affine/hbias manipulation function
	NULL,

	// Flag to indicate in which display to show the texture (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_RON,
};




//——————————————————————————————————————————————————————————————————————————————————————————————————————————

//                                                 ENTITY                                                  

//——————————————————————————————————————————————————————————————————————————————————————————————————————————


ComponentSpec* const AlignmentCheckEntityComponentSpecs[] = 
{
	(ComponentSpec*)&AlignmentCheckSprite1SpriteSpec,
	(ComponentSpec*)&AlignmentCheckSprite2SpriteSpec,
	NULL
};

EntityROMSpec AlignmentCheckEntitySpec =
{
			// Class allocator			
			__TYPE(Entity),

			// Component specs
			(ComponentSpec**)AlignmentCheckEntityComponentSpecs,

			// Children specs
			NULL,

			// Extra info
			NULL,

			// Size
			// If 0, it is computed from the visual components if any
			{ 0, 0, 0 },

			// Entity's in-game type
			kTypeNone,

			
};
