/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LOCALIZED_ENTITY_H_
#define LOCALIZED_ENTITY_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <AnimatedEntity.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// An LocalizedEntity Spec
/// @memberof LocalizedEntity
typedef struct LocalizedEntitySpec
{
	AnimatedEntitySpec animatedEntitySpec;

} LocalizedEntitySpec;

/// A LocalizedEntity spec that is stored in ROM
/// @memberof LocalizedEntity
typedef const LocalizedEntitySpec LocalizedEntityROMSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

///
/// Class LocalizedEntity
///
/// Inherits from AnimatedEntity
///
/// Implements localized visual elements, where each animation represents one translation to another language.
class LocalizedEntity : AnimatedEntity
{
	/// @publicsection

	/// @param localizedEntitySpec: Specification that determines how to configure the actor
	/// @param internalId: ID to keep track internally of the new instance
	/// @param name: Name to assign to the new instance
	void constructor(const LocalizedEntitySpec* localizedEntitySpec, int16 internalId, const char* const name);

	/// Make the localized entity ready to start operating once it has been completely intialized.
	/// @param recursive: If true, the ready call is propagated to its children, grand children, etc.
	override void ready(bool recursive);
}

#endif
