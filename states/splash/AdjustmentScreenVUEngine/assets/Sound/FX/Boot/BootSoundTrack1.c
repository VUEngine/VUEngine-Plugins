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

const uint8 BootSoundTrack1SxINT[] =
{
	0x9F,
};

const uint8 BootSoundTrack1SxLRV[] =
{
	0xFF,
};

const uint16 BootSoundTrack1SxFQ[] =
{
	A_6, E_6, FS6
};

const uint8 BootSoundTrack1SxEV0[] =
{
	0x80,
};

const uint8 BootSoundTrack1SxEV1[] =
{
	0x00
};

const WaveformData* const BootSoundTrack1SxRAM[] =
{
	NULL,
};

const uint8 BootSoundTrack1SxSWP[] =
{
	0x00,
};

const SoundTrackKeyframe BootSoundTrack1Keyframes[] =
{
	{60, kSoundTrackEventStart},
	{30, kSoundTrackEventSxFQ},
	{30, kSoundTrackEventSxFQ},
	{0, kSoundTrackEventEnd},	
};

SoundTrackROMSpec BootSoundTrack1 =
{
	/// Priority for sound channel usage
	1,

	/// Skip if no sound source available?
	false,

	/// Loop back point (cursor)
	0,

	/// Keyframes that define the track
	(SoundTrackKeyframe*)BootSoundTrack1Keyframes,

	/// SxINT values
	(uint8*)BootSoundTrack1SxINT,

	/// SxLRV values
	(uint8*)BootSoundTrack1SxLRV,

	/// SxFQH and SxFQL values
	(uint16*)BootSoundTrack1SxFQ,

	/// SxEV0 values
	(uint8*)BootSoundTrack1SxEV0,

	/// SxEV1 values
	(uint8*)BootSoundTrack1SxEV1,

	/// SxRAM pointers
	(WaveformData**)BootSoundTrack1SxRAM,

	/// SxSWP values
	(uint8*)BootSoundTrack1SxSWP,

	/// SxMOD values
	(int8**)NULL
};