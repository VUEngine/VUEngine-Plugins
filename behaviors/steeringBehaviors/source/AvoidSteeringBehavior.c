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


//---------------------------------------------------------------------------------------------------------
//												CLASS'S DECLARATIONS
//---------------------------------------------------------------------------------------------------------


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
	VirtualNode node = VirtualList::begin(this->obstacles);

	for(; node; node = VirtualNode::getNext(node))
	{
		delete VirtualNode::getData(node);
	}

	VirtualList::clear(this->obstacles);
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

	if(isDeleted(owner))
	{
		this->enabled = false;
		return Vector3D::zero();
	}

	return  VirtualList::getSize(this->obstacles) ? AvoidSteeringBehavior::awayFromObstacles(this, owner) : Vector3D::zero();
}

Vector3D AvoidSteeringBehavior::awayFromObstacles(Vehicle vehicle)
{
	Vector3D desiredVelocity = Vector3D::zero();

	Vector3D position = *Vehicle::getPosition(vehicle);
	Body body = Vehicle::getBody(vehicle);
	Velocity velocity = Body::getVelocity(body);
	Direction3D direction = Body::getDirection3D(body);
	fix10_6 projectedDistance = __FIX10_6_MULT(Vector3D::length(velocity), __F_TO_FIX10_6(0.4f));

	VirtualNode node = VirtualList::begin(this->obstacles);

	for(; node; node = VirtualNode::getNext(node))
	{
		Obstacle* obstacle = (Obstacle*)VirtualNode::getData(node);

		Vector3D vectorVehicleObstacle = Vector3D::get(position, *obstacle->position);
		fix10_6 distance = Vector3D::length(vectorVehicleObstacle);// - radius - obstacle->radius;

		fix10_6 dotProduct = Vector3D::dotProduct(Vector3D::normalize(vectorVehicleObstacle), direction);
		
		if(__FIX7_9_TO_FIX10_6(-__ABS(__COS(this->avoidSteeringBehaviorSpec->maximumAngle))) < dotProduct && distance < projectedDistance)
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
			desiredVelocity = Vector3D::sum(desiredVelocity, Vector3D::scalarProduct(desiredDirection, (projectedDistance - distance)));
		}
	}

	return desiredVelocity;
}
