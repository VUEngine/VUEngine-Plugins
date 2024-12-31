/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <Vehicle.h>
#include <VirtualList.h>
#include <VirtualNode.h>
#include <VUEngine.h>

#include "AvoidSteeringBehavior.h"


//=========================================================================================================
// CLASS' DECLARATIONS
//=========================================================================================================

friend class VirtualList;
friend class VirtualNode;


//=========================================================================================================
// CLASS' DATA
//=========================================================================================================

typedef struct Obstacle
{
	GameObject gameObject;
	const Vector3D* position;
	fixed_t radius;

}Obstacle;


//=========================================================================================================
// CLASS' PUBLIC METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
void AvoidSteeringBehavior::constructor(GameObject owner, const AvoidSteeringBehaviorSpec* avoidSteeringBehaviorSpec)
{
	// Always explicitly call the base's constructor 
	Base::constructor(owner, &avoidSteeringBehaviorSpec->steeringBehaviorSpec);

	this->obstacles = new VirtualList();
}
//---------------------------------------------------------------------------------------------------------
void AvoidSteeringBehavior::destructor()
{
	AvoidSteeringBehavior::removeAllObstacles(this);
	delete this->obstacles;

	// Always explicitly call the base's destructor 
	Base::destructor();
}
//---------------------------------------------------------------------------------------------------------
Vector3D AvoidSteeringBehavior::calculate(Vehicle owner)
{
	this->force = Vector3D::zero();

	if(isDeleted(owner))
	{
		this->enabled = false;
		return this->force;
	}

	this->force = AvoidSteeringBehavior::awayFromObstacles(this, owner);

	return this->force;
}
//---------------------------------------------------------------------------------------------------------
void AvoidSteeringBehavior::addObstacle(GameObject gameObject)
{
	if(isDeleted(gameObject))
	{
		return;
	}

	Obstacle* obstacle = new Obstacle;

	obstacle->gameObject = gameObject;
	obstacle->position = GameObject::getPosition(gameObject);
	obstacle->radius = GameObject::getRadius(gameObject);

	VirtualList::pushBack(this->obstacles, obstacle);
}
//---------------------------------------------------------------------------------------------------------
void AvoidSteeringBehavior::removeAllObstacles()
{
	VirtualList::deleteData(this->obstacles);
}
//---------------------------------------------------------------------------------------------------------

//=========================================================================================================
// CLASS' PRIVATE METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
Vector3D AvoidSteeringBehavior::awayFromObstacles(Vehicle vehicle)
{
	VirtualNode node = this->obstacles->head;

	if(!node)
	{
		return Vector3D::zero();
	}

	Vector3D desiredVelocity = Vector3D::zero();

	Vector3D position = *Vehicle::getPosition(vehicle);
	Vector3D direction = *Vehicle::getDirection(vehicle);

	fixed_t squareAvoidanceDetectionDistance = __FIXED_MULT(((AvoidSteeringBehaviorSpec*)this->componentSpec)->avoidanceDetectionDistance, ((AvoidSteeringBehaviorSpec*)this->componentSpec)->avoidanceDetectionDistance);
	fixed_ext_t squareMaximumForce = __FIXED_EXT_MULT(this->maximumForce, this->maximumForce);

	for(; NULL != node; node = node->next)
	{
		Obstacle* obstacle = (Obstacle*)node->data;

		Vector3D vectorVehicleObstacle = Vector3D::get(position, *obstacle->position);
		fixed_t squareDistance = __FIXED_EXT_TO_FIXED(Vector3D::squareLength(vectorVehicleObstacle));

		fixed_t dotProduct = Vector3D::dotProduct(direction, Vector3D::normalize(vectorVehicleObstacle));

		if(squareDistance < squareAvoidanceDetectionDistance && __FIX7_9_TO_FIXED(__COS(((AvoidSteeringBehaviorSpec*)this->componentSpec)->maximumAngle)) < dotProduct)
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

			fixed_t squareDistance1 = Vector3D::squareLength(Vector3D::get(position, obstacleEdge1));
			fixed_t squareDistance2 = Vector3D::squareLength(Vector3D::get(position, obstacleEdge2));

			Vector3D desiredDirection = squareDistance2 < squareDistance1 ? desiredDirection2 : desiredDirection1;

			fixed_ext_t factor = squareMaximumForce;

			if(0 != squareDistance)
			{
				factor = __FIXED_EXT_DIV(factor, squareDistance);
			}

			desiredVelocity = Vector3D::sum(desiredVelocity, Vector3D::scalarProduct(desiredDirection, __FIXED_EXT_MULT(dotProduct, factor)));
			fixed_t obstacleSpeed = GameObject::getSpeed(obstacle->gameObject);

			if(obstacleSpeed)
			{
				fixed_t speedDifference = __FIXED_DIV(Vehicle::getSpeed(vehicle), obstacleSpeed) - __I_TO_FIXED(1);

				if(0 < speedDifference && __F_TO_FIXED(0.6f) > speedDifference && ((AvoidSteeringBehaviorSpec*)this->componentSpec)->brakingMinimumAngleCos < dotProduct)
				{
					factor = __FIXED_EXT_MULT(speedDifference, __FIXED_DIV(factor, Vehicle::getFrictionMassRatio(vehicle)));
					Vector3D reverseDirection = Vector3D::scalarProduct(direction, -(__FIXED_MULT(factor, dotProduct)));
					desiredVelocity = Vector3D::sum(desiredVelocity, reverseDirection);
				}
			}
		}
	}

	return desiredVelocity;
}
//---------------------------------------------------------------------------------------------------------
