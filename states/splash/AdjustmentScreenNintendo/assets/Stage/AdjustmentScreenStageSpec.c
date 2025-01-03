/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Stage.h>
#include <AdjustmentScreenState.h>



//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


extern EntitySpec AdjustmentScreenBgEntitySpec;
extern EntitySpec AdjustmentScreenIconLEntitySpec;
extern EntitySpec AdjustmentScreenIconREntitySpec;
extern EntitySpec AdjustmentScreenLogoEntitySpec;

#if __PLUGIN_ADJUSTMENT_SCREEN_NINTENDO_USE_LOW_POWER_ENTITY
extern EntitySpec LowPowerIndicatorEntitySpec;
#endif


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// ENTITY LISTS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

PositionedEntityROMSpec AdjustmentScreenStageEntities[] =
{
	{NULL, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec AdjustmentScreenStageUiEntities[] =
{
#if __PLUGIN_ADJUSTMENT_SCREEN_NINTENDO_USE_LOW_POWER_ENTITY
	{&LowPowerIndicatorEntitySpec, 	{__PLUGIN_ADJUSTMENT_SCREEN_NINTENDO_LOW_POWER_ENTITY_X_POSITION, __PLUGIN_ADJUSTMENT_SCREEN_NINTENDO_LOW_POWER_ENTITY_Y_POSITION, __PLUGIN_ADJUSTMENT_SCREEN_NINTENDO_LOW_POWER_ENTITY_Z_POSITION, __PLUGIN_ADJUSTMENT_SCREEN_NINTENDO_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
#endif

#ifdef __LEGACY_COORDINATE_PROJECTION
	{&AdjustmentScreenIconLEntitySpec, 	{   8,    8,  0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
	{&AdjustmentScreenIconREntitySpec, 	{   8,  216,  0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
	{&AdjustmentScreenBgEntitySpec, 	{ 192,  112,  1}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
	{&AdjustmentScreenLogoEntitySpec, 	{ 192,  100,  0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
	{&AdjustmentScreenIconLEntitySpec, 	{ 376,  216,  0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
	{&AdjustmentScreenIconREntitySpec, 	{ 376,    8,  0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
#else
	{&AdjustmentScreenIconLEntitySpec, 	{-184, -104,  0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
	{&AdjustmentScreenIconREntitySpec, 	{-184,  104,  0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
	{&AdjustmentScreenBgEntitySpec, 	{   0,    0,  1}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
	{&AdjustmentScreenLogoEntitySpec, 	{   0,  -12,  0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
	{&AdjustmentScreenIconLEntitySpec, 	{ 184,  104,  0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
	{&AdjustmentScreenIconREntitySpec, 	{ 184, -104,  0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
#endif

	{NULL, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, 0, NULL, NULL, NULL, false},
};

SoundROMSpec* const AdjustmentScreenStageSoundSpecs[] =
{
	NULL
};


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// STAGE DEFINITION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

StageROMSpec AdjustmentScreenStage =
{
	// Class allocator
	__TYPE(Stage),

	// Timer config
	{
		__TIMER_100US,
		10,
		kMS
	},

	// Sound config
	{
		__DEFAULT_PCM_HZ,
		false
	},

	// General stage's attributes
	{
		// Stage's size in pixels
		{
			// x
			__SCREEN_WIDTH,
			// y
			__SCREEN_HEIGHT,
			// z
			__SCREEN_DEPTH,
		},

		// Camera's initial position inside the stage
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

		// Camera's frustum
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

	// Streaming
	{
		// Padding to be added to camera's frustum when checking if a entity spec
		// describes an entity that is within the camera's range
		40,
		// Padding to be added to camera's frustum when checking if a entity is
		// out of the camera's range
		16,
		// Amount of entity descriptions to check for streaming in entities
		24,
		// If true, entity instantiation is done over time
		false,
	},

	// Rendering
	{
		// Maximum number of texture's rows to write each time the texture writing is active
		12,

		// Maximum number of rows to compute on each call to the affine functions
		16,

		// Color configuration
		{
			// Background color
			__COLOR_BLACK,

			// Brightness
			// These values times the repeat values specified in the column table (max. 16) make the final
			// brightness values on the respective regions of the screen. maximum brightness is 128.
			{
				// Dark red
				__BRIGHTNESS_DARK_RED,
				// Medium red
				__BRIGHTNESS_MEDIUM_RED,
				// Bright red
				__BRIGHTNESS_BRIGHT_RED,
			},

			// Brightness repeat
			(BrightnessRepeatSpec*)NULL,
		},

		// Palettes' configuration
		{
			{
				// Bgmap palette 0
				__BGMAP_PALETTE_0,
				// Bgmap palette 1
				__BGMAP_PALETTE_1,
				// Bgmap palette 2
				__BGMAP_PALETTE_2,
				// Bgmap palette 3
				__BGMAP_PALETTE_3,
			},
			{
				// Object palette 0
				__OBJECT_PALETTE_0,
				// Object palette 1
				__OBJECT_PALETTE_1,
				// Object palette 2
				__OBJECT_PALETTE_2,
				// Object palette 3
				__OBJECT_PALETTE_3,
			},
		},

		// Bgmap segments configuration
		// Number of BGMAP segments reserved for the param
		1,

		// Object segments' sizes (__spt0 to __spt3, up to 1024 in total)
		// Can impact performance, make sure to configure only as large as maximally needed
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

		// Object segments' z coordinates (__spt0 to __spt3)
		// Note that each spt's z coordinate much be larger than or equal to the previous one's,
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

		// Struct defining the optical settings for the stage
		{
			// Maximum view distance's power into the horizon
			__MAXIMUM_X_VIEW_DISTANCE, __MAXIMUM_Y_VIEW_DISTANCE,
			// Distance of the eyes to the screen
			0,
			// Distance from left to right eye (depth sensation)
			__BASE_FACTOR,
			// Horizontal view point center
			__HORIZONTAL_VIEW_POINT_CENTER,
			// Vertical view point center
			__VERTICAL_VIEW_POINT_CENTER,
			// Scaling factor
			__SCALING_MODIFIER_FACTOR,
		},
	},

	// Physical world's properties
	{
		// Gravity
		{
			__I_TO_FIXED(0),
			__F_TO_FIXED(0),
			__I_TO_FIXED(0),
		},

		// Friction coefficient
		__F_TO_FIXED(0),
	},

	// Assets
	{
		// Fonts to preload
		(FontSpec**)NULL,

		// CharSets to preload
		(CharSetSpec**)NULL,

		// Textures to preload
		(TextureSpec**)NULL,

		// background sounds
		(SoundSpec**)AdjustmentScreenStageSoundSpecs,
	},

	// Entities
	{
		// UI configuration
		{
			(PositionedEntity*)AdjustmentScreenStageUiEntities,
			__TYPE(UIContainer),
		},

		// Stage's children entities
		(PositionedEntity*)AdjustmentScreenStageEntities,
	},

	// Post processing effects
	(PostProcessingEffect*)NULL,
};

