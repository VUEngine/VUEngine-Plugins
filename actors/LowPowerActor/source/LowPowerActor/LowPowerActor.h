/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LOW_POWER_ACTOR_H_
#define LOW_POWER_ACTOR_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Actor.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// An LowPowerActor Spec
/// @memberof LowPowerActor
typedef struct LowPowerActorSpec
{
	ActorSpec actorSpec;

} LowPowerActorSpec;

/// A LowPowerActor spec that is stored in ROM
/// @memberof LowPowerActor
typedef const LowPowerActorSpec LowPowerActorROMSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class LowPowerActor
///
/// Inherits from Actor
///
/// Implements localized visual elements, where each animation represents one translation to another
/// language.
class LowPowerActor : Actor
{
	/// @param lowPowerActorSpec: Specification that determines how to configure the actor
	/// @param internalId: ID to keep track internally of the new instance
	/// @param name: Name to assign to the new instance
	void constructor
	(
		const LowPowerActorSpec* lowPowerActorSpec, int16 internalId, const char* const name
	);
}

#endif
