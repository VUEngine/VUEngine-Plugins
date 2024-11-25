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


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <SteeringBehavior.h>


//=========================================================================================================
// CLASS' DATA
//=========================================================================================================

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


//=========================================================================================================
// CLASS' DECLARATION
//=========================================================================================================

///
/// Class Behavior
///
/// Inherits from Behavior
///
/// Defines a behavior that returns a steering force which will
/// direct the agent towards a target
class SeekSteeringBehavior : SteeringBehavior
{
	Vector3D target;
	fixed_ext_t squaredReachedDistanceThreshold;
	fixed_t easingDistanceThreshold;
	bool slowDownWhenReachingTarget;
	bool reachedTarget;
	bool allowEasing;

	/// Class' constructor
	/// @param owner: SpatialObject to which the behavior attaches to
	/// @param seekSteeringBehaviorSpec: Specification that determines how to configure the behavior
	void constructor(SpatialObject owner, const SeekSteeringBehaviorSpec* seekSteeringBehaviorSpec);

	/// Calculate the force vector to apply.
	/// @param owner: Vehicle that owns the steering behavior
	/// @return The force vector to apply to the provided vechile
	override Vector3D calculate(Vehicle owner);

	void setTarget(Vector3D value);
	Vector3D getTarget();

	void setAllowEasing(bool value);
	bool getAllowEasing();
	
	void setSlowDownWhenReachingTarget(bool value);
	bool getSlowDownWhenReachingTarget();
	
	void setReachedDistanceThreshold(fixed_t value);
	fixed_t getReachedDistanceThreshold();
	
}


#endif
