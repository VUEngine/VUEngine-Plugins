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

#include <BrakeSteeringBehavior.h>
#include <Vehicle.h>
#include <VirtualList.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

/**
 * Class constructor
 */
void BrakeSteeringBehavior::constructor(const BrakeSteeringBehaviorSpec* brakeSteeringBehaviorSpec)
{
	Base::constructor(&brakeSteeringBehaviorSpec->steeringBehaviorSpec);

	this->strength = 0;
}

/**
 * Class destructor
 */
void BrakeSteeringBehavior::destructor()
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

fix10_6 BrakeSteeringBehavior::getStrength()
{
	return this->strength;
}

void BrakeSteeringBehavior::setStrength(fix10_6 value)
{
	this->strength = __ABS(value);
}

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

static Vector3D BrakeSteeringBehavior::toTarget(BrakeSteeringBehavior seekSteeringBehavior, Vehicle vehicle)
{
	fix10_6 magnitude = __FIX10_6_DIV(Vehicle::getSpeed(vehicle), Vehicle::getFrictionMassRatio(vehicle));

	if(seekSteeringBehavior->strength)
	{
		magnitude = __FIX10_6_MULT(magnitude, seekSteeringBehavior->strength);
	}

	return Vector3D::scalarProduct(*Vehicle::getDirection3D(vehicle), -magnitude);
}
