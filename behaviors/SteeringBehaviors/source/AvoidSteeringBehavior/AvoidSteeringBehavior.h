/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef AVOID_STEERING_BEHAVIOR_H_
#define AVOID_STEERING_BEHAVIOR_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <SteeringBehavior.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// FORWARD DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

class GameObject;
class VirtualList;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// A AvoidSteeringBehavior Spec
/// @memberof AvoidSteeringBehavior
typedef struct AvoidSteeringBehaviorSpec
{
	SteeringBehaviorSpec steeringBehaviorSpec;

	/// Maximum angle betwen vehicle and obstacle to account for
	fixed_t maximumAngle;

	/// Avoidance check distance modification percentage
	fixed_t avoidanceDetectionDistance;

	/// Minimum angle's cos to start braking
	fixed_t brakingMinimumAngleCos;

} AvoidSteeringBehaviorSpec;

/// A AvoidSteeringBehavior spec that is stored in ROM
/// @memberof AvoidSteeringBehavior
typedef const AvoidSteeringBehaviorSpec AvoidSteeringBehaviorROMSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class SeekSteeringBehavior
///
/// Inherits from Behavior
///
//  Implements a behavior that computes a steering force that avoids
/// obstacles.
class AvoidSteeringBehavior : SteeringBehavior
{
	/// Linked list of obstacles to avoid
	VirtualList obstacles;

	/// Class' constructor
	/// @param owner: GameObject to which the behavior attaches to
	/// @param seekSteeringBehaviorSpec: Specification that determines how to configure the behavior
	void constructor(GameObject owner, const AvoidSteeringBehaviorSpec* seekSteeringBehaviorSpec);

	/// Calculate the force vector to apply.
	/// @param owner: Vehicle that owns the steering behavior
	/// @return The force vector to apply to the provided vechile
	override Vector3D calculate(Vehicle owner);

	/// Add an obstacle to avoid.
	/// @param gameObject: Obstacle to avoid
	void addObstacle(GameObject gameObject);

	/// Remove all registerd obstacles.
	void removeAllObstacles();
}

#endif
