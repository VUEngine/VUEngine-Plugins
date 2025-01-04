/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef SEEK_STEERING_BEHAVIOR_H_
#define SEEK_STEERING_BEHAVIOR_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <SteeringBehavior.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// A SeekSteeringBehavior Spec
/// @memberof SeekSteeringBehavior
typedef struct SeekSteeringBehaviorSpec
{
	SteeringBehaviorSpec steeringBehaviorSpec;

	/// Distance when it is considered that the target has been reached
	fixed_t reachedDistanceThreshold;

	/// Distance when easing starts to apply to the computed force
	fixed_t easingDistanceThreshold;

} SeekSteeringBehaviorSpec;

/// A SeekSteeringBehavior spec that is stored in ROM
/// @memberof SeekSteeringBehavior
typedef const SeekSteeringBehaviorSpec SeekSteeringBehaviorROMSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class SeekSteeringBehavior
///
/// Inherits from SteeringBehavior
///
/// Implements a behavior that returns a steering force which will
/// direct the agent towards a target.
class SeekSteeringBehavior : SteeringBehavior
{
	/// Target to steer the vehicle towards
	Vector3D target;

	/// Threshold to start easing the computed force
	fixed_t easingDistanceThreshold;

	/// Squared threshold to detect if the target has been reached
	fixed_ext_t squaredReachedDistanceThreshold;

	/// If true, the force is gradually reduced when approaching the target
	bool slowDownWhenReachingTarget;

	/// If true, the target has been reached
	bool reachedTarget;

	/// If true, easing of the computed force is enabled
	bool allowEasing;

	/// Class' constructor
	/// @param owner: Entity to which the behavior attaches to
	/// @param seekSteeringBehaviorSpec: Specification that determines how to configure the behavior
	void constructor(Entity owner, const SeekSteeringBehaviorSpec* seekSteeringBehaviorSpec);

	/// Calculate the force vector to apply.
	/// @param owner: Vehicle that owns the steering behavior
	/// @return The force vector to apply to the provided vechile
	override Vector3D calculate(Vehicle owner);

	/// Set the target.
	/// @param target: Target to seek to
	void setTarget(Vector3D target);

	/// Retrieve the target.
	/// @return Target to seek to
	Vector3D getTarget();
	
	/// Set the squared threshold to detect if the target has been reached.
	/// @param reachedDistanceThreshold: Threshold to detect if the target has been reached
	void setReachedDistanceThreshold(fixed_t reachedDistanceThreshold);

	/// Retrieve the threshold to detect if the target has been reached.
	/// @return Threshold to detect if the target has been reached
	fixed_t getReachedDistanceThreshold();

	/// Set the threshold to start easing the computed force.
	/// @param easingDistanceThreshold: Threshold to start easing the computed force
	void setEasingDistanceThreshold(fixed_t easingDistanceThreshold);

	/// Retrieve the threshold to start easing the computed force.
	/// @return Threshold to start easing the computed force
	fixed_t getEasingDistanceThreshold();

	/// Allow/prevent if the force is gradually reduced when approaching the target.
	/// @param slowDownWhenReachingTarget: If true, the force is gradually reduced when approaching the target
	void setSlowDownWhenReachingTarget(bool slowDownWhenReachingTarget);

	/// Check if the force is gradually reduced when approaching the target.
	/// @return True, the force is gradually reduced when approaching the target
	bool getSlowDownWhenReachingTarget();

	/// Allow/prevent easing on the computation of the force.
	/// @param allowEasing: If true, easing on the computation of the force is allowed
	void setAllowEasing(bool allowEasing);

	/// Check if easing on the computation is allowed of the force.
	/// @return If true, easing on the computation of the force is allowed
	bool getAllowEasing();
}

#endif
