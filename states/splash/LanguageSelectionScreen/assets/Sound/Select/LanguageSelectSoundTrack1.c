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

const uint8 LanguageSelectSoundTrack1SxINT[] =
{
	0x9F,
};

const uint8 LanguageSelectSoundTrack1SxLRV[] =
{
	0xFF,
};

const uint16 LanguageSelectSoundTrack1SxFQ[] =
{
	G_4
};

const uint8 LanguageSelectSoundTrack1SxEV0[] =
{
	0xF0,
};

const uint8 LanguageSelectSoundTrack1SxEV1[] =
{
	0x00, 0x01
};

const WaveformData* const LanguageSelectSoundTrack1SxRAM[] =
{
	NULL,
};

const uint8 LanguageSelectSoundTrack1SxSWP[] =
{
	0x00,
};

const SoundTrackKeyframe LanguageSelectSoundTrack1Keyframes[] =
{
	{40, kSoundTrackEventStart},
	{40, kSoundTrackEventSxEV1},
	{0, kSoundTrackEventEnd},	
};

SoundTrackROMSpec LanguageSelectSoundTrack1 =
{
	/// Priority for sound channel usage
	1,

	/// Skip if no sound source available?
	false,

	/// Total number of samples (0 if not PCM)
	0,

	/// Loop back point (cursor)
	0,

	/// Keyframes that define the track
	(SoundTrackKeyframe*)LanguageSelectSoundTrack1Keyframes,

	/// SxINT values
	(uint8*)LanguageSelectSoundTrack1SxINT,

	/// SxLRV values
	(uint8*)LanguageSelectSoundTrack1SxLRV,

	/// SxFQH and SxFQL values
	(uint16*)LanguageSelectSoundTrack1SxFQ,

	/// SxEV0 values
	(uint8*)LanguageSelectSoundTrack1SxEV0,

	/// SxEV1 values
	(uint8*)LanguageSelectSoundTrack1SxEV1,

	/// SxRAM pointers
	(WaveformData**)LanguageSelectSoundTrack1SxRAM,

	/// SxSWP values
	(uint8*)LanguageSelectSoundTrack1SxSWP,

	/// SxMOD values
	(int8**)NULL
};