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

const uint8 PrecautionScreenIntroSoundTrack1SxINT[] =
{
	0x9F,
};

const uint8 PrecautionScreenIntroSoundTrack1SxLRV[] =
{
	0xFF,
};

const uint16 PrecautionScreenIntroSoundTrack1SxFQ[] =
{
	CS4, F_5
};

const uint8 PrecautionScreenIntroSoundTrack1SxEV0[] =
{
	0xF0,
};

const uint8 PrecautionScreenIntroSoundTrack1SxEV1[] =
{
	0x00, 0x01
};

const int8* const PrecautionScreenIntroSoundTrack1SxRAM[] =
{
	SquareWaveForm,
};

const uint8 PrecautionScreenIntroSoundTrack1SxSWP[] =
{
	0x00,
};

const SoundTrackKeyframe PrecautionScreenIntroSoundTrack1Keyframes[] =
{
	{80, kSoundTrackEventStart},
	{80, kSoundTrackEventSxFQ | kSoundTrackEventSxEV1},
	{0, kSoundTrackEventEnd},	
};

SoundTrackROMSpec PrecautionScreenIntroSoundTrack1 =
{
	/// kTrackNative, kTrackPCM
	kTrackNative,

	/// Skip if no sound source available?
	false,

	/// Total number of samples (0 if not PCM)
	0,

	/// Keyframes that define the track
	(SoundTrackKeyframe*)PrecautionScreenIntroSoundTrack1Keyframes,

	/// SxINT values
	(uint8*)PrecautionScreenIntroSoundTrack1SxINT,

	/// SxLRV values
	(uint8*)PrecautionScreenIntroSoundTrack1SxLRV,

	/// SxFQH and SxFQL values
	(uint16*)PrecautionScreenIntroSoundTrack1SxFQ,

	/// SxEV0 values
	(uint8*)PrecautionScreenIntroSoundTrack1SxEV0,

	/// SxEV1 values
	(uint8*)PrecautionScreenIntroSoundTrack1SxEV1,

	/// SxRAM pointers
	(int8**)PrecautionScreenIntroSoundTrack1SxRAM,

	/// S5SWP values
	(uint8*)PrecautionScreenIntroSoundTrack1SxSWP
};
