/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Body.h>
#include <SteeringBehavior.h>
#include <VirtualList.h>
#include <VirtualNode.h>
#include <VUEngine.h>

#include "Vehicle.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

friend class VirtualNode;
friend class VirtualList;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void Vehicle::constructor(VehicleSpec* vehicleSpec, int16 internalId, const char* const name)
{
	// construct base
	// Always explicitly call the base's constructor 
	Base::constructor((StatefulActorSpec*)&vehicleSpec->statefulActorSpec, internalId, name);

	// save vehicle spec
	this->steeringBehaviors = NULL;
	this->evenCycle = vehicleSpec->runSteeringBehaviorsAtHalfSpeed ? 0 : -1;
	this->accumulatedForce = Vector3D::zero();
	this->radius = 0;
	this->checkIfCanMove = false;

	if(isDeleted(this->body))
	{
		this->frictionMassRatio = 0;
	}
	else
	{
		this->frictionMassRatio = Body::getFrictionCoefficient(this->body) + Body::getMass(this->body);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void Vehicle::destructor()
{
	if(!isDeleted(this->steeringBehaviors))
	{
		delete this->steeringBehaviors;
		this->steeringBehaviors = NULL;
	}

	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

fixed_t Vehicle::getRadius()
{
	if(0 == this->radius)
	{
		this->radius = Base::getRadius(this);
	}

	return this->radius;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void Vehicle::ready(bool recursive)
{
	Base::ready(this, recursive);

	this->radius = Vehicle::getRadius(this);

	if(isDeleted(this->steeringBehaviors))
	{
		this->steeringBehaviors = new VirtualList();
	}

	// get steering behaviors to sort them based on their priority
	Vehicle::getComponentsOfClass(this, typeofclass(SteeringBehavior), this->steeringBehaviors, kBehaviorComponent);

	if(NULL == this->steeringBehaviors->head)
	{
		delete this->steeringBehaviors;
#ifndef __SILENT_CRASHES
		this->steeringBehaviors = NULL;
#else
#if __SILENT_CRASHES
		this->steeringBehaviors = this->steeringBehaviors;
#else
		this->steeringBehaviors = NULL;
#endif
#endif
	}
	else
	{
		VirtualNode node = this->steeringBehaviors->head;

		// just an easy bubble sort
		for(; NULL != node; node = node->next)
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
	}

	//m_headingSmoother = new BLGSmoother(m_iSamplesForSmoothing, new Vector3(0.0F, 0.0F, 0.0F));
	if(0 <= this->evenCycle)
	{
		this->evenCycle = this->internalId % 2;
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void Vehicle::update()
{
	Base::update(this);

	Vehicle::updateForce(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool Vehicle::applyForce(const Vector3D* force, bool checkIfCanMove __attribute__((unused)))
{
	this->checkIfCanMove |= checkIfCanMove;
	this->accumulatedForce = Vector3D::sum(this->accumulatedForce, *force);

	return true;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

VirtualList Vehicle::getSteeringBehaviors()
{
	return this->steeringBehaviors;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

fixed_t Vehicle::getFrictionMassRatio()
{
	return this->frictionMassRatio;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool Vehicle::updateForce()
{
	bool computeForce = 0 > this->evenCycle;

	if(!computeForce)
	{
		uint16 modulo = __MODULO(this->evenCycle, 2);
		computeForce = 1 == modulo;
		this->evenCycle = !modulo;
	}

	Vector3D totalForce = this->accumulatedForce;

	if(computeForce && NULL != this->steeringBehaviors)
	{
		totalForce = 
			Vector3D::sum(totalForce, SteeringBehavior::calculateForce(this, ((VehicleSpec*)this->actorSpec)->summingMethod));
	}

	Base::applyForce(this, &totalForce, this->checkIfCanMove);

	this->accumulatedForce = Vector3D::zero();
	this->checkIfCanMove = false;

	return computeForce;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
