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

#include <SoundTrack.h>
#include <WaveForms.h>


//=========================================================================================================
// DEFINITIONS
//=========================================================================================================

const uint8 AutomaticPauseSelectSoundTrack1SxINT[] =
{
	0x9F,
};

const uint8 AutomaticPauseSelectSoundTrack1SxLRV[] =
{
	0xFF,
};

const uint16 AutomaticPauseSelectSoundTrack1SxFQ[] =
{
	E_4
};

const uint8 AutomaticPauseSelectSoundTrack1SxEV0[] =
{
	0xF0,
};

const uint8 AutomaticPauseSelectSoundTrack1SxEV1[] =
{
	0x00, 0x01
};

const int8* const AutomaticPauseSelectSoundTrack1SxRAM[] =
{
	SawtoothWaveForm,
};

const uint8 AutomaticPauseSelectSoundTrack1SxSWP[] =
{
	0x00,
};

const SoundTrackKeyframe AutomaticPauseSelectSoundTrack1Keyframes[] =
{
	{40, kSoundTrackEventStart},
	{40, kSoundTrackEventSxEV1},
	{0, kSoundTrackEventEnd},	
};

SoundTrackROMSpec AutomaticPauseSelectSoundTrack1 =
{
	/// kTrackNative, kTrackPCM
	kTrackNative,

	/// Skip if no sound source available?
	false,

	/// Total number of samples (0 if not PCM)
	0,

	/// Keyframes that define the track
	(SoundTrackKeyframe*)AutomaticPauseSelectSoundTrack1Keyframes,

	/// SxINT values
	(uint8*)AutomaticPauseSelectSoundTrack1SxINT,

	/// SxLRV values
	(uint8*)AutomaticPauseSelectSoundTrack1SxLRV,

	/// SxFQH and SxFQL values
	(uint16*)AutomaticPauseSelectSoundTrack1SxFQ,

	/// SxEV0 values
	(uint8*)AutomaticPauseSelectSoundTrack1SxEV0,

	/// SxEV1 values
	(uint8*)AutomaticPauseSelectSoundTrack1SxEV1,

	/// SxRAM pointers
	(int8**)AutomaticPauseSelectSoundTrack1SxRAM,

	/// S5SWP values
	(uint8*)AutomaticPauseSelectSoundTrack1SxSWP
};