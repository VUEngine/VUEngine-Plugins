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

#include <DisplayUnit.h>
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

/// Pointer to the hardware's sound registers
static SoundSource* _soundSources = (SoundSource*)__SOUND_SOURCES_ADRESS;

/// Pointer to the spec
static const PCMSoundSpec* _pcmSoundSpec = NULL;

/// Elapsed time during playback
static uint32 _elapsedMicroseconds = 0;

/// Counter to keep track of the playback's frequency
static uint16 _samplesPerSecond = 0;


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static bool PCMSoundPlayer::playSound(const PCMSoundSpec* pcmSoundSpec, ListenerObject scope)
{
	PCMSoundPlayer pcmSoundPlayer = PCMSoundPlayer::getInstance();

	if(NULL == pcmSoundSpec)
	{
		return false;
	}

	if(NULL != pcmSoundSpec)
	{
		SoundUnit::stopAllSounds();

		_pcmSoundSpec = pcmSoundSpec;
		_samplesPerSecond = 0;
		_elapsedMicroseconds = 0;

		if(!isDeleted(scope))
		{
			PCMSoundPlayer::addEventListener(pcmSoundPlayer, scope, kEventSoundFinished);
		}

		PCMSoundPlayer::configureSoundSources();
		Timer::configure(pcmSoundSpec->timerConfig);
		Timer::addEventListener(Timer::getInstance(), ListenerObject::safeCast(pcmSoundPlayer), kEventTimerInterrupt);
		DisplayUnit::enableMultiplexedInterrupts(kVIPOnlyNonVIPMultiplexedInterrupts);

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
	_elapsedMicroseconds = 0;
	PCMSoundPlayer pcmSoundPlayer = PCMSoundPlayer::getInstance();

	DisplayUnit::enableMultiplexedInterrupts(kVIPNoMultiplexedInterrupts);
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
			_samplesPerSecond++;
			bool playing = PCMSoundPlayer::update(Timer::getMicrosecondsPerInterrupt());

#ifdef __PROFILE_PCM_PLAYBACK
			if(!playing)
			{
				FrameRate::removeEventListener(FrameRate::getInstance(), ListenerObject::safeCast(this), kEventFramerateReady);
			}
#endif
			if(!playing)
			{
				PCMSoundPlayer::fireEvent(this, kEventSoundFinished);
			}

			return playing;
		}

		case kEventFramerateReady:
		{
			PCMSoundPlayer::printStats(1, 0);
			return true;
		}
	}

	return Base::onEvent(this, eventFirer, eventCode);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static bool PCMSoundPlayer::update(uint32 elapsedMicroseconds)
{
	if(NULL == _pcmSoundSpec)
	{
		return false;
	}

	_elapsedMicroseconds += elapsedMicroseconds;

 	uint32 cursor = _elapsedMicroseconds / _pcmSoundSpec->targetPCMUpdates;

	if(cursor >= _pcmSoundSpec->samples)
	{
		if(_pcmSoundSpec->loop)
		{
			_elapsedMicroseconds = 0;
			cursor = 0;
		}
		else
		{
			return false;
		}
	}

	int8 sample = _pcmSoundSpec->SxLRV[cursor];
	int16 vsuSoundSourceIndex = 0;

#ifndef __RELEASE
	if(__TOTAL_POTENTIAL_NORMAL_CHANNELS * __MAXIMUM_VOLUME < sample)
	{
		sample = __TOTAL_POTENTIAL_NORMAL_CHANNELS * __MAXIMUM_VOLUME - 1;
	}
#endif

	do
	{
		if(__MAXIMUM_VOLUME <= sample)
		{
			_soundSources[vsuSoundSourceIndex].SxLRV = 0xFF;
			sample -= __MAXIMUM_VOLUME;
		}
		else
		{
			_soundSources[vsuSoundSourceIndex].SxLRV = ((sample << 4) | sample);
			sample = 0;
		}
		
	} while(++vsuSoundSourceIndex < __TOTAL_POTENTIAL_NORMAL_CHANNELS);

	return true;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static void PCMSoundPlayer::configureSoundSources()
{
	__SSTOP = 0x01;

	uint8* wave = (uint8*)__WAVE_ADDRESS(0);

	// Set the wave data
	for(uint32 i = 0; i < 32; i++)
	{
		wave[(i << 2)] = 63;
	}

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
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static void PCMSoundPlayer::printStats(int x, int y)
{
//	PRINT_TEXT("TIMER STATUS", x, y++);
	PRINT_TEXT("Inter./sec.:          ", x, y);
	PRINT_INT(_samplesPerSecond, x + 17, y);
	PRINT_INT(_elapsedMicroseconds, x + 27, y);

	_samplesPerSecond = 0;
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
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PCMSoundPlayer::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————