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

extern SoundTrackROMSpec PrecautionScreenIntroSoundTrack1;


//=========================================================================================================
// DEFINITIONS
//=========================================================================================================

SoundTrackROMSpec* const PrecautionScreenIntroSoundTracks[] =
{
	&PrecautionScreenIntroSoundTrack1,
	NULL
};

SoundROMSpec PrecautionScreenIntroSoundSpec =
{
	// Name
	"Intro Sound",

	// Play in loop
	false,

	// Tick duration in US
	1000,

	// Tracks
	(SoundTrackSpec**)PrecautionScreenIntroSoundTracks
};
