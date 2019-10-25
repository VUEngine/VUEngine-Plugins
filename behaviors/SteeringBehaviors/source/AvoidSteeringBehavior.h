/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
	Force force;
	VirtualList obstacles;
	const AvoidSteeringBehaviorSpec* avoidSteeringBehaviorSpec;

	void constructor(const AvoidSteeringBehaviorSpec* seekSteeringBehaviorSpec);

	void addObstacle(SpatialObject spatialObject);
	void removeAllObstacles();
	VirtualList getObstacles();
	fix10_6 getAvoidanceDetectionDistance();
	Vector3D getForce();
	override Vector3D calculate(Vehicle owner);
}


#endif
