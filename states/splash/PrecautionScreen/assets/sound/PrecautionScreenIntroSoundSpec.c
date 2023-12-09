/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SoundManager.h>
#include <WaveForms.h>


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

const uint16 PrecautionScreenIntroTrack[] =
{
  CS4, PAU, ENDSOUND,
  100, 50, 1,
  15, 15, 15, 
};

SoundChannelConfigurationROM PrecautionScreenIntroSoundChannel1Configuration =
{
	/// kMIDI, kPCM
	kMIDI,

	/// SxINT
	0x9F,

	/// Volume SxLRV
	0xFF,

	/// SxRAM (this is overrode by the SoundManager)
	0x00,

	/// SxEV0
	0xF0,

	/// SxEV1
	0x01,

	/// SxFQH
	0x00,

	/// SxFQL
	0x00,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	NULL,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM PrecautionScreenIntroSoundChannel1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&PrecautionScreenIntroSoundChannel1Configuration,

	//// Total number of samples
	0,

	/// Sound track
	{
		(const uint8*)PrecautionScreenIntroTrack
	}
};


SoundChannelROM* const PrecautionScreenIntroSoundChannels[] =
{
	&PrecautionScreenIntroSoundChannel1,
	NULL
};

SoundROM PrecautionScreenIntroSound =
{
	/// Name
	"Boot",

	/// Play in loop
	false,

	/// Target timer resolution in us
	1000,

	/// Tracks
	(SoundChannel**)PrecautionScreenIntroSoundChannels
};
