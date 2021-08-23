/*
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
	this->force = Vector3D::zero();

	if(isDeleted(owner))
	{
		this->enabled = false;
		return this->force;
	}

	this->force = AvoidSteeringBehavior::awayFromObstacles(this, owner);

	return this->force;
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
	Direction3D direction = *Vehicle::getDirection3D(vehicle);

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
			fix10_6 obstacleSpeed = SpatialObject::getSpeed(obstacle->spatialObject);

			if(obstacleSpeed)
			{
				fix10_6 speedDifference = __FIX10_6_DIV(Vehicle::getSpeed(vehicle), obstacleSpeed) - __I_TO_FIX10_6(1);

				if(0 < speedDifference && __F_TO_FIX10_6(0.6f) > speedDifference && this->avoidSteeringBehaviorSpec->brakingMinimumAngleCos < dotProduct)
				{
					this->isBraking = true;

					factor = __FIX10_6_EXT_MULT(speedDifference, __FIX10_6_DIV(factor, Vehicle::getFrictionMassRatio(vehicle)));
					Direction3D reverseDirection = Vector3D::scalarProduct(direction, -(__FIX10_6_MULT(factor, dotProduct)));
					desiredVelocity = Vector3D::sum(desiredVelocity, reverseDirection);
				}
			}
		}
	}

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