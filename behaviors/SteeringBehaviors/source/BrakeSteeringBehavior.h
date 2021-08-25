/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef BRAKE_STEERING_BEHAVIOR_H_
#define BRAKE_STEERING_BEHAVIOR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

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
	fix10_6 strength;

	void constructor(const BrakeSteeringBehaviorSpec* brakeSteeringBehaviorSpec);

	fix10_6 getStrength();
	void setStrength(fix10_6 value);

	override Vector3D calculate(Vehicle owner);
}


#endif
