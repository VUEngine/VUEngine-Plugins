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

#include <Optics.h>
#include <Camera.h>
#include <MessageDispatcher.h>
#include <Actor.h>
#include <VUEngine.h>
#include <BodyManager.h>
#include <InverseBox.h>
#include <EventManager.h>
#include <Utilities.h>

#include "PlatformerCameraMovementManager.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

Vector3D PlatformerCameraMovementManager::focus(Camera camera)
{
	if(isDeleted(camera))
	{
		return Vector3D::zero()s;
	}

	return this->focusFunction(this, camera, false);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PlatformerCameraMovementManager::enable()
{
	this->focusFunction = this->previousFocusFunction;
	this->previousFocusFunction = this->focusFunction;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PlatformerCameraMovementManager::disable()
{
	if(&PlatformerCameraMovementManager::dontFocus != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &PlatformerCameraMovementManager::dontFocus;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PlatformerCameraMovementManager::enableFocusEasing()
{
	this->focusFunction = &PlatformerCameraMovementManager::doFocus;
	this->previousFocusFunction = this->focusFunction;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PlatformerCameraMovementManager::disableFocusEasing()
{
	this->focusFunction = &PlatformerCameraMovementManager::doFocusWithNoEasing;
	this->previousFocusFunction = this->focusFunction;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PlatformerCameraMovementManager::alertWhenTargetFocused()
{
	if(&PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PlatformerCameraMovementManager::dontAlertWhenTargetFocused()
{
	this->focusFunction = this->previousFocusFunction;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PlatformerCameraMovementManager::setPositionFlag(Vector3DFlag positionFlag)
{
	this->positionFlag = positionFlag;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

Vector3DFlag PlatformerCameraMovementManager::getPositionFlag()
{
	return this->positionFlag;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PlatformerCameraMovementManager::lockMovement(uint8 axisToLockUp, bool locked)
{
	if(!isDeleted(this->cameraTrigger))
	{
		PlatformerCameraTriggerActor::lockMovement(this->cameraTrigger, axisToLockUp, locked);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PlatformerCameraMovementManager::configure
(
	Actor focusActor, uint32 focusActorLayer, uint32 cameraTriggerLayer, PixelSize boundingBoxSize, 
	Vector3D boundingBoxDisplacement, Vector3D screenDisplacement
)
{
	this->platformerCameraTriggerActorCollidersSpec[0] = (ColliderSpec)
	{
		// Collider
		__TYPE(InverseBox),

		// Size (x, y, z)
		boundingBoxSize,

		// Displacement (x, y, z, p)
		{0, 0, 0, 0},

		// Rotation (x, y, z)
		{0, 0, 0},

		// Scale (x, y, z)
		{0, 0, 0},

		/// If true this collider checks for collisions against other colliders
		true,

		/// Layers in which I live
		cameraTriggerLayer,

		/// Layers to ignore when checking for collisions
		~(focusActorLayer),
	};

	this->platformerCameraTriggerActorCollidersSpec[1] = 
		(ColliderSpec) {NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone};

	this->platformerCameraTriggerActorSpec = (PlatformerCameraTriggerActorSpec)
	{
		// Class allocator
		__TYPE(PlatformerCameraTriggerActor),

		// Children
		NULL,

		// Behaviors
		NULL,

		// Extra
		NULL,

		// Sprites
		NULL,

		// Use z displacement in projection
		false,

		// Wireframes
		(WireframeSpec**)NULL,

		// Collision colliders
		(ColliderSpec*)this->platformerCameraTriggerActorCollidersSpec,

		// Size
		// If 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// Gameworld's character's type
		!isDeleted(focusActor) ? Actor::getInGameType(focusActor) : kTypeNone
	};

	if(!isDeleted(focusActor))
	{
		// Configure the camera
		Camera::setFocusActor(focusActor);
		Camera::setFocusActorPositionDisplacement(screenDisplacement);

		// Configure the camera trigger
		this->cameraTrigger = 
			Actor::spawnChildActor
			(
				focusActor, (ActorSpec*)&this->platformerCameraTriggerActorSpec, 0, NULL, &boundingBoxDisplacement, NULL
			);

		// Make sure that focusing gets completed immediately
		PlatformerCameraMovementManager::enable(this);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PlatformerCameraMovementManager::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	this->positionFlag.x = 0;
	this->positionFlag.y = 0;
	this->positionFlag.z = 0;

	this->cameraTrigger = NULL;
	this->focusFunction = &PlatformerCameraMovementManager::doFocus;
	this->previousFocusFunction = this->focusFunction;

	PlatformerCameraMovementManager::configure
	(
		this, NULL, kLayerNone, kLayerNone, (PixelSize){8 * 8, 8 * 8, 8 * 8}, Vector3D::zero(), Vector3D::zero()
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PlatformerCameraMovementManager::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

Vector3D PlatformerCameraMovementManager::doFocusWithNoEasing(Camera camera, uint32 introFocusing __attribute__ ((unused)))
{
	NormalizedDirection normalizedDirection = Actor::getNormalizedDirection(Actor::safeCast(Camera::getFocusActor(camera)));

	return cameraPosition =
	{
		this->focusActorPosition->x + normalizedDirection.x * Camera::getFocusActorPositionDisplacement(camera).x - 
		__PIXELS_TO_METERS(__SCREEN_WIDTH / 2),
		this->focusActorPosition->y + Camera::getFocusActorPositionDisplacement(camera).y - 
		__PIXELS_TO_METERS(__SCREEN_HEIGHT / 2),
		0
	};
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

Vector3D PlatformerCameraMovementManager::dontFocus(Camera camera __attribute__ ((unused)), uint32 introFocusing __attribute__ ((unused)))
{
	return Camera::getPosition(camera);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

Vector3D PlatformerCameraMovementManager::doFocus(Camera camera, uint32 introFocusing __attribute__ ((unused)))
{
	// If focusActor is defined
	if(!Camera::getFocusActor(camera))
	{
		return Camera::getPosition(camera);
	}

	Actor focusActor = Actor::safeCast(Camera::getFocusActor(camera));

	NormalizedDirection normalizedDirection = Actor::getNormalizedDirection(focusActor);

	Vector3D cameraNewPosition = Camera::getPosition(camera);

	Vector3DFlag reachedTargetFlag = {true, true, true};

	Vector3D position3D = Vector3D::getRelativeToCamera(*this->focusActorPosition);
	PixelVector position2D = PixelVector::projectVector3D(position3D, 0);

	Size stageSize = Camera::getStageSize(camera);

	{
		bool focusActorOutOfBounds = 
			(unsigned)(position2D.x - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION) 
			>
			(unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION);

		if(this->positionFlag.x | focusActorOutOfBounds)
		{
			// Calculate the target position
			fixed_t horizontalPosition = cameraNewPosition.x;
			fixed_t horizontalTarget = 
				this->focusActorPosition->x + normalizedDirection.x * this->focusActorPositionDisplacement.x - 
				__PIXELS_TO_METERS(__SCREEN_WIDTH / 2);

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
		bool focusActorOutOfBounds = 
			position2D.y > _cameraFrustum->y1 - SCREEN_HEIGHT_REDUCTION 
			||
			position2D.y < _cameraFrustum->y0 + SCREEN_HEIGHT_REDUCTION / 4;

		if(this->positionFlag.y | focusActorOutOfBounds)
		{
			// Calculate the target position
			fixed_t verticalPosition = cameraNewPosition.y;
			fixed_t verticalTarget = 
				this->focusActorPosition->y + this->focusActorPositionDisplacement.y - __PIXELS_TO_METERS(__SCREEN_HEIGHT / 2);

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

			if(focusActorOutOfBounds)
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

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

Vector3D PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached(Camera camera, uint32 introFocusing __attribute__ ((unused)))
{
	if(PlatformerCameraMovementManager::doFocus(this, camera, true))
	{
		EventManager::fireEvent(EventManager::getInstance(), kEventPlatformerCameraScreenFocused);
		NM_ASSERT
		(
			!isDeleted(EventManager::getInstance()), 
			"PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached: deleted actor manager during kEventPlatformerCameraScreenFocused"
		);
	}

	return Camera::getPosition(camera);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
