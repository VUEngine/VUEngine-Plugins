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

#include <Sound.h>
#include <SoundTrack.h>
#include <WaveForms.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

extern SoundTrackROMSpec AutomaticPauseConfirmSoundTrack1;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// DEFINITIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

SoundTrackROMSpec* const AutomaticPauseConfirmSoundTracks[] =
{
	&AutomaticPauseConfirmSoundTrack1,
	NULL
};

SoundROMSpec AutomaticPauseConfirmSoundSpec =
{
	// Component
	{
		// Allocator
		__TYPE(Sound),

		// Component type
		kSoundComponent
	},

	// Song/Sound's name
	"AutomaticPause confirm",

	// Author's name
	NULL,

	// Play in loop
	false,

	// Tick duration in US
	1000,

	// Tracks
	(SoundTrackSpec**)AutomaticPauseConfirmSoundTracks,

	// Sound group
	kSoundGroupEffects
};