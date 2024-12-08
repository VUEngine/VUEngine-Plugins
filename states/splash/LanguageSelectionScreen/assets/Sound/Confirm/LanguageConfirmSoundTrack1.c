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

const uint8 LanguageConfirmSoundTrack1SxINT[] =
{
	0x9F,
};

const uint8 LanguageConfirmSoundTrack1SxLRV[] =
{
	0xFF,
};

const uint16 LanguageConfirmSoundTrack1SxFQ[] =
{
	A_4, B_4, E_5
};

const uint8 LanguageConfirmSoundTrack1SxEV0[] =
{
	0x80,
};

const uint8 LanguageConfirmSoundTrack1SxEV1[] =
{
	0x01
};

const int8* const LanguageConfirmSoundTrack1SxRAM[] =
{
	SawtoothWaveForm,
};

const uint8 LanguageConfirmSoundTrack1SxSWP[] =
{
	0x00,
};

const SoundTrackKeyframe LanguageConfirmSoundTrack1Keyframes[] =
{
	{80, kSoundTrackEventStart},
	{80, kSoundTrackEventSxFQ},
	{80, kSoundTrackEventSxFQ},
	{0, kSoundTrackEventEnd},	
};

SoundTrackROMSpec LanguageConfirmSoundTrack1 =
{
	/// kTrackNative, kTrackPCM
	kTrackNative,

	/// Total number of samples (0 if not PCM)
	0,

	/// Keyframes that define the track
	(SoundTrackKeyframe*)LanguageConfirmSoundTrack1Keyframes,

	/// SxINT values
	(uint8*)LanguageConfirmSoundTrack1SxINT,

	/// SxLRV values
	(uint8*)LanguageConfirmSoundTrack1SxLRV,

	/// SxFQH and SxFQL values
	(uint16*)LanguageConfirmSoundTrack1SxFQ,

	/// SxEV0 values
	(uint8*)LanguageConfirmSoundTrack1SxEV0,

	/// SxEV1 values
	(uint8*)LanguageConfirmSoundTrack1SxEV1,

	/// SxRAM pointers
	(int8**)LanguageConfirmSoundTrack1SxRAM,

	/// S5SWP values
	(uint8*)LanguageConfirmSoundTrack1SxSWP
};