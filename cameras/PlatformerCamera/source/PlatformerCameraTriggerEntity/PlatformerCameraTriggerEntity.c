/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <PlatformerCameraTriggerEntity.h>
#include <CollisionManager.h>
#include <Optics.h>
#include <Collider.h>
#include <Camera.h>
#include <InverseBox.h>
#include <PlatformerLevelState.h>
#include <PlatformerCameraMovementManager.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void PlatformerCameraTriggerEntity::constructor(PlatformerCameraTriggerEntitySpec* cameraEntitySpec, int16 internalId, const char* const name)
{
	ASSERT(cameraEntitySpec, "PlatformerCameraTriggerEntity::constructor: null spec");

	// construct base object
	Base::constructor((EntitySpec*)cameraEntitySpec, internalId, name);

	this->overridePositionFlag.x = false;
	this->overridePositionFlag.y = false;
	this->overridePositionFlag.z = false;

	this->normalizedDirection.x = __RIGHT;
	this->normalizedDirection.y = __DOWN;
	this->normalizedDirection.z = __FAR;

	this->previousGlobalPosition = (Vector3D) {0, 0, 0};
}

// class's destructor
void PlatformerCameraTriggerEntity::destructor()
{
	Camera::setFocusEntity(Camera::getInstance(), NULL);

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void PlatformerCameraTriggerEntity::ready(bool recursive)
{
	Base::ready(this, recursive);

	Entity::checkCollisions(this, true);
}

void PlatformerCameraTriggerEntity::transform(const Transformation* environmentTransform, uint8 invalidateTransformationFlag)
{
	Vector3D currentGlobalPosition = this->transformation.position;

	Base::transform(this, environmentTransform, invalidateTransformationFlag);

	if(this->overridePositionFlag.x)
	{
		this->transformation.position.x = currentGlobalPosition.x;
	}

	if(this->overridePositionFlag.y)
	{
		this->transformation.position.y = currentGlobalPosition.y;
	}
}

void PlatformerCameraTriggerEntity::update()
{
	Base::update(this);

	// If there is a change in direction over the X axis
	int8 currentXDirection = this->transformation.position.x > this->previousGlobalPosition.x ? __RIGHT : this->transformation.position.x < this->previousGlobalPosition.x ? __LEFT : 0;

	if(currentXDirection)
	{
		if(currentXDirection != this->normalizedDirection.x)
		{
			PlatformerCameraTriggerEntity::lockMovement(this, __X_AXIS, true);
			this->normalizedDirection.x = currentXDirection;
		}

		this->previousGlobalPosition = this->transformation.position;
	}
}

void PlatformerCameraTriggerEntity::resume()
{
	Base::resume(this);

	Camera::focus(Camera::getInstance());

	Vector3DFlag positionFlag = {true, true, true};
	PlatformerCameraMovementManager::setPositionFlag(PlatformerCameraMovementManager::getInstance(), positionFlag);

	PlatformerCameraTriggerEntity::lockMovement(this, __X_AXIS | __Y_AXIS, true);
}

void PlatformerCameraTriggerEntity::lockMovement(uint8 axisToLockUp, bool locked)
{
	Vector3DFlag overridePositionFlag = PlatformerCameraTriggerEntity::getOverridePositionFlag(this);

	Vector3DFlag positionFlag = PlatformerCameraMovementManager::getPositionFlag(PlatformerCameraMovementManager::getInstance());

	if(__X_AXIS & axisToLockUp)
	{
		overridePositionFlag.x = locked;

		positionFlag.x = !locked;
	}

	if(__Y_AXIS & axisToLockUp)
	{
		overridePositionFlag.y = locked;
	}

	PlatformerCameraTriggerEntity::setOverridePositionFlag(this, overridePositionFlag);
	PlatformerCameraMovementManager::setPositionFlag(PlatformerCameraMovementManager::getInstance(), positionFlag);
}

void PlatformerCameraTriggerEntity::setOverridePositionFlag(Vector3DFlag overridePositionFlag)
{
	Container::invalidateGlobalPosition(this);

	Transformation* environmentTransform = Container::getTransform(this->parent);

	// don't lock yet, allow the global position to be calculated before locking
	this->overridePositionFlag.y = false;
	PlatformerCameraTriggerEntity::transform(this, environmentTransform, __INVALIDATE_TRANSFORMATION);

	this->overridePositionFlag = overridePositionFlag;
}

Vector3DFlag PlatformerCameraTriggerEntity::getOverridePositionFlag()
{
	return this->overridePositionFlag;
}

// process collisions
bool PlatformerCameraTriggerEntity::enterCollision(const CollisionInformation* collisionInformation)
{
	ASSERT(collisionInformation->otherCollider, "PlatformerCameraTriggerEntity::enterCollision: null collidingObjects");

#define CAMERA_BOUNDING_BOX_DISPLACEMENT	{__PIXELS_TO_METERS(0), __PIXELS_TO_METERS(-24/16), __PIXELS_TO_METERS(0)}

	if(collisionInformation->solutionVector.direction.y)
	{
		PlatformerCameraTriggerEntity::lockMovement(this, __Y_AXIS, false);
	}

	if(collisionInformation->solutionVector.direction.x)
	{
		PlatformerCameraTriggerEntity::lockMovement(this, __X_AXIS, false);
	}
	else
	{
		PlatformerCameraTriggerEntity::lockMovement(this, __Y_AXIS, false);
	}

	Vector3D position = CAMERA_BOUNDING_BOX_DISPLACEMENT;

	Container::setLocalPosition(this, &position);

	return false;
}

