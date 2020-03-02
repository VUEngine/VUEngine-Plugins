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

#include <Game.h>
#include <SteeringBehavior.h>
#include "Vehicle.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S DECLARATIONS
//---------------------------------------------------------------------------------------------------------

friend class VirtualNode;
friend class VirtualList;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Vehicle::constructor(VehicleSpec* vehicleSpec, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorSpec*)&vehicleSpec->actorSpec, id, internalId, name);

	// save vehicle spec
	this->vehicleSpec = vehicleSpec;
	this->steeringBehaviors = NULL;
	this->evenCycle = vehicleSpec->runSteeringBehaviorsAtHalfSpeed ? 0 : -1;
	this->steeringForce = Vector3D::zero();
	this->accumulatedForce = Vector3D::zero();
	this->radius = 0;
	this->checkIfCanMove = false;
//	this->frictionMassRatio = Body::getFrictionCoefficient(this->body) + Body::getMass(this->body);
}

// class's destructor
void Vehicle::destructor()
{
	if(this->steeringBehaviors)
	{
		delete this->steeringBehaviors;
		this->steeringBehaviors = NULL;
	}

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Vehicle::ready(bool recursive)
{
	Base::ready(this, recursive);

	this->radius = Vehicle::getRadius(this);


	if(!this->steeringBehaviors)
	{
		this->steeringBehaviors = new VirtualList();
	}
	
	// get steering behaviors to sort them based on their priority
	Container::getBehaviors(this, typeofclass(SteeringBehavior), this->steeringBehaviors);

	VirtualNode node = this->steeringBehaviors->head;

	// just an easy bubble sort
	for(; node; node = node->next)
	{
		SteeringBehavior steeringBehavior = SteeringBehavior::safeCast(node->data);

		VirtualNode auxNode = node->next;

		for(; auxNode; auxNode = auxNode->next)
		{
			SteeringBehavior auxSteeringBehavior = SteeringBehavior::safeCast(auxNode->data);
			
			// check the priority and swap them to make the higher priority to come first in the array
			if(SteeringBehavior::getPriority(steeringBehavior) < SteeringBehavior::getPriority(auxSteeringBehavior))
			{
				VirtualNode::swapData(node, auxNode);
				steeringBehavior = auxSteeringBehavior;
				auxNode = node->next;
			}				
		}
	}

	//m_headingSmoother = new BLGSmoother(m_iSamplesForSmoothing, new Vector3(0.0F, 0.0F, 0.0F));
	if(0 <= this->evenCycle)
	{
		this->evenCycle = this->internalId % 2;
	}
}

void Vehicle::addForce(const Force* force, bool checkIfCanMove __attribute__((unused)))
{
	this->checkIfCanMove |= checkIfCanMove;
	this->accumulatedForce = Vector3D::sum(this->accumulatedForce, *force);
}

int Vehicle::getSummingMethod()
{
	return this->vehicleSpec->summingMethod;
}

VirtualList Vehicle::getSteeringBehaviors()
{
	return this->steeringBehaviors;
}

Velocity Vehicle::getVelocity()
{
	return Body::getVelocity(this->body);
}

const Direction3D* Vehicle::getDirection3D()
{
	return Body::getDirection3D(this->body);
}

fix10_6 Vehicle::getFrictionMassRatio()
{
	return 0;//this->frictionMassRatio;
}

const Vector3D* Vehicle::getReferencePosition()
{
	return Vehicle::getPosition(this);
}

bool Vehicle::updateForce()
{
	bool computeForce = 0 > this->evenCycle;
	
	if(!computeForce)
	{
		u16 modulo = __MODULO(this->evenCycle, 2);
		computeForce = 1 == modulo;
		this->evenCycle = !modulo;
	}

	if(computeForce && this->behaviors)
	{
		this->steeringForce = SteeringBehavior::calculateForce(this);
	}

	Force totalForce = Vector3D::sum(this->accumulatedForce, this->steeringForce);

	Base::addForce(this, &totalForce, this->checkIfCanMove);

	this->accumulatedForce = Vector3D::zero();
	this->checkIfCanMove = false;

	return computeForce;
}

void Vehicle::update(u32 elapsedTime __attribute__((unused)))
{
	Base::update(this, elapsedTime);
	
	Vehicle::updateForce(this);
}

fix10_6 Vehicle::getRadius()
{
	if(0 == this->radius)
	{
		this->radius = Base::getRadius(this);
	}

	return this->radius;
}
