/*
 * VUEngine Core
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PCM_SOUND_PLAYER_H_
#define PCM_SOUND_PLAYER_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <ListenerObject.h>
#include <Sound.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' MACROS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#define __DEFAULT_PCM_HZ					8000

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// A Sound spec
/// @memberof Sound
typedef struct PCMSoundSpec
{
	/// Timer configuration
    TimerConfig timerConfig;

	/// Name
	char* name;

	/// Author's name
	char* author;

	/// Play in loop
	bool loop;

	/// Total number of samples (0 if not PCM)
	uint32 samples;

	/// Target PCM cycles per game cycle
	uint32 targetPCMUpdates;

	/// SxLRV values
	uint8* SxLRV;

} PCMSoundSpec;

/// A PCMSound spec that is stored in ROM
/// @memberof PCMSound
typedef const PCMSoundSpec PCMSoundROMSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class PCMSoundPlayer
///
/// Inherits from ListenerObject
///
/// Plays PCM Data.
singleton class PCMSoundPlayer : ListenerObject
{
	/// @protectedsection

	/// Pointer to the spec
	const PCMSoundSpec* pcmSoundSpec;

	/// Total elapsed time
	fix7_9_ext elapsedMicroseconds;

	/// Counter to keep track of the playback's frequency
	uint16 samplesPerSecond;

	/// If raised, no petitions to play a sound are processed
	bool lock;

	/// @publicsection

	/// Play a sound defined by the provided spec.
	/// @param pcmSoundSpec: Spec that defines the sound to play
	static bool playSound(const PCMSoundSpec* pcmSoundSpec);

	/// Mute playing sound.
	static void mute();

	/// Unmute playing sound.
	static void unmute();

	/// Rewind playing sound.
	static void rewind();

	/// Stop playing sound.
	static void stop();
	
	/// Process an event that the instance is listen for.
	/// @param eventFirer: ListenerObject that signals the event
	/// @param eventCode: Code of the firing event
	/// @return False if the listener has to be removed; true to keep it
	override bool onEvent(ListenerObject eventFirer, uint16 eventCode);
}

#endif
