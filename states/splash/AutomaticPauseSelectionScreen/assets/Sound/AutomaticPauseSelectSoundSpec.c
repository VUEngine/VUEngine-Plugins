/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <SoundManager.h>
#include <WaveForms.h>


//=========================================================================================================
// DEFINITIONS
//=========================================================================================================

const uint16 AutomaticPauseSelectTrack[] =
{
  CS4, PAU, ENDSOUND,
  100, 50, 1,
  15, 15, 15, 
};

SoundChannelConfigurationROM AutomaticPauseSelectSoundChannel1Configuration =
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
	SawtoothWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM AutomaticPauseSelectSoundChannel1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&AutomaticPauseSelectSoundChannel1Configuration,

	//// Total number of samples
	0,

	/// Sound track
	{
		(const uint8*)AutomaticPauseSelectTrack
	}
};


SoundChannelROM* const AutomaticPauseSelectSoundChannels[] =
{
	&AutomaticPauseSelectSoundChannel1,
	NULL
};

SoundROMSpec AutomaticPauseSelectSoundSpec =
{
	/// Name
	"Automatic Pause select",

	/// Play in loop
	false,

	/// Target timer resolution in us
	1000,

	/// Tracks
	(SoundChannel**)AutomaticPauseSelectSoundChannels
};