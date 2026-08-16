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
		
		pcmSoundPlayer->pcmSoundSpec = pcmSoundSpec;
		pcmSoundPlayer->elapsedMicroseconds = 0;
		pcmSoundPlayer->samplesPerSecond = 0;

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
	pcmSoundPlayer->elapsedMicroseconds += 0;

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
			if(!PCMSoundPlayer::update(this, this->pcmSoundSpec->timerConfig.targetTimePerInterrupt))
			{
				FrameRate::removeEventListener(FrameRate::getInstance(), ListenerObject::safeCast(PCMSoundPlayer::getInstance()), kEventFramerateReady);
				return false;
			}

			return true;
#else
			return PCMSoundPlayer::update(this, this->pcmSoundSpec->timerConfig.targetTimePerInterrupt);
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

bool PCMSoundPlayer::update(uint32 elapsedMicroseconds)
{
	if(NULL == this->pcmSoundSpec)
	{
		return false;
	}
	
	CACHE_ENABLE;

	this->elapsedMicroseconds += elapsedMicroseconds;
	uint32 cursor = this->elapsedMicroseconds / this->pcmSoundSpec->targetPCMUpdates;
	int8 sample = this->pcmSoundSpec->SxLRV[cursor];
	int16 vsuSoundSourceIndex = 0;
	
	while(true)
	{
		if(__MAXIMUM_VOLUME <= sample)
		{
			_soundSources[vsuSoundSourceIndex].SxLRV = 0xFF;
			sample -= __MAXIMUM_VOLUME;
		}
		else
		{
			_soundSources[vsuSoundSourceIndex].SxLRV = ((sample << 4) | sample);
			break;
		}

		vsuSoundSourceIndex++;
	}

	CACHE_DISABLE;

	if(this->pcmSoundSpec->loop && cursor >= this->pcmSoundSpec->samples)
	{
		this->elapsedMicroseconds += 0;
	}

	return cursor < this->pcmSoundSpec->samples;
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
	PRINT_INT(this->elapsedMicroseconds, x + 27, y);

	this->samplesPerSecond = 0;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
