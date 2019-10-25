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

static Vector3D SteeringBehavior::applyDeviation(Vector3D force, fix10_6 deviation)
{
	long seed = Game::getRandomSeed(Game::getInstance());
	force.x -= force.x ? Utilities::random(seed, deviation << 1) - deviation : 0;
	force.y -= force.y ? Utilities::random(seed, deviation << 1) - deviation : 0;
	force.z -= force.z ? Utilities::random(seed, deviation << 1) - deviation : 0;

	return force;
}

static Vector3D SteeringBehavior::clampForce(Vector3D force, fix10_6 maximumForce)
{
	if(maximumForce)
	{		
		fix10_6_ext squaredForceMagnitude = Vector3D::squareLength(force);

		if(squaredForceMagnitude > __FIX10_6_EXT_MULT(maximumForce, maximumForce))
		{
			fix10_6 forceMagnitude = __F_TO_FIX10_6(Math::squareRoot(__FIX10_6_EXT_TO_F(squaredForceMagnitude)));

			if(forceMagnitude)
			{
				force = Vector3D::scalarProduct(force, __FIX10_6_DIV(maximumForce, forceMagnitude));
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
		fix10_6 maximumForce = 0;
		VirtualNode node = steeringBehaviors->head;

		for(; node; node = node->next)
		{
			SteeringBehavior steeringBehavior = SteeringBehavior::safeCast(node->data);

			if(steeringBehavior->enabled)
			{
				maximumForce += steeringBehavior->maximumForce;
			}
		}

		node = steeringBehaviors->head;

		for(; node; node = node->next)
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

		for(; node; node = node->next)
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
static bool SteeringBehavior::accumulateForce(fix10_6 maximumForce, Vector3D *totalForce, Vector3D forceToAdd)
{	
	//calculate how much steering force the vehicle has used so far
	fix10_6 squareMagnitudeSoFar = Vector3D::squareLength(*totalForce);
	
	//calculate how much steering force remains to be used by this vehicle
	fix10_6 squareMagnitudeRemaining = __FIX10_6_EXT_MULT(maximumForce, maximumForce) - squareMagnitudeSoFar;
	
	//return false if there is no more force left to use
	if (squareMagnitudeRemaining < 0)
	{
		return false;
	}

	//calculate the magnitude of the force we want to add
	fix10_6 squareMagnitudeToAdd = Vector3D::squareLength(forceToAdd);
	
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
		fix10_6 magnitudeToAdd = __F_TO_FIX10_6(Math::squareRoot(__FIX10_6_EXT_TO_F(squareMagnitudeToAdd)));
		fix10_6 magnitudeSoFar = __F_TO_FIX10_6(Math::squareRoot(__FIX10_6_EXT_TO_F(squareMagnitudeSoFar)));
	
		//calculate how much steering force remains to be used by this vehicle
		fix10_6 magnitudeRemaining = maximumForce - magnitudeSoFar;
		
		//add it to the steering force
		if(magnitudeToAdd)
		{
			*totalForce = Vector3D::sum(*totalForce, Vector3D::scalarProduct(forceToAdd, __FIX10_6_DIV(magnitudeRemaining, magnitudeToAdd)));
		}
	}

	return true;
}

int SteeringBehavior::getPriority()
{
	return this->priority;
}

void SteeringBehavior::setPriority(int value)
{
	this->priority = value;
}

fix10_6 SteeringBehavior::getWeight()
{
	return this->weight;
}

void SteeringBehavior::setWeight(fix10_6 value)
{
	this->weight = value;
}

fix10_6 SteeringBehavior::getMaximumForce()
{
	return this->maximumForce;
}

void SteeringBehavior::setMaximumForce(fix10_6 value)
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
