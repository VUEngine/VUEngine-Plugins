/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LOCALIZED_ACTOR_H_
#define LOCALIZED_ACTOR_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Actor.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// An LocalizedActor Spec
/// @memberof LocalizedActor
typedef struct LocalizedActorSpec
{
	ActorSpec actorSpec;

} LocalizedActorSpec;

/// A LocalizedActor spec that is stored in ROM
/// @memberof LocalizedActor
typedef const LocalizedActorSpec LocalizedActorROMSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class LocalizedActor
///
/// Inherits from Actor
///
/// Implements localized visual elements, where each animation represents one translation to another language.
class LocalizedActor : Actor
{
	/// @publicsection

	/// @param localizedActorSpec: Specification that determines how to configure the statefulActor
	/// @param internalId: ID to keep track internally of the new instance
	/// @param name: Name to assign to the new instance
	void constructor(const LocalizedActorSpec* localizedActorSpec, int16 internalId, const char* const name);

	/// Make the localized actor ready to start operating once it has been completely intialized.
	/// @param recursive: If true, the ready call is propagated to its children, grand children, etc.
	override void ready(bool recursive);
}

#endif
