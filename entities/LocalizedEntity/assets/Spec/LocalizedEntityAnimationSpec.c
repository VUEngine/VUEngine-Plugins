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

#include <BgmapAnimatedSprite.h>
#include <uiConfig.h>

//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec LOCALIZED_ENTITY_0_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 0
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"0",
};

#if(__MAX_ANIMATION_FUNCTIONS > 2)
AnimationFunctionROMSpec LOCALIZED_ENTITY_1_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 1
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"1",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 3)
AnimationFunctionROMSpec LOCALIZED_ENTITY_2_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 2
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"2",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 4)
AnimationFunctionROMSpec LOCALIZED_ENTITY_3_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 3
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"3",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 5)
AnimationFunctionROMSpec LOCALIZED_ENTITY_4_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 4
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"4",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 6)
AnimationFunctionROMSpec LOCALIZED_ENTITY_5_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 5
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"5",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 7)
AnimationFunctionROMSpec LOCALIZED_ENTITY_6_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 6
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"6",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 8)
AnimationFunctionROMSpec LOCALIZED_ENTITY_7_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 7
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"7",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 9)
AnimationFunctionROMSpec LOCALIZED_ENTITY_8_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 8
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"8",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 10)
AnimationFunctionROMSpec LOCALIZED_ENTITY_9_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 9
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"9",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 11)
AnimationFunctionROMSpec LOCALIZED_ENTITY_10_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 10
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"10",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 12)
AnimationFunctionROMSpec LOCALIZED_ENTITY_11_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 11
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"11",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 13)
AnimationFunctionROMSpec LOCALIZED_ENTITY_12_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 12
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"12",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 14)
AnimationFunctionROMSpec LOCALIZED_ENTITY_13_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 13
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"13",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 15)
AnimationFunctionROMSpec LOCALIZED_ENTITY_14_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 14
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"14",
};
#endif

#if(__MAX_ANIMATION_FUNCTIONS > 16)
AnimationFunctionROMSpec LOCALIZED_ENTITY_15_ANIM =
{
	// number of frames of this animation function
	ANIMATED_LABEL_TOTAL_FRAMES,

	// frames to play in animation
	{
		ANIMATED_LABEL_FRAMES 15
	},

	// number of cycles a frame of animation is displayed
	ANIMATED_LABEL_FRAME_CYCLE,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"15",
};
#endif

// an animation spec
AnimationDescriptionROMSpec LOCALIZED_ENTITY_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&LOCALIZED_ENTITY_0_ANIM,
		#if(__MAX_ANIMATION_FUNCTIONS > 2)
		(AnimationFunction*)&LOCALIZED_ENTITY_1_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 3)
		(AnimationFunction*)&LOCALIZED_ENTITY_2_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 4)
		(AnimationFunction*)&LOCALIZED_ENTITY_3_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 5)
		(AnimationFunction*)&LOCALIZED_ENTITY_4_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 6)
		(AnimationFunction*)&LOCALIZED_ENTITY_5_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 7)
		(AnimationFunction*)&LOCALIZED_ENTITY_6_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 8)
		(AnimationFunction*)&LOCALIZED_ENTITY_7_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 9)
		(AnimationFunction*)&LOCALIZED_ENTITY_8_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 10)
		(AnimationFunction*)&LOCALIZED_ENTITY_9_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 11)
		(AnimationFunction*)&LOCALIZED_ENTITY_10_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 12)
		(AnimationFunction*)&LOCALIZED_ENTITY_11_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 13)
		(AnimationFunction*)&LOCALIZED_ENTITY_12_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 14)
		(AnimationFunction*)&LOCALIZED_ENTITY_13_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 15)
		(AnimationFunction*)&LOCALIZED_ENTITY_14_ANIM,
		#endif
		#if(__MAX_ANIMATION_FUNCTIONS > 16)
		(AnimationFunction*)&LOCALIZED_ENTITY_15_ANIM,
		#endif
		NULL,
	}
};
