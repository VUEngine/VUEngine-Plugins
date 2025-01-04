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

#include <BgmapAnimatedSprite.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// DEFINITIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

AnimationFunctionROMSpec LocalizedActor0Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		0
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"0",
};

AnimationFunctionROMSpec LocalizedActor1Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		1
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"1",
};

AnimationFunctionROMSpec LocalizedActor2Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		2
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"2",
};

AnimationFunctionROMSpec LocalizedActor3Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		3
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"3",
};

AnimationFunctionROMSpec LocalizedActor4Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		4
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"4",
};

AnimationFunctionROMSpec LocalizedActor5Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		5
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"5",
};

AnimationFunctionROMSpec LocalizedActor6Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		6
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"6",
};

AnimationFunctionROMSpec LocalizedActor7Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		7
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"7",
};

AnimationFunctionROMSpec LocalizedActor8Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		8
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"8",
};

AnimationFunctionROMSpec LocalizedActor9Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		9
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"9",
};

AnimationFunctionROMSpec LocalizedActor10Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		0
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"10",
};

AnimationFunctionROMSpec LocalizedActor11Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		1
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"11",
};

AnimationFunctionROMSpec LocalizedActor12Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		2
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"12",
};

AnimationFunctionROMSpec LocalizedActor13Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		3
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"13",
};

AnimationFunctionROMSpec LocalizedActor14Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		4
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"14",
};

AnimationFunctionROMSpec LocalizedActor15Animations =
{
	// Number of frames that the texture supports of this animation function
	1,

	// Frames to play in animation
	{
		5
	},

	// Number of cycles a frame of animation is displayed
	8,

	// Whether to play it in loop or not
	false,

	// Callback on animation completion
	NULL,

	// Animation's name
	"15",
};

// an animation spec
AnimationFunctionROMSpec* const LocalizedActorAnimationSpecs[] =
{
	&LocalizedActor0Animations,
	
	&LocalizedActor1Animations,
		
	&LocalizedActor2Animations,
		
	&LocalizedActor3Animations,
		
	&LocalizedActor4Animations,
		
	&LocalizedActor5Animations,
		
	&LocalizedActor6Animations,
		
	&LocalizedActor7Animations,
		
	&LocalizedActor8Animations,
		
	&LocalizedActor9Animations,
		
	&LocalizedActor10Animations,
		
	&LocalizedActor11Animations,
		
	&LocalizedActor12Animations,
		
	&LocalizedActor13Animations,
		
	&LocalizedActor14Animations,
		
	&LocalizedActor15Animations,
		NULL,
};
