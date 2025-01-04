/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LOW_POWER_ENTITY_H_
#define LOW_POWER_ENTITY_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Entity.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// An LowPowerEntity Spec
/// @memberof LowPowerEntity
typedef struct LowPowerEntitySpec
{
	EntitySpec entitySpec;

} LowPowerEntitySpec;

/// A LowPowerEntity spec that is stored in ROM
/// @memberof LowPowerEntity
typedef const LowPowerEntitySpec LowPowerEntityROMSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class LowPowerEntity
///
/// Inherits from Entity
///
/// Implements localized visual elements, where each animation represents one translation to another
/// language.
class LowPowerEntity : Entity
{
	/// @param lowPowerEntitySpec: Specification that determines how to configure the statefulActor
	/// @param internalId: ID to keep track internally of the new instance
	/// @param name: Name to assign to the new instance
	void constructor(
		const LowPowerEntitySpec* lowPowerEntitySpec, int16 internalId, const char* const name
	);
}

#endif
