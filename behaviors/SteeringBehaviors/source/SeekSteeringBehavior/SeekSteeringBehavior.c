/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <Vehicle.h>
#include <VirtualList.h>

#include "SeekSteeringBehavior.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

/**
 * Class constructor
 */
void SeekSteeringBehavior::constructor(SpatialObject owner, const SeekSteeringBehaviorSpec* seekSteeringBehaviorSpec)
{
	Base::constructor(owner, &seekSteeringBehaviorSpec->steeringBehaviorSpec);

	this->target = Vector3D::zero();
	this->slowDownWhenReachingTarget = false;
	this->reachedTarget = false;
	this->allowEasing = false;
	this->squaredReachedDistanceThreshold = __FIXED_SQUARE(seekSteeringBehaviorSpec->reachedDistanceThreshold);
	this->easingDistanceThreshold = seekSteeringBehaviorSpec->easingDistanceThreshold;
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

bool SeekSteeringBehavior::getAllowEasing()
{
	return this->allowEasing;
}

void SeekSteeringBehavior::setAllowEasing(bool value)
{
	this->allowEasing = value;
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
	this->force = Vector3D::zero();

	if(isDeleted(owner))
	{
		this->enabled = false;
		return this->force;
	}

	if(this->reachedTarget)
	{
		return this->force;
	}

	this->force = SeekSteeringBehavior::toTarget(this, owner, this->target, this->slowDownWhenReachingTarget, this->squaredReachedDistanceThreshold, this->easingDistanceThreshold, this->allowEasing);

	return this->force;
}

static Vector3D SeekSteeringBehavior::toTarget(SeekSteeringBehavior seekSteeringBehavior, Vehicle vehicle, Vector3D target, bool proportionalToDistance, fixed_ext_t squaredReachedDistanceThreshold, fixed_t easingDistanceThreshold, bool allowEasing)
{
	Vector3D trajectory = Vector3D::get(*Vehicle::getPosition(vehicle), target);
	fixed_ext_t squaredLength = Vector3D::squareLength(trajectory);

	if(0 == squaredLength || squaredLength < squaredReachedDistanceThreshold)
	{
		seekSteeringBehavior->reachedTarget = true;

		if(!isDeleted(seekSteeringBehavior->events))
		{
			SeekSteeringBehavior::fireEvent(seekSteeringBehavior, kTargetReached);
		}

		return Vector3D::zero();
	}

	fixed_t length = Math::squareRootFixed(squaredLength);

	fixed_t magnitude = Vehicle::getMaximumSpeed(vehicle);
	fixed_t desiredVelocityLength = __FIXED_DIV(magnitude, length) << 1;

	Vector3D desiredVelocity = Vector3D::scalarProduct(trajectory, desiredVelocityLength);

	if(proportionalToDistance)
	{
		desiredVelocity = Vector3D::get(*Vehicle::getVelocity(vehicle), desiredVelocity);

		if(allowEasing && easingDistanceThreshold > length)
		{
			fixed_t scaleFactor = __FIXED_EXT_TO_FIXED(__FIXED_EXT_MULT(magnitude, __FIXED_EXT_DIV(length, easingDistanceThreshold)));
			desiredVelocity = Vector3D::scalarProduct(desiredVelocity, scaleFactor);
		}
	}

	return desiredVelocity;
}

fixed_t SeekSteeringBehavior::getEasingDistanceThreshold()
{
	return this->easingDistanceThreshold;
}

void SeekSteeringBehavior::setEasingDistanceThreshold(fixed_t value)
{
	this->easingDistanceThreshold = value;
}

fixed_t SeekSteeringBehavior::getReachedDistanceThreshold()
{
	return Math::squareRootFixed(this->squaredReachedDistanceThreshold);
}

void SeekSteeringBehavior::setReachedDistanceThreshold(fixed_t value)
{
	this->squaredReachedDistanceThreshold = __FIXED_SQUARE(value);
}
