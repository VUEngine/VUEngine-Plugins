/* VUEngine - Virtual Utopia Engine <https://www.vuengine.dev>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>, 2007-2020
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
