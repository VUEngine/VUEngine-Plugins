/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LOOK_AT_STEERING_BEHAVIOR_H_
#define LOOK_AT_STEERING_BEHAVIOR_H_


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <SteeringBehavior.h>


//=========================================================================================================
// CLASS' DATA
//=========================================================================================================

/// A LookAtSteeringBehavior Spec
/// @memberof LookAtSteeringBehavior
typedef struct LookAtSteeringBehaviorSpec
{
	SteeringBehaviorSpec steeringBehaviorSpec;

	/// Distance when it is considered that the target has been reached
	fixed_t reachedDistanceThreshold;

	/// Distance when easing starts to apply to the computed force
	fixed_t easingDistanceThreshold;

} LookAtSteeringBehaviorSpec;

/// A LookAtSteeringBehavior spec that is stored in ROM
/// @memberof LookAtSteeringBehavior
typedef const LookAtSteeringBehaviorSpec LookAtSteeringBehaviorROMSpec;


//=========================================================================================================
// CLASS' DECLARATION
//=========================================================================================================

///
/// Class LookAtSteeringBehavior
///
/// Inherits from SteeringBehavior
///
//  Implements a behavior that computes a steering force which will
//  rotate the agent towards the target
class LookAtSteeringBehavior : SteeringBehavior
{
	/// Target to rotate the vehicle towards
	Vector3D target;

	/// Threshold to start easing the computed force
	fixed_t easingDistanceThreshold;

	/// Threshold to detect if the target has been reached
	fixed_t reachedDistanceThreshold;

	/// If true, the force is gradually reduced when approaching the target
	bool slowDownWhenReachingTarget;

	/// If true, the target has been reached
	bool reachedTarget;

	/// If true, easing of the computed force is enabled
	bool allowEasing;

	/// Class' constructor
	/// @param owner: SpatialObject to which the behavior attaches to
	/// @param lookAtSteeringBehaviorSpec: Specification that determines how to configure the behavior
	void constructor(SpatialObject owner, const LookAtSteeringBehaviorSpec* lookAtSteeringBehaviorSpec);

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
