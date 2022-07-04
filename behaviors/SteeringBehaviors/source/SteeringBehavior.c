/**
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

#include <SteeringBehavior.h>
#include <Vehicle.h>
#include <Game.h>
#include <Utilities.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S DECLARATIONS
//---------------------------------------------------------------------------------------------------------

friend class VirtualNode;
friend class VirtualList;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

/**
 * Class constructor
 */
void SteeringBehavior::constructor(const SteeringBehaviorSpec* steeringBehaviorSpec)
{
	Base::constructor(&steeringBehaviorSpec->behaviorSpec);

	this->steeringBehaviorSpec = steeringBehaviorSpec;

	this->force = Vector3D::zero();

	SteeringBehavior::reset(this);
}

/**
 * Class destructor
 */
void SteeringBehavior::destructor()
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

static Vector3D SteeringBehavior::calculateForce(Vehicle vehicle)
{
	Vector3D steeringForce = {0, 0, 0};

	// otherwise it's just a velocity and add it
	switch(Vehicle::getSummingMethod(vehicle))
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

static Vector3D SteeringBehavior::applyDeviation(Vector3D force, fixed_t deviation)
{
	long seed = _gameRandomSeed;
	force.x -= force.x ? Utilities::random(seed, deviation << 1) - deviation : 0;
	force.y -= force.y ? Utilities::random(seed, deviation << 1) - deviation : 0;
	force.z -= force.z ? Utilities::random(seed, deviation << 1) - deviation : 0;

	return force;
}

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

				if(steeringBehavior->deviation)
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

int32 SteeringBehavior::getPriority()
{
	return this->priority;
}

void SteeringBehavior::setPriority(int32 value)
{
	this->priority = value;
}

fixed_t SteeringBehavior::getWeight()
{
	return this->weight;
}

void SteeringBehavior::setWeight(fixed_t value)
{
	this->weight = value;
}

fixed_t SteeringBehavior::getMaximumForce()
{
	return this->maximumForce;
}

void SteeringBehavior::setMaximumForce(fixed_t value)
{
	this->maximumForce = value;
}

void SteeringBehavior::reset()
{
	this->priority = this->steeringBehaviorSpec->priority;
	this->weight = this->steeringBehaviorSpec->weight;
	this->maximumForce = this->steeringBehaviorSpec->maximumForce;
	this->deviation = this->steeringBehaviorSpec->deviation;
}

const SteeringBehaviorSpec* SteeringBehavior::getSteeringBehaviorSpec()
{
	return this->steeringBehaviorSpec;
}

Vector3D SteeringBehavior::getForce()
{
	return this->force;
}
