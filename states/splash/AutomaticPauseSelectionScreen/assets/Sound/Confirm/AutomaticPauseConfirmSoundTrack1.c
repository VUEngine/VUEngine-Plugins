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

const uint8 AutomaticPauseConfirmSoundTrack1SxINT[] =
{
	0x9F,
};

const uint8 AutomaticPauseConfirmSoundTrack1SxLRV[] =
{
	0xFF,
};

const uint16 AutomaticPauseConfirmSoundTrack1SxFQ[] =
{
	A_4, B_4, E_5
};

const uint8 AutomaticPauseConfirmSoundTrack1SxEV0[] =
{
	0x80,
};

const uint8 AutomaticPauseConfirmSoundTrack1SxEV1[] =
{
	0x01
};

const int8* const AutomaticPauseConfirmSoundTrack1SxRAM[] =
{
	SawtoothWaveForm,
};

const uint8 AutomaticPauseConfirmSoundTrack1SxSWP[] =
{
	0x00,
};

const SoundTrackKeyframe AutomaticPauseConfirmSoundTrack1Keyframes[] =
{
	{80, kSoundTrackEventStart},
	{80, kSoundTrackEventSxFQ},
	{80, kSoundTrackEventSxFQ},
	{0, kSoundTrackEventEnd},	
};

SoundTrackROMSpec AutomaticPauseConfirmSoundTrack1 =
{
	/// kTrackNative, kTrackPCM
	kTrackNative,

	/// Skip if no sound source available?
	false,

	/// Total number of samples (0 if not PCM)
	0,

	/// Keyframes that define the track
	(SoundTrackKeyframe*)AutomaticPauseConfirmSoundTrack1Keyframes,

	/// SxINT values
	(uint8*)AutomaticPauseConfirmSoundTrack1SxINT,

	/// SxLRV values
	(uint8*)AutomaticPauseConfirmSoundTrack1SxLRV,

	/// SxFQH and SxFQL values
	(uint16*)AutomaticPauseConfirmSoundTrack1SxFQ,

	/// SxEV0 values
	(uint8*)AutomaticPauseConfirmSoundTrack1SxEV0,

	/// SxEV1 values
	(uint8*)AutomaticPauseConfirmSoundTrack1SxEV1,

	/// SxRAM pointers
	(int8**)AutomaticPauseConfirmSoundTrack1SxRAM,

	/// SxSWP values
	(uint8*)AutomaticPauseConfirmSoundTrack1SxSWP,

	/// SxMOD values
	(int8**)NULL
};