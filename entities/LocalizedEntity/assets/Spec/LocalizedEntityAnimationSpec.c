/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2019 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec LOCALIZED_ENTITY_0_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"0",
};

AnimationFunctionROMSpec LOCALIZED_ENTITY_1_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{1},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"1",
};

AnimationFunctionROMSpec LOCALIZED_ENTITY_2_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{2},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"2",
};

AnimationFunctionROMSpec LOCALIZED_ENTITY_3_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{3},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"3",
};

AnimationFunctionROMSpec LOCALIZED_ENTITY_4_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{4},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"4",
};

AnimationFunctionROMSpec LOCALIZED_ENTITY_5_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{5},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"5",
};

AnimationFunctionROMSpec LOCALIZED_ENTITY_6_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{6},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"6",
};

AnimationFunctionROMSpec LOCALIZED_ENTITY_7_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{7},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"7",
};

// an animation spec
AnimationDescriptionROMSpec LOCALIZED_ENTITY_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&LOCALIZED_ENTITY_0_ANIM,
		(AnimationFunction*)&LOCALIZED_ENTITY_1_ANIM,
		(AnimationFunction*)&LOCALIZED_ENTITY_2_ANIM,
		(AnimationFunction*)&LOCALIZED_ENTITY_3_ANIM,
		(AnimationFunction*)&LOCALIZED_ENTITY_4_ANIM,
		(AnimationFunction*)&LOCALIZED_ENTITY_5_ANIM,
		(AnimationFunction*)&LOCALIZED_ENTITY_6_ANIM,
		//(AnimationFunction*)&LOCALIZED_ENTITY_7_ANIM,
		NULL,
	}
};
