/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
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
	void constructor(const LowPowerEntitySpec* LowPowerEntitySpec, int16 internalId, const char* const name);
}


#endif
