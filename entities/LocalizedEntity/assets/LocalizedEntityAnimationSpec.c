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

AnimationFunctionROMSpec LocalizedEntity0Animations =
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


AnimationFunctionROMSpec LocalizedEntity1Animations =
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


AnimationFunctionROMSpec LocalizedEntity2Animations =
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


AnimationFunctionROMSpec LocalizedEntity3Animations =
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


AnimationFunctionROMSpec LocalizedEntity4Animations =
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


AnimationFunctionROMSpec LocalizedEntity5Animations =
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


AnimationFunctionROMSpec LocalizedEntity6Animations =
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


AnimationFunctionROMSpec LocalizedEntity7Animations =
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


AnimationFunctionROMSpec LocalizedEntity8Animations =
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


AnimationFunctionROMSpec LocalizedEntity9Animations =
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


AnimationFunctionROMSpec LocalizedEntity10Animations =
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


AnimationFunctionROMSpec LocalizedEntity11Animations =
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


AnimationFunctionROMSpec LocalizedEntity12Animations =
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


AnimationFunctionROMSpec LocalizedEntity13Animations =
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


AnimationFunctionROMSpec LocalizedEntity14Animations =
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


AnimationFunctionROMSpec LocalizedEntity15Animations =
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
AnimationFunctionROMSpec* const LocalizedEntityAnimationSpecs[] =
{
	&LocalizedEntity0Animations,
	
	&LocalizedEntity1Animations,
		
	&LocalizedEntity2Animations,
		
	&LocalizedEntity3Animations,
		
	&LocalizedEntity4Animations,
		
	&LocalizedEntity5Animations,
		
	&LocalizedEntity6Animations,
		
	&LocalizedEntity7Animations,
		
	&LocalizedEntity8Animations,
		
	&LocalizedEntity9Animations,
		
	&LocalizedEntity10Animations,
		
	&LocalizedEntity11Animations,
		
	&LocalizedEntity12Animations,
		
	&LocalizedEntity13Animations,
		
	&LocalizedEntity14Animations,
		
	&LocalizedEntity15Animations,
		NULL,
};
