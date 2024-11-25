/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef BRAKE_STEERING_BEHAVIOR_H_
#define BRAKE_STEERING_BEHAVIOR_H_


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <SteeringBehavior.h>


//---------------------------------------------------------------------------------------------------------
//											 DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// defines an entity in ROM memory
typedef struct BrakeSteeringBehaviorSpec
{
	SteeringBehaviorSpec steeringBehaviorSpec;

} BrakeSteeringBehaviorSpec;

typedef const BrakeSteeringBehaviorSpec BrakeSteeringBehaviorROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

//  Given a target, this behavior returns a steering force which will
//  direct the agent towards the target

/// @ingroup base
class BrakeSteeringBehavior : SteeringBehavior
{
	fixed_t strength;

	void constructor(SpatialObject owner, const BrakeSteeringBehaviorSpec* brakeSteeringBehaviorSpec);

	fixed_t getStrength();
	void setStrength(fixed_t value);

	override Vector3D calculate(Vehicle owner);
}


#endif
