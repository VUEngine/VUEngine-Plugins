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

#include <Vehicle.h>
#include <VirtualList.h>

#include "BrakeSteeringBehavior.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static Vector3D BrakeSteeringBehavior::toTarget(BrakeSteeringBehavior seekSteeringBehavior, Vehicle vehicle)
{
	fixed_t magnitude = __FIXED_DIV(Vehicle::getSpeed(vehicle), Vehicle::getFrictionMassRatio(vehicle));

	if(seekSteeringBehavior->strength)
	{
		magnitude = __FIXED_MULT(magnitude, seekSteeringBehavior->strength);
	}

	return Vector3D::scalarProduct(*Vehicle::getDirection(vehicle), -magnitude);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void BrakeSteeringBehavior::constructor(GameObject owner, const BrakeSteeringBehaviorSpec* brakeSteeringBehaviorSpec)
{
	// Always explicitly call the base's constructor 
	Base::constructor(owner, &brakeSteeringBehaviorSpec->steeringBehaviorSpec);

	this->strength = 0;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void BrakeSteeringBehavior::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

Vector3D BrakeSteeringBehavior::calculate(Vehicle owner)
{
	this->force = Vector3D::zero();

	if(isDeleted(owner))
	{
		this->enabled = false;
		return this->force;
	}

	this->force = BrakeSteeringBehavior::toTarget(this, owner);

	return this->force;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void BrakeSteeringBehavior::setStrength(fixed_t value)
{
	this->strength = __ABS(value);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

fixed_t BrakeSteeringBehavior::getStrength()
{
	return this->strength;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
