///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                              THIS FILE WAS AUTO-GENERATED - DO NOT EDIT                               //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------------------
//                                                INCLUDES                                                 
//---------------------------------------------------------------------------------------------------------

#include <BgmapSprite.h>
#include <Entity.h>
#include <Texture.h>


//---------------------------------------------------------------------------------------------------------
//                                              DECLARATIONS                                               
//---------------------------------------------------------------------------------------------------------

extern uint32 AlignmentCheckEntityAlignmentCheckLeftTiles[];
extern uint16 AlignmentCheckEntityAlignmentCheckLeftMap[];
extern uint32 AlignmentCheckEntityAlignmentCheckRightTiles[];
extern uint16 AlignmentCheckEntityAlignmentCheckRightMap[];


//---------------------------------------------------------------------------------------------------------
//                                                 SPRITES                                                 
//---------------------------------------------------------------------------------------------------------


CharSetROMSpec AlignmentCheckSprite1CharsetSpec =
{
	// number of chars in function or the number of frames to load at the same time
	1,

	// whether it is shared or not
	true,

	// whether the tiles are optimized or not
	true,

	// char spec
	AlignmentCheckEntityAlignmentCheckLeftTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec AlignmentCheckSprite1TextureSpec =
{
	// charset spec
	(CharSetSpec*)&AlignmentCheckSprite1CharsetSpec,

	// bgmap spec
	AlignmentCheckEntityAlignmentCheckLeftMap,

	// cols (max 64)
	48,

	// rows (max 64)
	1,

	// padding for affine/hbias transformations
	{ 0, 0 },

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

		// texture spec
		(TextureSpec*)&AlignmentCheckSprite1TextureSpec,

		// transparency (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{ 0, 0, 0, 0 },
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,
	
	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_LON,
};


CharSetROMSpec AlignmentCheckSprite2CharsetSpec =
{
	// number of chars in function or the number of frames to load at the same time
	2,

	// whether it is shared or not
	true,

	// whether the tiles are optimized or not
	true,

	// char spec
	AlignmentCheckEntityAlignmentCheckRightTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec AlignmentCheckSprite2TextureSpec =
{
	// charset spec
	(CharSetSpec*)&AlignmentCheckSprite2CharsetSpec,

	// bgmap spec
	AlignmentCheckEntityAlignmentCheckRightMap,

	// cols (max 64)
	16,

	// rows (max 64)
	3,

	// padding for affine/hbias transformations
	{ 0, 0 },

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

		// texture spec
		(TextureSpec*)&AlignmentCheckSprite2TextureSpec,

		// transparency (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{ 0, 0, 0, 0 },
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,
	
	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_RON,
};



//---------------------------------------------------------------------------------------------------------
//                                                 ENTITY                                                  
//---------------------------------------------------------------------------------------------------------

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
