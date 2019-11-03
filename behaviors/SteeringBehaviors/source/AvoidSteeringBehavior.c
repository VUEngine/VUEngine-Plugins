/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AvoidSteeringBehavior.h>
#include <Vehicle.h>
#include <VirtualList.h>
#include <Game.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S DECLARATIONS
//---------------------------------------------------------------------------------------------------------

friend class VirtualNode;
friend class VirtualList;


#undef DRAW_FORCE



//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

/**
 * Class constructor
 */
void AvoidSteeringBehavior::constructor(const AvoidSteeringBehaviorSpec* avoidSteeringBehaviorSpec)
{
	Base::constructor(&avoidSteeringBehaviorSpec->steeringBehaviorSpec);

	this->obstacles = new VirtualList();
	this->avoidSteeringBehaviorSpec = avoidSteeringBehaviorSpec;
	this->force = Vector3D::zero();
	this->isBraking = false;
}

/**
 * Class destructor
 */
void AvoidSteeringBehavior::destructor()
{
	AvoidSteeringBehavior::removeAllObstacles(this);
	delete this->obstacles;

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void AvoidSteeringBehavior::removeAllObstacles()
{
	VirtualNode node = this->obstacles->head;

	for(; node; node = node->next)
	{
		delete node->data;
	}

	VirtualList::clear(this->obstacles);
}

fix10_6 AvoidSteeringBehavior::getAvoidanceDetectionDistance()
{
	return this->avoidSteeringBehaviorSpec->avoidanceDetectionDistance;
}

VirtualList AvoidSteeringBehavior::getObstacles()
{
	return this->obstacles;
}

void AvoidSteeringBehavior::addObstacle(SpatialObject spatialObject)
{
	if(isDeleted(spatialObject))
	{
		return;
	}

	Obstacle* obstacle = new Obstacle;

	obstacle->spatialObject = spatialObject;
	obstacle->position = SpatialObject::getPosition(spatialObject);
	obstacle->radius = SpatialObject::getRadius(spatialObject);


	VirtualList::pushBack(this->obstacles, obstacle);
}

Vector3D AvoidSteeringBehavior::calculate(Vehicle owner)
{
	this->isBraking = false;

	if(isDeleted(owner))
	{
		this->enabled = false;
		return Vector3D::zero();
	}

	return  AvoidSteeringBehavior::awayFromObstacles(this, owner);
}

Vector3D AvoidSteeringBehavior::awayFromObstacles(Vehicle vehicle)
{
	VirtualNode node = this->obstacles->head;

	if(!node)
	{
		return Vector3D::zero();
	}

	Vector3D desiredVelocity = Vector3D::zero();

	Vector3D position = *Vehicle::getPosition(vehicle);
	Direction3D direction = Vehicle::getDirection3D(vehicle);

	fix10_6 squareAvoidanceDetectionDistance = __FIX10_6_MULT(this->avoidSteeringBehaviorSpec->avoidanceDetectionDistance, this->avoidSteeringBehaviorSpec->avoidanceDetectionDistance);
	fix10_6_ext squareMaximumForce = __FIX10_6_EXT_MULT(this->maximumForce, this->maximumForce);

	for(; node; node = node->next)
	{
		Obstacle* obstacle = (Obstacle*)node->data;

		Vector3D vectorVehicleObstacle = Vector3D::get(position, *obstacle->position);
		fix10_6 squareDistance = __FIX10_6_EXT_TO_FIX10_6(Vector3D::squareLength(vectorVehicleObstacle));
		
		fix10_6 dotProduct = Vector3D::dotProduct(direction, Vector3D::normalize(vectorVehicleObstacle));

		if(squareDistance < squareAvoidanceDetectionDistance && __FIX7_9_TO_FIX10_6(__COS(this->avoidSteeringBehaviorSpec->maximumAngle)) < dotProduct)
		{
			Vector3D desiredDirection1 = 
			{	
				direction.y,
				-direction.x,
				0
			};

			Vector3D desiredDirection2 = 
			{	
				-direction.y,
				direction.x,
				0
			};

			Vector3D obstacleEdge1 = Vector3D::sum(*obstacle->position, Vector3D::scalarProduct(desiredDirection1, obstacle->radius));
			Vector3D obstacleEdge2 = Vector3D::sum(*obstacle->position, Vector3D::scalarProduct(desiredDirection2, obstacle->radius));

			fix10_6 squareDistance1 = Vector3D::squareLength(Vector3D::get(position, obstacleEdge1));
			fix10_6 squareDistance2 = Vector3D::squareLength(Vector3D::get(position, obstacleEdge2));

			Vector3D desiredDirection = squareDistance2 < squareDistance1 ? desiredDirection2 : desiredDirection1;

			fix10_6_ext factor = squareMaximumForce;

			if(0 != squareDistance)
			{
				factor = __FIX10_6_EXT_DIV(factor, squareDistance);
			}

			desiredVelocity = Vector3D::sum(desiredVelocity, Vector3D::scalarProduct(desiredDirection, __FIX10_6_EXT_MULT(dotProduct, factor)));
			fix10_6 speedDifference = Vehicle::getSpeed(vehicle) - Vehicle::getSpeed(obstacle->spatialObject);

			if(0 < speedDifference && this->avoidSteeringBehaviorSpec->brakingMinimumAngleCos < dotProduct)
			{
				this->isBraking = true;

				factor = __FIX10_6_EXT_MULT(speedDifference, factor);
				Direction3D reverseDirection = Vector3D::scalarProduct(direction, -(__FIX10_6_MULT(factor, dotProduct)));
				desiredVelocity = Vector3D::sum(desiredVelocity, reverseDirection);
			}
		}
	}

	this->force = desiredVelocity;

	return desiredVelocity;
}

Vector3D AvoidSteeringBehavior::getForce()
{
	return this->enabled ? this->force : Vector3D::zero();
}

bool AvoidSteeringBehavior::isBraking()
{
	return this->isBraking && this->enabled;
}