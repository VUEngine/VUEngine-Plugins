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

#include <SeekSteeringBehavior.h>
#include <Vehicle.h>
#include <VirtualList.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

/**
 * Class constructor
 */
void SeekSteeringBehavior::constructor(const SeekSteeringBehaviorSpec* seekSteeringBehaviorSpec)
{
	Base::constructor(&seekSteeringBehaviorSpec->steeringBehaviorSpec);

	this->target = Vector3D::zero();
	this->slowDownWhenReachingTarget = true;
	this->reachedTarget = false;
}

/**
 * Class destructor
 */
void SeekSteeringBehavior::destructor()
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

Vector3D SeekSteeringBehavior::getTarget()
{
	return this->target;
}

void SeekSteeringBehavior::setTarget(Vector3D value)
{
	this->target = value;
	this->reachedTarget = false;
}

bool SeekSteeringBehavior::getSlowDownWhenReachingTarget()
{
	return this->slowDownWhenReachingTarget;
}

void SeekSteeringBehavior::setSlowDownWhenReachingTarget(bool value)
{
	this->slowDownWhenReachingTarget = value;
}

Vector3D SeekSteeringBehavior::calculate(Vehicle owner)
{
	if(isDeleted(owner))
	{
		this->enabled = false;
		return Vector3D::zero();
	}

	if(this->reachedTarget)
	{
		return Vector3D::zero();
	}

	return SeekSteeringBehavior::toTarget(this, owner, this->target, this->slowDownWhenReachingTarget, this->reachedDistanceThreshold, this->easingDistanceThreshold);
}

static Vector3D SeekSteeringBehavior::toTarget(SeekSteeringBehavior seekSteeringBehavior, Vehicle vehicle, Vector3D target, bool proportionalToDistance, fix10_6 reachedDistanceThreshold, fix10_6 easingDistanceThreshold)
{
	Vector3D trajectory = Vector3D::get(target, *Vehicle::getPosition(vehicle));
	fix10_6 length = Vector3D::length(trajectory);

	if(!length || length < reachedDistanceThreshold)
	{
		if(!seekSteeringBehavior->reachedTarget)
		{
			seekSteeringBehavior->reachedTarget = true;
			SeekSteeringBehavior::fireEvent(seekSteeringBehavior, kTargetReached);
		}

		return Vector3D::zero();
	}

	fix10_6 magnitude = Vehicle::getMaximumSpeed(vehicle);

	Vector3D desiredVelocity = Vector3D::scalarProduct(Vector3D::scalarDivision(trajectory, length), magnitude);
	
	if(proportionalToDistance)
	{
		desiredVelocity = Vector3D::get(desiredVelocity, Vehicle::getVelocity(vehicle));
		
		if(easingDistanceThreshold > length)
		{
			fix10_6 scaleFactor = __FIX10_6_EXT_TO_FIX10_6(__FIX10_6_EXT_MULT(magnitude, __FIX10_6_EXT_DIV(length, easingDistanceThreshold)));
			desiredVelocity = Vector3D::scalarProduct(desiredVelocity, scaleFactor);
		}
	}

	return desiredVelocity;
}
