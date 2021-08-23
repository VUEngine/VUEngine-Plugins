/*
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LOW_POWER_ENTITY_H_
#define LOW_POWER_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <Body.h>
#include "../config.h"


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

typedef const AnimatedEntitySpec LowPowerEntitySpec;
typedef const LowPowerEntitySpec LowPowerEntityROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

class LowPowerEntity : AnimatedEntity
{
	// number of seconds of receiving the low power signal
	u8 lowPowerDuration;

	void constructor(const LowPowerEntitySpec* LowPowerEntitySpec, s16 internalId, const char* const name);
}


#endif
