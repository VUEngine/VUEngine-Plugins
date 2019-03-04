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


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

/**
 * Class constructor
 */
void SteeringBehavior::constructor(const SteeringBehaviorSpec* steeringBehaviorSpec)
{
	Base::constructor(&steeringBehaviorSpec->behaviorSpec);

	this->priority = steeringBehaviorSpec->priority;
	this->weight = steeringBehaviorSpec->weight;
	this->maximumForce = steeringBehaviorSpec->maximumForce;
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

static Vector3D SteeringBehavior::clampForce(Vector3D force, fix10_6 maximumForce)
{
	if(maximumForce)
	{		
		if(Vector3D::squareLength(force) > __FIX10_6_MULT(maximumForce, maximumForce))
		{
			force = Vector3D::scalarProduct(Vector3D::normalize(force), maximumForce);
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
		VirtualNode node = VirtualList::begin(steeringBehaviors);

		for(; node; node = VirtualNode::getNext(node))
		{
			SteeringBehavior steeringBehavior = SteeringBehavior::safeCast(VirtualNode::getData(node));

			if(SteeringBehavior::isEnabled(steeringBehavior))
			{
				Vector3D force = SteeringBehavior::clampForce(Vector3D::scalarProduct(SteeringBehavior::calculate(steeringBehavior, vehicle), steeringBehavior->weight), steeringBehavior->maximumForce);
				
				if(!SteeringBehavior::accumulateForce(steeringBehavior->maximumForce, &steeringForce, force))
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
		VirtualNode node = VirtualList::begin(steeringBehaviors);

		for(; node; node = VirtualNode::getNext(node))
		{
			SteeringBehavior steeringBehavior = SteeringBehavior::safeCast(VirtualNode::getData(node));

			if(SteeringBehavior::isEnabled(steeringBehavior))
			{
				Vector3D force = SteeringBehavior::clampForce(Vector3D::scalarProduct(SteeringBehavior::calculate(steeringBehavior, vehicle), steeringBehavior->weight), steeringBehavior->maximumForce);
				
				steeringForce = Vector3D::sum(steeringForce, force);
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
	fix10_6 magnitudeSoFar = Vector3D::length(*totalForce);
	
	//calculate how much steering force remains to be used by this vehicle
	fix10_6 magnitudeRemaining = maximumForce - magnitudeSoFar;
	
	//return false if there is no more force left to use
	if (magnitudeRemaining < 0)
	{
		return false;
	}

	//calculate the magnitude of the force we want to add
	fix10_6 magnitudeToAdd = Vector3D::length(forceToAdd);
	
	//if the magnitude of the sum of forceToAdd and the running total
	//does not exceed the maximum force available to this vehicle, just
	//add together. Otherwise add as much of the forceToAdd vector is
	//possible without going over the max.
	if (magnitudeToAdd < magnitudeRemaining)
	{	
		*totalForce = Vector3D::sum(*totalForce, forceToAdd);
	}		
	else
	{
		//add it to the steering force
		*totalForce = Vector3D::sum(*totalForce, Vector3D::scalarProduct(Vector3D::normalize(forceToAdd), magnitudeRemaining));
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
