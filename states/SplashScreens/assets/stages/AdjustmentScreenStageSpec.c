/* VUEngine - Virtual Utopia Engine <https://www.vuengine.dev>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>, 2007-2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Stage.h>
#include <AdjustmentScreenState.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntitySpec ADJUSTMENT_SCREEN_BG_EN;
extern EntitySpec ADJUSTMENT_SCREEN_ICON_L_EN;
extern EntitySpec ADJUSTMENT_SCREEN_ICON_R_EN;
extern EntitySpec ADJUSTMENT_SCREEN_LOGO_EN;

#ifdef __SPLASH_SCREENS_USE_LOW_POWER_ENTITY
extern EntitySpec LOW_POWER_INDICATOR_LB;
#endif


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec ADJUSTMENT_SCREEN_STAGE_ENTITIES[] =
{
#ifdef __SPLASH_SCREENS_USE_LOW_POWER_ENTITY
	{&LOW_POWER_INDICATOR_LB, 	{__ADJUSTMENT_SCREEN_LOW_POWER_ENTITY_X_POSITION, __ADJUSTMENT_SCREEN_LOW_POWER_ENTITY_Y_POSITION, __ADJUSTMENT_SCREEN_LOW_POWER_ENTITY_Z_POSITION, __ADJUSTMENT_SCREEN_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
#endif

#if(__ADJUSTMENT_SCREEN_VARIANT == 0)

	// VUEngine
	{&ADJUSTMENT_SCREEN_ICON_L_EN, 	{ 12,  12,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_R_EN, 	{ 12, 212,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_BG_EN, 		{192, 112, 16, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_LOGO_EN, 	{192, 112,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_L_EN, 	{372, 212,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_R_EN, 	{372,  12,  0, 0}, 0, NULL, NULL, NULL, false},

#endif
#if(__ADJUSTMENT_SCREEN_VARIANT == 1)

	// PVB
	{&ADJUSTMENT_SCREEN_ICON_L_EN, 	{  8,   8,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_R_EN, 	{  8, 216,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_BG_EN, 		{192, 112, 16, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_LOGO_EN, 	{192, 110,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_L_EN, 	{376, 216,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_R_EN, 	{376,   8,  0, 0}, 0, NULL, NULL, NULL, false},

#endif
#if(__ADJUSTMENT_SCREEN_VARIANT == 2)

	// Nintendo
	{&ADJUSTMENT_SCREEN_ICON_L_EN, 	{  8,   8,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_R_EN, 	{  8, 216,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_BG_EN, 		{192, 112,  1, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_LOGO_EN, 	{192, 100,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_L_EN, 	{376, 216,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_R_EN, 	{376,   8,  0, 0}, 0, NULL, NULL, NULL, false},

#endif
#if(__ADJUSTMENT_SCREEN_VARIANT == 3)

	// Prototype
	{&ADJUSTMENT_SCREEN_ICON_L_EN, 	{  8,   8,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_R_EN, 	{  8, 216,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_BG_EN, 		{192, 112,  1, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_LOGO_EN, 	{192, 104,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_L_EN, 	{376, 216,  0, 0}, 0, NULL, NULL, NULL, false},
	{&ADJUSTMENT_SCREEN_ICON_R_EN, 	{376,   8,  0, 0}, 0, NULL, NULL, NULL, false},

#endif

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec ADJUSTMENT_SCREEN_STAGE_UI_ENTITIES[] =
{
	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

SoundROM* const ADJUSTMENT_SCREEN_STAGE_SOUNDS[] =
{
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec ADJUSTMENT_SCREEN_STAGE =
{
	// allocator
	__TYPE(Stage),

	// Timer config
	{
		__TIMER_100US,
		1000,
		kMS
	},

	// Sound config
	{
		__DEFAULT_PCM_HZ,
		false
	},

	// level
	{
		// size
		{
			// x
			__SCREEN_WIDTH,
			// y
			__SCREEN_HEIGHT,
			// z
			__SCREEN_DEPTH,
		},

		// camera's initial position inside the game world
		{
			// x
			0,
			// y
			0,
			// z
			0,
			// p
			0,
		},

		// camera's frustum
        {
        	// x0
        	0,
        	// y0
			0,
			// z0
			-10,
        	// x1
        	__SCREEN_WIDTH,
        	// y1
        	__SCREEN_HEIGHT,
        	// z1
        	__SCREEN_WIDTH * 5,
        }
	},

	// streaming
	{
		// load padding
		40,
		// unload padding
		16,
		// streaming amplitude
		24,
		// particle removal delay cycles
		0,
		// deferred
		false,
	},

	// rendering
	{
		// maximum number of texture's rows to write each time the texture writing is active
		12,

		// maximum number of rows to compute on each call to the affine functions
		16,

		// colors config
		{
			// background color
			__COLOR_BLACK,

			// brightness
			// these values times the repeat values specified in the column table (max. 16) make the final
			// brightness values on the respective regions of the screen. maximum brightness is 128.
			{
				// dark red
#if(__ADJUSTMENT_SCREEN_VARIANT == 0)
				16,
#endif
#if(__ADJUSTMENT_SCREEN_VARIANT > 0)
				__BRIGHTNESS_DARK_RED,
#endif
				// medium red
				__BRIGHTNESS_MEDIUM_RED,
				// bright red
				__BRIGHTNESS_BRIGHT_RED,
			},

			// brightness repeat
			(BrightnessRepeatSpec*)NULL,
		},

		// palettes' config
		{
			{
				// bgmap palette 0
				__BGMAP_PALETTE_0,
				// bgmap palette 1
				__BGMAP_PALETTE_1,
				// bgmap palette 2
				__BGMAP_PALETTE_2,
				// bgmap palette 3
				__BGMAP_PALETTE_3,
			},
			{
				// object palette 0
				__OBJECT_PALETTE_0,
				// object palette 1
				__OBJECT_PALETTE_1,
				// object palette 2
				__OBJECT_PALETTE_2,
				// object palette 3
				__OBJECT_PALETTE_3,
			},
		},

		// bgmap segments configuration
		// number of segments reserved for the param table
		1,

		// object segments sizes (up to 1024 in total)
		// can impact performance, make sure to configure only as large as maximally needed
		{
			// __spt0
			0,
			// __spt1
			0,
			// __spt2
			0,
			// __spt3
			0,
		},

		// object segments z coordinates
		// note that each spt's z coordinate much be larger than or equal to the previous one's,
		// since the vip renders obj worlds in reverse order (__spt3 to __spt0)
		{
			// __spt0
			0,
			// __spt1
			0,
			// __spt2
			0,
			// __spt3
			0,
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_X_VIEW_DISTANCE, __MAXIMUM_Y_VIEW_DISTANCE,
			// distance of the eyes to the screen
			__DISTANCE_EYE_SCREEN,
			// distance from left to right eye (depth sensation)
			__BASE_FACTOR,
			// horizontal view point center
			__HORIZONTAL_VIEW_POINT_CENTER,
			// vertical view point center
			__VERTICAL_VIEW_POINT_CENTER,
			// scaling factor
			__SCALING_MODIFIER_FACTOR,
		},
	},

	// physics
	{
		// gravity
		{
			__I_TO_FIX10_6(0),
			__F_TO_FIX10_6(0),
			__I_TO_FIX10_6(0),
		},

		// friction
		__F_TO_FIX10_6(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontSpec**)NULL,

		// char sets to preload
		(CharSetSpec**)NULL,

		// textures to preload
		(TextureSpec**)NULL,

		// background sounds
		(Sound**)ADJUSTMENT_SCREEN_STAGE_SOUNDS,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)ADJUSTMENT_SCREEN_STAGE_UI_ENTITIES,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)ADJUSTMENT_SCREEN_STAGE_ENTITIES,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};

