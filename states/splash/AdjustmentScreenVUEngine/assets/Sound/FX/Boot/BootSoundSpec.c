/*
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <Sound.h>
#include <SoundTrack.h>
#include <WaveForms.h>


//=========================================================================================================
// DECLARATIONS
//=========================================================================================================

extern SoundTrackROMSpec BootSoundTrack1;
extern SoundTrackROMSpec BootSoundTrack2;
extern SoundTrackROMSpec BootSoundTrack3;


//=========================================================================================================
// DEFINITIONS
//=========================================================================================================

SoundTrackROMSpec* const BootSoundTracks[] =
{
	&BootSoundTrack1,
	&BootSoundTrack2,
	&BootSoundTrack3,
	NULL
};

SoundROMSpec BootSoundSpec =
{
	// Name
	"Boot Sound",

	// Play in loop
	false,

	// Tick duraction in US
	1000,

	// Tracks
	(SoundTrackSpec**)NULL
};
