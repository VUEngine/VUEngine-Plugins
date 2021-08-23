/*
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
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

#include <MIDI.h>

const u16 LangSelectTrack[] =
{
  CS4, PAU, ENDSOUND,
  100, 50, 1,
  15, 15, 15, 
};

SoundChannelConfigurationROM LANG_SELECT_SND_CHANNEL_1_CONFIGURATION =
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
	sawtoothWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM LANG_SELECT_SND_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&LANG_SELECT_SND_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const u8*)LangSelectTrack
	}
};


SoundChannelROM* LANG_SELECT_SND_CHANNELS[] =
{
	&LANG_SELECT_SND_CHANNEL_1,
	NULL
};

SoundROM LANG_SELECT_SND =
{
	/// Name
	"Language select",

	/// Play in loop
	false,

	/// Target timer resolution in us
	1000,

	/// Tracks
	(SoundChannel**)LANG_SELECT_SND_CHANNELS
};