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

#include <VUEngine.h>
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
void Vehicle::constructor(VehicleSpec* vehicleSpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorSpec*)&vehicleSpec->actorSpec, internalId, name);

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
	if(!isDeleted(this->steeringBehaviors))
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

	if(isDeleted(this->steeringBehaviors))
	{
		this->steeringBehaviors = new VirtualList();
	}

	// get steering behaviors to sort them based on their priority
	Container::getBehaviors(this, typeofclass(SteeringBehavior), this->steeringBehaviors);

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

void Vehicle::applyForce(const Force* force, bool checkIfCanMove __attribute__((unused)))
{
	this->checkIfCanMove |= checkIfCanMove;
	this->accumulatedForce = Vector3D::sum(this->accumulatedForce, *force);
}

int32 Vehicle::getSummingMethod()
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

fixed_t Vehicle::getFrictionMassRatio()
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
		uint16 modulo = __MODULO(this->evenCycle, 2);
		computeForce = 1 == modulo;
		this->evenCycle = !modulo;
	}

	Force totalForce = this->accumulatedForce;

	if(computeForce && this->behaviors)
	{
		totalForce = Vector3D::sum(totalForce, SteeringBehavior::calculateForce(this));
	}

	Base::applyForce(this, &totalForce, this->checkIfCanMove);

	this->accumulatedForce = Vector3D::zero();
	this->checkIfCanMove = false;

	return computeForce;
}

void Vehicle::update(uint32 elapsedTime __attribute__((unused)))
{
	Base::update(this, elapsedTime);

	Vehicle::updateForce(this);
}

fixed_t Vehicle::getRadius()
{
	if(0 == this->radius)
	{
		this->radius = Base::getRadius(this);
	}

	return this->radius;
}
