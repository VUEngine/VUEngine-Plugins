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
#include <VSUSoundTrack.h>
#include <WaveForms.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

extern VSUSoundTrackROMSpec BootSoundTrack1;
extern VSUSoundTrackROMSpec BootSoundTrack2;
extern VSUSoundTrackROMSpec BootSoundTrack3;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// DEFINITIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

VSUSoundTrackROMSpec* const BootSoundTracks[] =
{
	&BootSoundTrack1,
	&BootSoundTrack2,
	&BootSoundTrack3,
	NULL
};

SoundROMSpec BootSoundSpec =
{
	// Component
	{
		// Allocator
		__TYPE(Sound),

		// Component type
		kSoundComponent
	},

	// Song/Sound's name
	"Boot Sound",

	// Author's name
	NULL,

	// Play in loop
	false,

	// Tick duration in US
	1000,

	// Tracks
	(SoundTrackSpec**)NULL,

	// Sound group
	kSoundGroupEffects
};
