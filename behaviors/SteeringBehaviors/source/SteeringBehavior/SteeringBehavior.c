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

#include <Utilities.h>
#include <Vehicle.h>
#include <VirtualNode.h>
#include <VirtualList.h>
#include <VUEngine.h>

#include "SteeringBehavior.h"


//=========================================================================================================
// CLASS' DECLARATIONS
//=========================================================================================================

friend class VirtualList;
friend class VirtualNode;


//=========================================================================================================
// CLASS' STATIC METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
static Vector3D SteeringBehavior::calculateForce(Vehicle vehicle, uint16 summingMethod)
{
	Vector3D steeringForce = {0, 0, 0};

	// otherwise it's just a velocity and add it
	switch(summingMethod)
	{
		case kPrioritized:

			steeringForce = SteeringBehavior::calculatePrioritized(vehicle);
			break;

		case kWeightedAverage:

			steeringForce = SteeringBehavior::calculateWeightedSum(vehicle);
			break;
	}

	return steeringForce;
}
//---------------------------------------------------------------------------------------------------------

//=========================================================================================================
// CLASS' PRIVATE STATIC METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
static Vector3D SteeringBehavior::calculatePrioritized(Vehicle vehicle)
{
	Vector3D steeringForce = {0, 0, 0};

	VirtualList steeringBehaviors = Vehicle::getSteeringBehaviors(vehicle);

	if(!isDeleted(steeringBehaviors))
	{
		fixed_t maximumForce = 0;
		VirtualNode node = steeringBehaviors->head;

		for(; NULL != node; node = node->next)
		{
			SteeringBehavior steeringBehavior = SteeringBehavior::safeCast(node->data);

			if(steeringBehavior->enabled)
			{
				maximumForce += steeringBehavior->maximumForce;
			}
		}

		node = steeringBehaviors->head;

		for(; NULL != node; node = node->next)
		{
			SteeringBehavior steeringBehavior = SteeringBehavior::safeCast(node->data);

			if(steeringBehavior->enabled)
			{
				Vector3D force = Vector3D::scalarProduct(SteeringBehavior::calculate(steeringBehavior, vehicle), steeringBehavior->weight);

				if(0 != steeringBehavior->deviation)
				{
					force = SteeringBehavior::applyDeviation(force, steeringBehavior->deviation);
				}

				force = SteeringBehavior::clampForce(force, steeringBehavior->maximumForce);

				if(!SteeringBehavior::accumulateForce(maximumForce, &steeringForce, force))
				{
					return steeringForce;
				}
			}
		}
	}

	return steeringForce;
}
//---------------------------------------------------------------------------------------------------------
static Vector3D SteeringBehavior::calculateWeightedSum(Vehicle vehicle)
{
	Vector3D steeringForce = {0, 0, 0};

	VirtualList steeringBehaviors = Vehicle::getSteeringBehaviors(vehicle);

	if(!isDeleted(steeringBehaviors))
	{
		VirtualNode node = steeringBehaviors->head;

		for(; NULL != node; node = node->next)
		{
			SteeringBehavior steeringBehavior = SteeringBehavior::safeCast(node->data);

			if(steeringBehavior->enabled)
			{
				Vector3D force = Vector3D::scalarProduct(SteeringBehavior::calculate(steeringBehavior, vehicle), steeringBehavior->weight);

				if(steeringBehavior->deviation)
				{
					force = SteeringBehavior::applyDeviation(force, steeringBehavior->deviation);
				}

				steeringForce = Vector3D::sum(steeringForce, SteeringBehavior::clampForce(force, steeringBehavior->maximumForce));
			}
		}
	}

	return steeringForce;
}
//---------------------------------------------------------------------------------------------------------
//  This function calculates how much of its max steering force the
//  vehicle has left to apply and then applies that amount of the
//  force to add.
static bool SteeringBehavior::accumulateForce(fixed_t maximumForce, Vector3D *totalForce, Vector3D forceToAdd)
{
	//calculate how much steering force the vehicle has used so far
	fixed_t squareMagnitudeSoFar = Vector3D::squareLength(*totalForce);

	//calculate how much steering force remains to be used by this vehicle
	fixed_t squareMagnitudeRemaining = __FIXED_EXT_MULT(maximumForce, maximumForce) - squareMagnitudeSoFar;

	//return false if there is no more force left to use
	if (squareMagnitudeRemaining < 0)
	{
		return false;
	}

	//calculate the magnitude of the force we want to add
	fixed_t squareMagnitudeToAdd = Vector3D::squareLength(forceToAdd);

	//if the magnitude of the sum of forceToAdd and the running total
	//does not exceed the maximum force available to this vehicle, just
	//add together. Otherwise add as much of the forceToAdd vector is
	//possible without going over the max.
	if (squareMagnitudeToAdd < squareMagnitudeRemaining)
	{
		*totalForce = Vector3D::sum(*totalForce, forceToAdd);
	}
	else if(squareMagnitudeToAdd)
	{
		fixed_t magnitudeToAdd = __F_TO_FIXED(Math::squareRoot(__FIXED_EXT_TO_F(squareMagnitudeToAdd)));
		fixed_t magnitudeSoFar = __F_TO_FIXED(Math::squareRoot(__FIXED_EXT_TO_F(squareMagnitudeSoFar)));

		//calculate how much steering force remains to be used by this vehicle
		fixed_t magnitudeRemaining = maximumForce - magnitudeSoFar;

		//add it to the steering force
		if(magnitudeToAdd)
		{
			*totalForce = Vector3D::sum(*totalForce, Vector3D::scalarProduct(forceToAdd, __FIXED_DIV(magnitudeRemaining, magnitudeToAdd)));
		}
	}

	return true;
}
//---------------------------------------------------------------------------------------------------------
static Vector3D SteeringBehavior::applyDeviation(Vector3D force, fixed_t deviation)
{
	long seed = _gameRandomSeed;
	force.x -= force.x ? Math::random(seed, deviation << 1) - deviation : 0;
	force.y -= force.y ? Math::random(seed, deviation << 1) - deviation : 0;
	force.z -= force.z ? Math::random(seed, deviation << 1) - deviation : 0;

	return force;
}
//---------------------------------------------------------------------------------------------------------
static Vector3D SteeringBehavior::clampForce(Vector3D force, fixed_t maximumForce)
{
	if(maximumForce)
	{
		fixed_ext_t squaredForceMagnitude = Vector3D::squareLength(force);

		if(squaredForceMagnitude > __FIXED_EXT_MULT(maximumForce, maximumForce))
		{
			fixed_t forceMagnitude = __F_TO_FIXED(Math::squareRoot(__FIXED_EXT_TO_F(squaredForceMagnitude)));

			if(forceMagnitude)
			{
				force = Vector3D::scalarProduct(force, __FIXED_DIV(maximumForce, forceMagnitude));
			}
		}
	}

	return force;
}
//---------------------------------------------------------------------------------------------------------

//=========================================================================================================
// CLASS' PUBLIC METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
void SteeringBehavior::constructor(GameObject owner, const SteeringBehaviorSpec* steeringBehaviorSpec)
{
	// Always explicitly call the base's constructor 
	Base::constructor(owner, &steeringBehaviorSpec->behaviorSpec);

	this->force = Vector3D::zero();

	SteeringBehavior::reset(this);
}
//---------------------------------------------------------------------------------------------------------
void SteeringBehavior::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}
//---------------------------------------------------------------------------------------------------------
const SteeringBehaviorSpec* SteeringBehavior::getSteeringBehaviorSpec()
{
	return ((SteeringBehaviorSpec*)this->componentSpec);
}
//---------------------------------------------------------------------------------------------------------
void SteeringBehavior::reset()
{
	this->priority = ((SteeringBehaviorSpec*)this->componentSpec)->priority;
	this->weight = ((SteeringBehaviorSpec*)this->componentSpec)->weight;
	this->maximumForce = ((SteeringBehaviorSpec*)this->componentSpec)->maximumForce;
	this->deviation = ((SteeringBehaviorSpec*)this->componentSpec)->deviation;
}
//---------------------------------------------------------------------------------------------------------
void SteeringBehavior::setPriority(int32 priority)
{
	this->priority = priority;
}
//---------------------------------------------------------------------------------------------------------
int32 SteeringBehavior::getPriority()
{
	return this->priority;
}
//---------------------------------------------------------------------------------------------------------
void SteeringBehavior::setWeight(fixed_t weight)
{
	this->weight = weight;
}
//---------------------------------------------------------------------------------------------------------
fixed_t SteeringBehavior::getWeight()
{
	return this->weight;
}
//---------------------------------------------------------------------------------------------------------
void SteeringBehavior::setMaximumForce(fixed_t maximumForce)
{
	this->maximumForce = maximumForce;
}
//---------------------------------------------------------------------------------------------------------
fixed_t SteeringBehavior::getMaximumForce()
{
	return this->maximumForce;
}
//---------------------------------------------------------------------------------------------------------
