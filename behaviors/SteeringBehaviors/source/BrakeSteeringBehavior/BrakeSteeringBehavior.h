/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef BRAKE_STEERING_BEHAVIOR_H_
#define BRAKE_STEERING_BEHAVIOR_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <SteeringBehavior.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// A BrakeSteeringBehavior Spec
/// @memberof BrakeSteeringBehavior
typedef struct BrakeSteeringBehaviorSpec
{
	SteeringBehaviorSpec steeringBehaviorSpec;

} BrakeSteeringBehaviorSpec;

/// A BrakeSteeringBehavior spec that is stored in ROM
/// @memberof BrakeSteeringBehavior
typedef const BrakeSteeringBehaviorSpec BrakeSteeringBehaviorROMSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class BrakeSteeringBehavior
///
/// Inherits from SteeringBehavior
///
//  Implements a behavior that computes a steering force which will
//  stop a vehicle.
class BrakeSteeringBehavior : SteeringBehavior
{
	/// Force's magnitude
	fixed_t strength;

	/// Class' constructor
	/// @param owner: Entity to which the behavior attaches to
	/// @param brakeSteeringBehaviorSpec: Specification that determines how to configure the behavior
	void constructor(Entity owner, const BrakeSteeringBehaviorSpec* brakeSteeringBehaviorSpec);

	/// Calculate the force vector to apply.
	/// @param owner: Vehicle that owns the steering behavior
	/// @return The force vector to apply to the provided vechile
	override Vector3D calculate(Vehicle owner);

	/// Set the force's magnitude.
	/// @param strength: Force's magnitude
	void setStrength(fixed_t strength);

	/// Retrieve the force's magnitude.
	/// @return Force's magnitude
	fixed_t getStrength();
}

#endif
