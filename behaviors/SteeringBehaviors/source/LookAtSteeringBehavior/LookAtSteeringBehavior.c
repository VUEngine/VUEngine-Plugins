/*
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

#include "LookAtSteeringBehavior.h"


//=========================================================================================================
// CLASS' STATIC METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
static Vector3D LookAtSteeringBehavior::toTarget(LookAtSteeringBehavior LookAtSteeringBehavior, Vehicle vehicle, Vector3D target, bool proportionalToDistance, fixed_t reachedDistanceThreshold, fixed_t easingDistanceThreshold, bool allowEasing)
{
	Vector3D trajectory = Vector3D::get(*Vehicle::getPosition(vehicle), target);
	fixed_t length = Vector3D::length(trajectory);

	if(!length || length < reachedDistanceThreshold)
	{
		LookAtSteeringBehavior->reachedTarget = true;
		LookAtSteeringBehavior::fireEvent(LookAtSteeringBehavior, kTargetReached);
		NM_ASSERT(!isDeleted(LookAtSteeringBehavior), "LookAtSteeringBehavior::toTarget: deleted LookAtSteeringBehavior during kTargetReached");
		return Vector3D::zero();
	}

	fixed_t magnitude = Vehicle::getMaximumSpeed(vehicle);
	fixed_t desiredVelocityLength = __FIXED_DIV(magnitude, length)<< 1;

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
//---------------------------------------------------------------------------------------------------------

//=========================================================================================================
// CLASS' PUBLIC METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
void LookAtSteeringBehavior::constructor(SpatialObject owner, const LookAtSteeringBehaviorSpec* lookAtSteeringBehaviorSpec)
{
	Base::constructor(owner, &lookAtSteeringBehaviorSpec->steeringBehaviorSpec);

	this->target = Vector3D::zero();
	this->slowDownWhenReachingTarget = false;
	this->reachedTarget = false;
	this->reachedDistanceThreshold = lookAtSteeringBehaviorSpec->reachedDistanceThreshold;
	this->easingDistanceThreshold = lookAtSteeringBehaviorSpec->easingDistanceThreshold;
}
//---------------------------------------------------------------------------------------------------------
void LookAtSteeringBehavior::destructor()
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}
//---------------------------------------------------------------------------------------------------------
Vector3D LookAtSteeringBehavior::calculate(Vehicle owner)
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

	this->force = LookAtSteeringBehavior::toTarget(this, owner, this->target, this->slowDownWhenReachingTarget, this->reachedDistanceThreshold, this->easingDistanceThreshold, this->allowEasing);

	return this->force;
}
//---------------------------------------------------------------------------------------------------------
void LookAtSteeringBehavior::setTarget(Vector3D value)
{
	this->target = value;
	this->reachedTarget = false;
}
//---------------------------------------------------------------------------------------------------------
Vector3D LookAtSteeringBehavior::getTarget()
{
	return this->target;
}
//---------------------------------------------------------------------------------------------------------
void LookAtSteeringBehavior::setReachedDistanceThreshold(fixed_t reachedDistanceThreshold)
{
	this->reachedDistanceThreshold = reachedDistanceThreshold;
}
//---------------------------------------------------------------------------------------------------------
fixed_t LookAtSteeringBehavior::getReachedDistanceThreshold()
{
	return this->reachedDistanceThreshold;
}
//---------------------------------------------------------------------------------------------------------
void LookAtSteeringBehavior::setEasingDistanceThreshold(fixed_t easingDistanceThreshold)
{
	this->easingDistanceThreshold = easingDistanceThreshold;
}
//---------------------------------------------------------------------------------------------------------
fixed_t LookAtSteeringBehavior::getEasingDistanceThreshold()
{
	return this->easingDistanceThreshold;
}
//---------------------------------------------------------------------------------------------------------
void LookAtSteeringBehavior::setSlowDownWhenReachingTarget(bool value)
{
	this->slowDownWhenReachingTarget = value;
}
//---------------------------------------------------------------------------------------------------------
bool LookAtSteeringBehavior::getSlowDownWhenReachingTarget()
{
	return this->slowDownWhenReachingTarget;
}
//---------------------------------------------------------------------------------------------------------
void LookAtSteeringBehavior::setAllowEasing(bool allowEasing)
{
	this->allowEasing = allowEasing;
}
//---------------------------------------------------------------------------------------------------------
bool LookAtSteeringBehavior::getAllowEasing()
{
	return this->allowEasing;
}
//---------------------------------------------------------------------------------------------------------
