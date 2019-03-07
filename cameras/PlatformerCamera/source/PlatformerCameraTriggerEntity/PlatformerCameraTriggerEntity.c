/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

#include <PlatformerCameraTriggerEntity.h>
#include <CollisionManager.h>
#include <Optics.h>
#include <Shape.h>
#include <Camera.h>
#include <InverseBox.h>
#include <PlatformerLevelState.h>
#include <PlatformerCameraMovementManager.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void PlatformerCameraTriggerEntity::constructor(PlatformerCameraTriggerEntitySpec* cameraEntitySpec, s16 id, s16 internalId, const char* const name)
{
	ASSERT(cameraEntitySpec, "PlatformerCameraTriggerEntity::constructor: null spec");

	// construct base object
	Base::constructor((EntitySpec*)cameraEntitySpec, id, internalId, name);

	this->overridePositionFlag.x = false;
	this->overridePositionFlag.y = false;
	this->overridePositionFlag.z = false;

	this->direction.x = __RIGHT;
	this->direction.y = __DOWN;
	this->direction.z = __FAR;

	this->previousGlobalPosition = (Vector3D) {0, 0, 0};

	PlatformerCameraTriggerEntity::lockMovement(this, __X_AXIS | __Y_AXIS, false);
}

// class's destructor
void PlatformerCameraTriggerEntity::destructor()
{
	Camera::setFocusGameEntity(Camera::getInstance(), NULL);

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void PlatformerCameraTriggerEntity::ready(bool recursive)
{
	Base::ready(this, recursive);

	Entity::activeCollisionChecks(this, true);
}

void PlatformerCameraTriggerEntity::transform(const Transformation* environmentTransform, u8 invalidateTransformationFlag)
{
	Vector3D currentGlobalPosition = this->transformation.globalPosition;

	Base::transform(this, environmentTransform, invalidateTransformationFlag);

	if(this->overridePositionFlag.x)
	{
		this->transformation.globalPosition.x = currentGlobalPosition.x;
	}

	if(this->overridePositionFlag.y)
	{
		this->transformation.globalPosition.y = currentGlobalPosition.y;
	}

	Entity::transformShapes(this);

//	Entity::showShapes(this);
}

void PlatformerCameraTriggerEntity::update(u32 elapsedTime)
{
	Base::update(this, elapsedTime);

	// If there is a change in direction over the X axis
	s8 currentXDirection = this->transformation.globalPosition.x > this->previousGlobalPosition.x ? __RIGHT : this->transformation.globalPosition.x < this->previousGlobalPosition.x ? __LEFT : 0;

	if(currentXDirection)
	{
		if(currentXDirection != this->direction.x)
		{
			PlatformerCameraTriggerEntity::lockMovement(this, __X_AXIS, true);
			this->direction.x = currentXDirection;
		}

		this->previousGlobalPosition = this->transformation.globalPosition;
	}
}

void PlatformerCameraTriggerEntity::resume()
{
	Base::resume(this);

	Camera::focus(Camera::getInstance(), false);

	Vector3DFlag positionFlag = {true, true, true};
	PlatformerCameraMovementManager::setPositionFlag(PlatformerCameraMovementManager::getInstance(), positionFlag);

	PlatformerCameraTriggerEntity::lockMovement(this, __X_AXIS | __Y_AXIS, true);
}

void PlatformerCameraTriggerEntity::lockMovement(u8 axisToLockUp, bool locked)
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
	ASSERT(collisionInformation->collidingShape, "PlatformerCameraTriggerEntity::enterCollision: null collidingObjects");

	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

#define CAMERA_BOUNDING_BOX_DISPLACEMENT	{__PIXELS_TO_METERS(0), __PIXELS_TO_METERS(-24/16), __PIXELS_TO_METERS(0)}

	switch(SpatialObject::getInGameType(collidingObject))
	{

		case kNoType + 1:
			{
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
			}
			return false;
			break;

	}

	return false;
}

