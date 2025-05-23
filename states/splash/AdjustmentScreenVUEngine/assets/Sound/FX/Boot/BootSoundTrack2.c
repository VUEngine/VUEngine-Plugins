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

#include <SoundTrack.h>
#include <WaveForms.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// DEFINITIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const uint8 BootSoundTrack2SxINT[] =
{
	0x9F,
};

const uint8 BootSoundTrack2SxLRV[] =
{
	0xFF,
};

const uint16 BootSoundTrack2SxFQ[] =
{
	E_6, CS6, DS6,
};

const uint8 BootSoundTrack2SxEV0[] =
{
	0x80,
};

const uint8 BootSoundTrack2SxEV1[] =
{
	0x01
};

const int8* const BootSoundTrack2SxRAM[] =
{
	SawWaveForm,
};

const uint8 BootSoundTrack2SxSWP[] =
{
	0x00,
};

const SoundTrackKeyframe BootSoundTrack2Keyframes[] =
{
	{60, kSoundTrackEventStart},
	{30, kSoundTrackEventSxFQ},
	{30, kSoundTrackEventSxFQ},
	{0, kSoundTrackEventEnd},	
};

SoundTrackROMSpec BootSoundTrack2 =
{
	/// kTrackNative, kTrackPCM
	kTrackNative,

	/// Skip if no sound source available?
	false,

	/// Total number of samples (0 if not PCM)
	0,

	/// Loop back point (cursor)
	0,

	/// Keyframes that define the track
	(SoundTrackKeyframe*)BootSoundTrack2Keyframes,

	/// SxINT values
	(uint8*)BootSoundTrack2SxINT,

	/// SxLRV values
	(uint8*)BootSoundTrack2SxLRV,

	/// SxFQH and SxFQL values
	(uint16*)BootSoundTrack2SxFQ,

	/// SxEV0 values
	(uint8*)BootSoundTrack2SxEV0,

	/// SxEV1 values
	(uint8*)BootSoundTrack2SxEV1,

	/// SxRAM pointers
	(int8**)BootSoundTrack2SxRAM,

	/// SxSWP values
	(uint8*)BootSoundTrack2SxSWP,

	/// SxMOD values
	(int8**)NULL
};