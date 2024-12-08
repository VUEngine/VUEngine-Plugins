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

#include <MIDI.h>
#include <SoundTrack.h>
#include <WaveForms.h>


//=========================================================================================================
// DEFINITIONS
//=========================================================================================================

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

const int8* const LanguageSelectSoundTrack1SxRAM[] =
{
	SawtoothWaveForm,
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
	/// kTrackNative, kTrackPCM
	kTrackNative,

	/// Total number of samples (0 if not PCM)
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
	(int8**)LanguageSelectSoundTrack1SxRAM,

	/// S5SWP values
	(uint8*)LanguageSelectSoundTrack1SxSWP
};