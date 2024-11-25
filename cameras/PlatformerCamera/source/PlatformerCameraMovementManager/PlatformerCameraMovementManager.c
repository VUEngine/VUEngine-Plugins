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

#include <Optics.h>
#include <Camera.h>
#include <MessageDispatcher.h>
#include <Actor.h>
#include <VUEngine.h>
#include <PhysicalWorld.h>
#include <InverseBox.h>
#include <EventManager.h>
#include <Utilities.h>

#include "PlatformerCameraMovementManager.h"


//=========================================================================================================
// CLASS' PUBLIC METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
Vector3D PlatformerCameraMovementManager::focus(Camera camera)
{
	if(isDeleted(camera))
	{
		return Vector3D::zero()s;
	}

	return this->focusFunction(this, camera, false);
}
//---------------------------------------------------------------------------------------------------------
void PlatformerCameraMovementManager::enable()
{
	this->focusFunction = this->previousFocusFunction;
	this->previousFocusFunction = this->focusFunction;
}
//---------------------------------------------------------------------------------------------------------
void PlatformerCameraMovementManager::disable()
{
	if(&PlatformerCameraMovementManager::dontFocus != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &PlatformerCameraMovementManager::dontFocus;
}
//---------------------------------------------------------------------------------------------------------
void PlatformerCameraMovementManager::enableFocusEasing()
{
	this->focusFunction = &PlatformerCameraMovementManager::doFocus;
	this->previousFocusFunction = this->focusFunction;
}
//---------------------------------------------------------------------------------------------------------
void PlatformerCameraMovementManager::disableFocusEasing()
{
	this->focusFunction = &PlatformerCameraMovementManager::doFocusWithNoEasing;
	this->previousFocusFunction = this->focusFunction;
}
//---------------------------------------------------------------------------------------------------------
void PlatformerCameraMovementManager::alertWhenTargetFocused()
{
	if(&PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached;
}
//---------------------------------------------------------------------------------------------------------
void PlatformerCameraMovementManager::dontAlertWhenTargetFocused()
{
	this->focusFunction = this->previousFocusFunction;
}
//---------------------------------------------------------------------------------------------------------
void PlatformerCameraMovementManager::setPositionFlag(Vector3DFlag positionFlag)
{
	this->positionFlag = positionFlag;
}
//---------------------------------------------------------------------------------------------------------
Vector3DFlag PlatformerCameraMovementManager::getPositionFlag()
{
	return this->positionFlag;
}
//---------------------------------------------------------------------------------------------------------
void PlatformerCameraMovementManager::lockMovement(uint8 axisToLockUp, bool locked)
{
	if(!isDeleted(this->cameraTrigger))
	{
		PlatformerCameraTriggerEntity::lockMovement(this->cameraTrigger, axisToLockUp, locked);
	}
}
//---------------------------------------------------------------------------------------------------------
void PlatformerCameraMovementManager::configure(Entity focusEntity, uint32 focusEntityLayer, uint32 cameraTriggerLayer, PixelSize boundingBoxSize, Vector3D boundingBoxDisplacement, Vector3D screenDisplacement)
{
	this->platformerCameraTriggerEntityCollidersSpec[0] = (ColliderSpec)
	{
		// collider
		__TYPE(InverseBox),

		// size (x, y, z)
		boundingBoxSize,

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		/// if true this collider checks for collisions against other colliders
		true,

		/// layers in which I live
		cameraTriggerLayer,

		/// layers to ignore when checking for collisions
		~(focusEntityLayer),
	};

	this->platformerCameraTriggerEntityCollidersSpec[1] = (ColliderSpec) {NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone};

	this->platformerCameraTriggerEntitySpec = (PlatformerCameraTriggerEntitySpec)
	{
		// class allocator
		__TYPE(PlatformerCameraTriggerEntity),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		NULL,

		// use z displacement in projection
		false,

		// wireframes
		(WireframeSpec**)NULL,

		// collision colliders
		(ColliderSpec*)this->platformerCameraTriggerEntityCollidersSpec,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		!isDeleted(focusEntity) ? Entity::getInGameType(focusEntity) : kTypeNone,

		// physical specification
		(PhysicalProperties*)NULL,
	};

	if(!isDeleted(focusEntity))
	{
		// Configure the camera
		Camera::setFocusEntity(Camera::getInstance(), focusEntity);
		Camera::setFocusEntityPositionDisplacement(Camera::getInstance(), screenDisplacement);

		// Configure the camera trigger
		this->cameraTrigger = Entity::spawnChildEntity(focusEntity, (EntitySpec*)&this->platformerCameraTriggerEntitySpec, 0, NULL, &boundingBoxDisplacement, NULL);

		// make sure that focusing gets completed immediately
		PlatformerCameraMovementManager::enable(this);
	}
}
//---------------------------------------------------------------------------------------------------------

//=========================================================================================================
// CLASS' PRIVATE METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
void PlatformerCameraMovementManager::constructor()
{
	// construct base object
	Base::constructor();

	this->positionFlag.x = 0;
	this->positionFlag.y = 0;
	this->positionFlag.z = 0;

	this->cameraTrigger = NULL;
	this->focusFunction = &PlatformerCameraMovementManager::doFocus;
	this->previousFocusFunction = this->focusFunction;

	PlatformerCameraMovementManager::configure(this, NULL, kLayerNone, kLayerNone, (PixelSize){8 * 8, 8 * 8, 8 * 8}, Vector3D::zero(), Vector3D::zero());
}
//---------------------------------------------------------------------------------------------------------
void PlatformerCameraMovementManager::destructor()
{
	// destroy base
	Base::destructor();
}
//---------------------------------------------------------------------------------------------------------
Vector3D PlatformerCameraMovementManager::doFocusWithNoEasing(Camera camera, uint32 introFocusing __attribute__ ((unused)))
{
	NormalizedDirection normalizedDirection = Entity::getNormalizedDirection(Entity::safeCast(Camera::getFocusEntity(camera)));

	return cameraPosition =
	{
		this->focusEntityPosition->x + normalizedDirection.x * Camera::getFocusEntityPositionDisplacement(camera).x - __PIXELS_TO_METERS(__SCREEN_WIDTH / 2),
		this->focusEntityPosition->y + Camera::getFocusEntityPositionDisplacement(camera).y - __PIXELS_TO_METERS(__SCREEN_HEIGHT / 2),
		0
	};
}
//---------------------------------------------------------------------------------------------------------
Vector3D PlatformerCameraMovementManager::dontFocus(Camera camera __attribute__ ((unused)), uint32 introFocusing __attribute__ ((unused)))
{
	return Camera::getPosition(camera);
}
//---------------------------------------------------------------------------------------------------------
Vector3D PlatformerCameraMovementManager::doFocus(Camera camera, uint32 introFocusing __attribute__ ((unused)))
{
	// if focusEntity is defined
	if(!Camera::getFocusEntity(camera))
	{
		return Camera::getPosition(camera);
	}

	Actor focusActor = Actor::safeCast(Camera::getFocusEntity(camera));

	NormalizedDirection normalizedDirection = Entity::getNormalizedDirection(focusActor);

	Vector3D cameraNewPosition = Camera::getPosition(camera);

	Vector3DFlag reachedTargetFlag = {true, true, true};

	Vector3D position3D = Vector3D::getRelativeToCamera(*this->focusEntityPosition);
	PixelVector position2D = PixelVector::projectVector3D(position3D, 0);

	Size stageSize = Camera::getStageSize(camera);

	{
		bool focusEntityOutOfBounds = (unsigned)(position2D.x - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION) > (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION);

		if(this->positionFlag.x | focusEntityOutOfBounds)
		{
			// calculate the target position
			fixed_t horizontalPosition = cameraNewPosition.x;
			fixed_t horizontalTarget = this->focusEntityPosition->x + normalizedDirection.x * this->focusEntityPositionDisplacement.x - __PIXELS_TO_METERS(__SCREEN_WIDTH / 2);

			fixed_t easingDisplacement = __PIXELS_TO_METERS(7);

			if(introFocusing)
			{
				easingDisplacement = __PIXELS_TO_METERS(1);
			}

			reachedTargetFlag.x = false;

			if(horizontalPosition + easingDisplacement < horizontalTarget)
			{
				cameraNewPosition.x += easingDisplacement;
			}
			else if(horizontalPosition - easingDisplacement > horizontalTarget)
			{
				cameraNewPosition.x -= easingDisplacement;
			}
			else
			{
				cameraNewPosition.x = horizontalTarget;
				reachedTargetFlag.x = true;
			}

			if(0 > cameraNewPosition.x)
			{
				reachedTargetFlag.x = true;
			}
			else if(stageSize.x < cameraNewPosition.x + __PIXELS_TO_METERS(__SCREEN_WIDTH))
			{
				reachedTargetFlag.x = true;
			}
		}
	}

	{
		bool focusEntityOutOfBounds = position2D.y > _cameraFrustum->y1 - SCREEN_HEIGHT_REDUCTION || position2D.y < _cameraFrustum->y0 + SCREEN_HEIGHT_REDUCTION / 4;

		if(this->positionFlag.y | focusEntityOutOfBounds)
		{
			// calculate the target position
			fixed_t verticalPosition = cameraNewPosition.y;
			fixed_t verticalTarget = this->focusEntityPosition->y + this->focusEntityPositionDisplacement.y - __PIXELS_TO_METERS(__SCREEN_HEIGHT / 2);

			fixed_t downEasingDisplacement = __PIXELS_TO_METERS(3);
			fixed_t upEasingDisplacement = __PIXELS_TO_METERS(3);

			if(introFocusing)
			{
				downEasingDisplacement = __PIXELS_TO_METERS(1);
				upEasingDisplacement = __PIXELS_TO_METERS(1);
			}
			else
			{
				Vector3D velocity = *Actor::getVelocity(focusActor);

				if(0 < velocity.y)
				{
					downEasingDisplacement = __PIXELS_TO_METERS(8);
				}
			}

			reachedTargetFlag.y = false;

			if(focusEntityOutOfBounds)
			{
				this->positionFlag.y = true;
			}

			if(verticalPosition + downEasingDisplacement < verticalTarget)
			{
				cameraNewPosition.y += downEasingDisplacement;
			}
			else if(verticalPosition - upEasingDisplacement > verticalTarget)
			{
				cameraNewPosition.y -= upEasingDisplacement;
			}
			else
			{
				cameraNewPosition.y = verticalTarget;
				this->positionFlag.y = false;
				reachedTargetFlag.y = true;
			}

			if(0 > cameraNewPosition.y)
			{
				reachedTargetFlag.y = true;
			}
			else if(stageSize.y < cameraNewPosition.y + __PIXELS_TO_METERS(__SCREEN_HEIGHT))
			{
				reachedTargetFlag.y = true;
			}
		}
	}

	if(reachedTargetFlag.x && reachedTargetFlag.y)
	{
		return cameraNewPosition;
	}

	return Camera::getPosition(camera);
}
//---------------------------------------------------------------------------------------------------------
Vector3D PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached(Camera camera, uint32 introFocusing __attribute__ ((unused)))
{
	if(PlatformerCameraMovementManager::doFocus(this, camera, true))
	{
		EventManager::fireEvent(EventManager::getInstance(), kEventScreenFocused);
		NM_ASSERT(!isDeleted(EventManager::getInstance()), "PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached: deleted entity manager during kEventScreenFocused");
	}

	return Camera::getPosition(camera);
}
//---------------------------------------------------------------------------------------------------------
