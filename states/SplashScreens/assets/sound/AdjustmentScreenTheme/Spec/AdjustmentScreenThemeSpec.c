
/* VUEngine - Virtual Utopia Engine <https://www.vuengine.dev>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>, 2007-2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SoundManager.h>


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

#define ADJUSTMENT_SCREEN_THEME_SOUND_TRACK_1 ADJUSTMENT_SCREEN_THEME_SOUND_TRACK_1

extern const u8 ADJUSTMENT_SCREEN_THEME_SOUND_TRACK_1[];



#define ADJUSTMENT_SCREEN_THEME_SOUND_TRACK_1_LENGTH		730000

#define WAVE_1_AMPLITUDE			2
#define WAVE_2_AMPLITUDE			4
#define WAVE_3_AMPLITUDE			16
#define WAVE_4_AMPLITUDE			31
#define WAVE_5_AMPLITUDE			63
#define WAVE_6_AMPLITUDE			63

const s8 adjustmentScreenThemeWave1[32] =
{
	WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE,
	WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE,
	WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE,
	WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE, WAVE_1_AMPLITUDE,
};

const s8 adjustmentScreenThemeWave2[32] =
{
	WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE,
	WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE,
	WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE,
	WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE, WAVE_2_AMPLITUDE,
};

const s8 adjustmentScreenThemeWave3[32] =
{
	WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE,
	WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE,
	WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE,
	WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE, WAVE_3_AMPLITUDE,
};


const s8 adjustmentScreenThemeWave4[32] =
{
	WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE,
	WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE,
	WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE,
	WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE, WAVE_4_AMPLITUDE,
};

const s8 adjustmentScreenThemeWave5[32] =
{
	WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE,
	WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE,
	WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE,
	WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE, WAVE_5_AMPLITUDE,
};

const s8 adjustmentScreenThemeWave6[32] =
{
	WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE,
	WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE,
	WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE,
	WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE, WAVE_6_AMPLITUDE,
};

SoundChannelConfigurationROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_1_CONFIGURATION =
{
	/// kMIDI, kPCM
	kPCM,

	/// SxINT
	0x00,

	/// Volume SxLRV
	0x00,

	/// SxRAM (this is overrode by the SoundManager)
	0x00,

	/// SxEV0
	0xF0,

	/// SxEV1
	0x00,

	/// SxFQH
	0xFF,

	/// SxFQL
	0xFF,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	adjustmentScreenThemeWave1,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelConfigurationROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_2_CONFIGURATION =
{
	/// kMIDI, kPCM
	kPCM,

	/// SxINT
	0x00,

	/// Volume SxLRV
	0x00,

	/// SxRAM (this is overrode by the SoundManager)
	0x00,

	/// SxEV0
	0xF0,

	/// SxEV1
	0x00,

	/// SxFQH
	0xFF,

	/// SxFQL
	0xFF,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	adjustmentScreenThemeWave2,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelConfigurationROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_3_CONFIGURATION =
{
	/// kMIDI, kPCM
	kPCM,

	/// SxINT
	0x00,

	/// Volume SxLRV
	0x00,

	/// SxRAM (this is overrode by the SoundManager)
	0x00,

	/// SxEV0
	0xF0,

	/// SxEV1
	0x00,

	/// SxFQH
	0xFF,

	/// SxFQL
	0xFF,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	adjustmentScreenThemeWave3,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelConfigurationROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_4_CONFIGURATION =
{
	/// kMIDI, kPCM
	kPCM,

	/// SxINT
	0x00,

	/// Volume SxLRV
	0x00,

	/// SxRAM (this is overrode by the SoundManager)
	0x00,

	/// SxEV0
	0xF0,

	/// SxEV1
	0x00,

	/// SxFQH
	0xFF,

	/// SxFQL
	0xFF,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	adjustmentScreenThemeWave4,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelConfigurationROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_5_CONFIGURATION =
{
	/// kMIDI, kPCM
	kPCM,

	/// SxINT
	0x00,

	/// Volume SxLRV
	0x00,

	/// SxRAM (this is overrode by the SoundManager)
	0x00,

	/// SxEV0
	0xF0,

	/// SxEV1
	0x00,

	/// SxFQH
	0xFF,

	/// SxFQL
	0xFF,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	adjustmentScreenThemeWave5,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelConfigurationROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_6_CONFIGURATION =
{
	/// kMIDI, kPCM
	kPCM,

	/// SxINT
	0x00,

	/// Volume SxLRV
	0x00,

	/// SxRAM (this is overrode by the SoundManager)
	0x00,

	/// SxEV0
	0x70,

	/// SxEV1
	0x00,

	/// SxFQH
	0xFF,

	/// SxFQL
	0xFF,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	adjustmentScreenThemeWave6,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};


SoundChannelROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_1 =
{
	/// Configuration
	(SoundChannelConfiguration*) &ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		ADJUSTMENT_SCREEN_THEME_SOUND_TRACK_1
	}
};

SoundChannelROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_2 =
{
	/// Configuration
	(SoundChannelConfiguration*) &ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_2_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		ADJUSTMENT_SCREEN_THEME_SOUND_TRACK_1
	}
};

SoundChannelROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_3 =
{
	/// Configuration
	(SoundChannelConfiguration*) &ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_3_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		ADJUSTMENT_SCREEN_THEME_SOUND_TRACK_1
	}
};

SoundChannelROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_4 =
{
	/// Configuration
	(SoundChannelConfiguration*) &ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_4_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		ADJUSTMENT_SCREEN_THEME_SOUND_TRACK_1
	}
};

SoundChannelROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_5 =
{
	/// Configuration
	(SoundChannelConfiguration*) &ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_5_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		ADJUSTMENT_SCREEN_THEME_SOUND_TRACK_1
	}
};

SoundChannelROM ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_6 =
{
	/// Configuration
	(SoundChannelConfiguration*) &ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_6_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		ADJUSTMENT_SCREEN_THEME_SOUND_TRACK_1
	}
};

SoundChannelROM* ADJUSTMENT_SCREEN_THEME_SOUND_CHANNELS[] =
{
	&ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_1,
	&ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_2,
	&ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_3,
//	&ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_4,
//	&ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_5,
//	&ADJUSTMENT_SCREEN_THEME_SOUND_CHANNEL_1_6,
	NULL
};

SoundROM ADJUSTMENT_SCREEN_THEME_SOUND =
{
	/// Name
	"Adjunstment screen theme",

	/// Play in loop
	false,

	/// Target timer resolution in us
	0,

	/// Tracks
	(SoundChannel**)ADJUSTMENT_SCREEN_THEME_SOUND_CHANNELS
};