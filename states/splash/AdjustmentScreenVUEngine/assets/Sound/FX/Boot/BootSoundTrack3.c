/*
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <SoundTrack.h>
#include <WaveForms.h>


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// DEFINITIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

const uint8 BootSoundTrack3SxINT[] =
{
	0x9F,
};

const uint8 BootSoundTrack3SxLRV[] =
{
	0xFF,
};

const uint16 BootSoundTrack3SxFQ[] =
{
	CS6, A_5, B_5,
};

const uint8 BootSoundTrack3SxEV0[] =
{
	0x80,
};

const uint8 BootSoundTrack3SxEV1[] =
{
	0x01
};

const int8* const BootSoundTrack3SxRAM[] =
{
	SquareWaveForm,
};

const uint8 BootSoundTrack3SxSWP[] =
{
	0x00,
};

const SoundTrackKeyframe BootSoundTrack3Keyframes[] =
{
	{60, kSoundTrackEventStart},
	{30, kSoundTrackEventSxFQ},
	{30, kSoundTrackEventSxFQ},
	{0, kSoundTrackEventEnd},	
};

SoundTrackROMSpec BootSoundTrack3 =
{
	/// kTrackNative, kTrackPCM
	kTrackNative,

	/// Skip if no sound source available?
	false,

	/// Total number of samples (0 if not PCM)
	0,

	/// Keyframes that define the track
	(SoundTrackKeyframe*)BootSoundTrack3Keyframes,

	/// SxINT values
	(uint8*)BootSoundTrack3SxINT,

	/// SxLRV values
	(uint8*)BootSoundTrack3SxLRV,

	/// SxFQH and SxFQL values
	(uint16*)BootSoundTrack3SxFQ,

	/// SxEV0 values
	(uint8*)BootSoundTrack3SxEV0,

	/// SxEV1 values
	(uint8*)BootSoundTrack3SxEV1,

	/// SxRAM pointers
	(int8**)BootSoundTrack3SxRAM,

	/// SxSWP values
	(uint8*)BootSoundTrack3SxSWP,

	/// SxMOD values
	(int8**)NULL
};