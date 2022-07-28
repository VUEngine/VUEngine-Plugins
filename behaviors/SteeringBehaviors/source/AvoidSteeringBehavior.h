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
	fixed_t maximumAngle;

	/// Avoidance check distance modification percentage
	fixed_t avoidanceDetectionDistance;

	/// Minimum angle's cos to start braking
	fixed_t brakingMinimumAngleCos;

} AvoidSteeringBehaviorSpec;

typedef const AvoidSteeringBehaviorSpec AvoidSteeringBehaviorROMSpec;


typedef struct Obstacle
{
	SpatialObject spatialObject;
	const Vector3D* position;
	fixed_t radius;

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
	fixed_t getAvoidanceDetectionDistance();
	Vector3D getForce();
	override Vector3D calculate(Vehicle owner);
}


#endif
