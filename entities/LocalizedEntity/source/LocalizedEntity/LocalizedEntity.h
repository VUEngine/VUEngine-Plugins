/*
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LOCALIZED_ENTITY_H_
#define LOCALIZED_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <Body.h>
#include <Events.h>


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

typedef const AnimatedEntitySpec LocalizedEntitySpec;
typedef const LocalizedEntitySpec LocalizedEntityROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

class LocalizedEntity : AnimatedEntity
{
	void constructor(const LocalizedEntitySpec* localizedEntitySpec, s16 internalId, const char* const name);
	override void ready(bool recursive);
}


#endif
