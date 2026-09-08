/*
 * VUEngine Core
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <FrameRate.h>
#include <Platform.h>
#include <Printer.h>
#include <Singleton.h>
#include <SoundUnit.h>
#include <WaveForms.h>

#include "PCMSoundPlayer.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' MACROS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#define AUDIO_INTERRUPT_OVERHEAD_BASE_US			11.0f
#define AUDIO_INTERRUPT_OVERHEAD_FACTOR				100.0f

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' ATTRIBUTES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static SoundSource* _soundSources = (SoundSource*)__SOUND_SOURCES_ADRESS;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static bool PCMSoundPlayer::playSound(const PCMSoundSpec* pcmSoundSpec)
{
	PCMSoundPlayer pcmSoundPlayer = PCMSoundPlayer::getInstance();

	if(pcmSoundPlayer->lock || NULL == pcmSoundSpec)
	{
		return false;
	}

	if(NULL != pcmSoundSpec)
	{
		SoundUnit::stopAllSounds();

		float overhead = AUDIO_INTERRUPT_OVERHEAD_FACTOR / pcmSoundSpec->timerConfig.targetTimePerInterrupt;
		overhead = overhead * overhead;

		uint16 adjustedTimePerInterrupt = pcmSoundSpec->timerConfig.targetTimePerInterrupt + AUDIO_INTERRUPT_OVERHEAD_BASE_US / overhead;
		
		pcmSoundPlayer->pcmSoundSpec = pcmSoundSpec;
		pcmSoundPlayer->samplesPerSecond = 0;
		pcmSoundPlayer->step = __F_TO_FIX7_9_EXT(adjustedTimePerInterrupt * (float)pcmSoundSpec->targetPCMUpdates / __MICROSECONDS_PER_SECOND);
		pcmSoundPlayer->cursor = 0;

		PCMSoundPlayer::configureSoundSources(pcmSoundPlayer);
#ifdef __RELEASE
		Timer::configure(pcmSoundSpec->timerConfig);
#endif
		Timer::addEventListener(Timer::getInstance(), ListenerObject::safeCast(pcmSoundPlayer), kEventTimerInterrupt);
#ifdef __PROFILE_PCM_PLAYBACK
		FrameRate::addEventListener(FrameRate::getInstance(), ListenerObject::safeCast(PCMSoundPlayer::getInstance()), kEventFramerateReady);
#endif
		return true;
	}

	return false;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static void PCMSoundPlayer::stop()
{
	PCMSoundPlayer pcmSoundPlayer = PCMSoundPlayer::getInstance();
	pcmSoundPlayer->cursor = 0;

	Timer::removeEventListener(Timer::getInstance(), ListenerObject::safeCast(pcmSoundPlayer), kEventTimerInterrupt);
#ifdef __PROFILE_PCM_PLAYBACK
	FrameRate::removeEventListener(FrameRate::getInstance(), ListenerObject::safeCast(PCMSoundPlayer::getInstance()), kEventFramerateReady);
#endif
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool PCMSoundPlayer::onEvent(ListenerObject eventFirer, uint16 eventCode)
{
	switch(eventCode)
	{
		case kEventTimerInterrupt:
		{
			this->samplesPerSecond++;
#ifdef __PROFILE_PCM_PLAYBACK
			if(!PCMSoundPlayer::update(this))
			{
				FrameRate::removeEventListener(FrameRate::getInstance(), ListenerObject::safeCast(PCMSoundPlayer::getInstance()), kEventFramerateReady);
				return false;
			}

			return true;
#else
			return PCMSoundPlayer::update(this);
#endif
		}

		case kEventFramerateReady:
		{
			PCMSoundPlayer::printStats(this, 1, 0);
			return true;
		}
	}

	return Base::onEvent(this, eventFirer, eventCode);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PCMSoundPlayer::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	this->pcmSoundSpec = NULL;
	this->lock = false;
	this->samplesPerSecond = 0;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PCMSoundPlayer::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool PCMSoundPlayer::update()
{
	if(NULL == this->pcmSoundSpec)
	{
		return false;
	}
	
	CACHE_ENABLE;

	uint32 cursor = __FIX7_9_EXT_TO_I(this->cursor);

	if(cursor >= this->pcmSoundSpec->samples)
	{
		if(this->pcmSoundSpec->loop)
		{
			this->cursor = 0;
			cursor = 0;
		}
		else
		{
			return false;
		}
	}

	this->cursor += this->step;

	int8 sample = this->pcmSoundSpec->SxLRV[cursor];
	int16 vsuSoundSourceIndex = 0;

	if(__TOTAL_POTENTIAL_NORMAL_CHANNELS * __MAXIMUM_VOLUME < sample)
	{
		sample = __TOTAL_POTENTIAL_NORMAL_CHANNELS * __MAXIMUM_VOLUME - 1;
	}

	do
	{
		if(__MAXIMUM_VOLUME <= sample)
		{
			_soundSources[vsuSoundSourceIndex].SxLRV = 0xFF;
		}
		else if(0 < sample)
		{
			_soundSources[vsuSoundSourceIndex].SxLRV = ((sample << 4) | sample);
		}
		else
		{
			_soundSources[vsuSoundSourceIndex].SxLRV = 0;
		}

		sample -= __MAXIMUM_VOLUME;

	} while(++vsuSoundSourceIndex < __TOTAL_POTENTIAL_NORMAL_CHANNELS);

	CACHE_DISABLE;

	return true;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PCMSoundPlayer::configureSoundSources()
{
	__SSTOP = 0x01;

	for(int16 i = 0; i < __TOTAL_SOUND_SOURCES; i++)
	{
		_soundSources[i].SxLRV = 0;
		_soundSources[i].SxFQL = 0;
		_soundSources[i].SxFQH = 0;
		_soundSources[i].SxEV0 = 0;
		_soundSources[i].SxEV1 = 0;
		_soundSources[i].SxRAM = 0;
		_soundSources[i].SxSWP = 0;
		_soundSources[i].SxINT = 0;
	}

	for(int16 i = 0; i < __TOTAL_POTENTIAL_NORMAL_CHANNELS; i++)
	{
		_soundSources[i].SxLRV = 0;
		_soundSources[i].SxFQL = 0;
		_soundSources[i].SxFQH = 0;
		_soundSources[i].SxEV0 = 0xF0;
		_soundSources[i].SxEV1 = 0;
		_soundSources[i].SxRAM = 0;
		_soundSources[i].SxSWP = 0;
		_soundSources[i].SxINT = 0x80;
	}

	uint8* wave = (uint8*)__WAVE_ADDRESS(0);

	// Set the wave data
	for(uint32 i = 0; i < 32; i++)
	{
		wave[(i << 2)] = 63;
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PCMSoundPlayer::printStats(int x, int y)
{
//	PRINT_TEXT("TIMER STATUS", x, y++);
	PRINT_TEXT("Inter./sec.:          ", x, y);
	PRINT_INT(this->samplesPerSecond, x + 17, y);
	PRINT_INT(this->cursor, x + 27, y);

	this->samplesPerSecond = 0;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
