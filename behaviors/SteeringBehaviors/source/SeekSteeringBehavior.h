/*
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef SEEK_STEERING_BEHAVIOR_H_
#define SEEK_STEERING_BEHAVIOR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SteeringBehavior.h>


//---------------------------------------------------------------------------------------------------------
//											 DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// defines an entity in ROM memory
typedef struct SeekSteeringBehaviorSpec
{
	SteeringBehaviorSpec steeringBehaviorSpec;

	/// Distance when it is considered that the target has been reached
	fix10_6 reachedDistanceThreshold;

	/// Distance when easing starts to apply to the computed force
	fix10_6 easingDistanceThreshold;

} SeekSteeringBehaviorSpec;

typedef const SeekSteeringBehaviorSpec SeekSteeringBehaviorROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

//  Given a target, this behavior returns a steering force which will
//  direct the agent towards the target

/// @ingroup base
class SeekSteeringBehavior : SteeringBehavior
{
	Vector3D target;
	fix10_6 reachedDistanceThreshold;
	fix10_6 easingDistanceThreshold;
	bool slowDownWhenReachingTarget;
	bool reachedTarget;
	bool allowEasing;

	void constructor(const SeekSteeringBehaviorSpec* seekSteeringBehaviorSpec);

	Vector3D getTarget();
	void setTarget(Vector3D value);
	bool getAllowEasing();
	void setAllowEasing(bool value);
	bool getSlowDownWhenReachingTarget();
	void setSlowDownWhenReachingTarget(bool value);
	fix10_6 getReachedDistanceThreshold();
	void setReachedDistanceThreshold(fix10_6 value);
	override Vector3D calculate(Vehicle owner);
}


#endif
