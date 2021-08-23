/*
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
	this->slowDownWhenReachingTarget = false;
	this->reachedTarget = false;
	this->allowEasing = false;
	this->reachedDistanceThreshold = seekSteeringBehaviorSpec->reachedDistanceThreshold;
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

	this->force = SeekSteeringBehavior::toTarget(this, owner, this->target, this->slowDownWhenReachingTarget, this->reachedDistanceThreshold, this->easingDistanceThreshold, this->allowEasing);

	return this->force;
}

static Vector3D SeekSteeringBehavior::toTarget(SeekSteeringBehavior seekSteeringBehavior, Vehicle vehicle, Vector3D target, bool proportionalToDistance, fix10_6 reachedDistanceThreshold, fix10_6 easingDistanceThreshold, bool allowEasing)
{
	Vector3D trajectory = Vector3D::get(*Vehicle::getReferencePosition(vehicle), target);
	fix10_6 length = Vector3D::length(trajectory);

	if(!length || length < reachedDistanceThreshold)
	{
		seekSteeringBehavior->reachedTarget = true;
		SeekSteeringBehavior::fireEvent(seekSteeringBehavior, kTargetReached);
		NM_ASSERT(!isDeleted(seekSteeringBehavior), "SeekSteeringBehavior::toTarget: deleted seekSteeringBehavior during kTargetReached");
		return Vector3D::zero();
	}

	fix10_6 magnitude = Vehicle::getMaximumSpeed(vehicle);
	fix10_6 desiredVelocityLength = __FIX10_6_DIV(magnitude, length);

	Vector3D desiredVelocity = Vector3D::scalarProduct(trajectory, desiredVelocityLength);

	if(proportionalToDistance)
	{
		desiredVelocity = Vector3D::get(Vehicle::getVelocity(vehicle), desiredVelocity);

		if(allowEasing && easingDistanceThreshold > length)
		{
			fix10_6 scaleFactor = __FIX10_6_EXT_TO_FIX10_6(__FIX10_6_EXT_MULT(magnitude, __FIX10_6_EXT_DIV(length, easingDistanceThreshold)));
			desiredVelocity = Vector3D::scalarProduct(desiredVelocity, scaleFactor);
		}
	}

	return desiredVelocity;
}

fix10_6 SeekSteeringBehavior::getEasingDistanceThreshold()
{
	return this->easingDistanceThreshold;
}

void SeekSteeringBehavior::setEasingDistanceThreshold(fix10_6 value)
{
	this->easingDistanceThreshold = value;
}

fix10_6 SeekSteeringBehavior::getReachedDistanceThreshold()
{
	return this->reachedDistanceThreshold;
}

void SeekSteeringBehavior::setReachedDistanceThreshold(fix10_6 value)
{
	this->reachedDistanceThreshold = value;
}
