/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef AVOID_STEERING_BEHAVIOR_H_
#define AVOID_STEERING_BEHAVIOR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SteeringBehavior.h>
#include <SpatialObject.h>


//---------------------------------------------------------------------------------------------------------
//											 DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// defines an entity in ROM memory
typedef struct AvoidSteeringBehaviorSpec
{
	SteeringBehaviorSpec steeringBehaviorSpec;

	/// Maximum angle betwen vehicle and obstacle to account for
	fix10_6 maximumAngle;

	/// Avoidance check distance modification percentage
	fix10_6 avoidanceDetectionDistance;

	/// Minimum angle's cos to start braking
	fix10_6 brakingMinimumAngleCos;

} AvoidSteeringBehaviorSpec;

typedef const AvoidSteeringBehaviorSpec AvoidSteeringBehaviorROMSpec;


typedef struct Obstacle
{
	SpatialObject spatialObject;
	const Vector3D* position;
	fix10_6 radius;

}Obstacle;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

//  Given a target, this behavior returns a steering force which will
//  direct the agent towards the target

/// @ingroup base
class AvoidSteeringBehavior : SteeringBehavior
{
	VirtualList obstacles;
	const AvoidSteeringBehaviorSpec* avoidSteeringBehaviorSpec;
	bool isBraking;

	void constructor(const AvoidSteeringBehaviorSpec* seekSteeringBehaviorSpec);

	void addObstacle(SpatialObject spatialObject);
	void removeAllObstacles();
	bool isBraking();
	VirtualList getObstacles();
	fix10_6 getAvoidanceDetectionDistance();
	Vector3D getForce();
	override Vector3D calculate(Vehicle owner);
}


#endif
