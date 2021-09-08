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

#include <GameEvents.h>
#include <PlatformerCameraMovementManager.h>
#include <Optics.h>
#include <Camera.h>
#include <MessageDispatcher.h>
#include <Actor.h>
#include <Game.h>
#include <PhysicalWorld.h>
#include <InverseBox.h>
#include <EventManager.h>
#include <Utilities.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
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

	this->camera = Camera::getInstance();

	PlatformerCameraMovementManager::configure(this, NULL, kLayerNone, kLayerNone, (PixelSize){8 * 8, 8 * 8, 8 * 8}, Vector3D::zero(), Vector3D::zero());

	NM_ASSERT(this->camera, "PlatformerCameraMovementManager::constructor: null this->camera");
}

// class's destructor
void PlatformerCameraMovementManager::destructor()
{
	// destroy base
	Base::destructor();
}

// center world's this->camera in function of focus actor's position
void PlatformerCameraMovementManager::focus(uint32 checkIfFocusEntityIsMoving __attribute__ ((unused)))
{
	this->focusFunction(this, checkIfFocusEntityIsMoving, false);
}

bool PlatformerCameraMovementManager::doFocusWithNoEasing(uint32 checkIfFocusEntityIsMoving __attribute__ ((unused)), uint32 introFocusing __attribute__ ((unused)))
{
	Vector3D focusEntityPosition = Camera::getFocusEntityPosition(this->camera);
	Direction direction = Entity::getDirection(Entity::safeCast(Camera::getFocusEntity(this->camera)));

	Vector3D cameraPosition =
	{
		focusEntityPosition.x + direction.x * Camera::getFocusEntityPositionDisplacement(this->camera).x - __PIXELS_TO_METERS(__SCREEN_WIDTH / 2),
		focusEntityPosition.y + Camera::getFocusEntityPositionDisplacement(this->camera).y - __PIXELS_TO_METERS(__SCREEN_HEIGHT / 2),
		0
	};

	Camera::setPosition(this->camera, cameraPosition);

	return true;
}

// center world's this->camera in function of focus actor's position
bool PlatformerCameraMovementManager::dontFocus(uint32 checkIfFocusEntityIsMoving __attribute__ ((unused)), uint32 introFocusing __attribute__ ((unused)))
{
	return false;
}

// center world's this->camera in function of focus actor's position
bool PlatformerCameraMovementManager::doFocus(uint32 checkIfFocusEntityIsMoving __attribute__ ((unused)), uint32 introFocusing __attribute__ ((unused)))
{
	// if focusEntity is defined
	if(!Camera::getFocusEntity(this->camera))
	{
		return false;
	}

	Actor focusActor = Actor::safeCast(Camera::getFocusEntity(this->camera));

	Direction direction = Entity::getDirection(focusActor);

	Vector3D cameraNewPosition = Camera::getPosition(this->camera);

	Vector3DFlag reachedTargetFlag = {true, true, true};

	Vector3D focusEntityPosition = Camera::getFocusEntityPosition(this->camera);
	Vector3D focusEntityPositionDisplacement = Camera::getFocusEntityPositionDisplacement(this->camera);

	Vector3D position3D = Vector3D::getRelativeToCamera(focusEntityPosition);
	PixelVector position2D = Vector3D::projectToPixelVector(position3D, 0);

	Size stageSize = Camera::getStageSize(this->camera);

	{
		bool focusEntityOutOfBounds = (unsigned)(position2D.x - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION) > (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION);

		if(this->positionFlag.x | focusEntityOutOfBounds)
		{
			// calculate the target position
			fix10_6 horizontalPosition = cameraNewPosition.x;
			fix10_6 horizontalTarget = focusEntityPosition.x + direction.x * focusEntityPositionDisplacement.x - __PIXELS_TO_METERS(__SCREEN_WIDTH / 2);

			fix10_6 easingDisplacement = __PIXELS_TO_METERS(7);

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
			fix10_6 verticalPosition = cameraNewPosition.y;
			fix10_6 verticalTarget = focusEntityPosition.y + focusEntityPositionDisplacement.y - __PIXELS_TO_METERS(__SCREEN_HEIGHT / 2);

			fix10_6 downEasingDisplacement = __PIXELS_TO_METERS(3);
			fix10_6 upEasingDisplacement = __PIXELS_TO_METERS(3);

			if(introFocusing)
			{
				downEasingDisplacement = __PIXELS_TO_METERS(1);
				upEasingDisplacement = __PIXELS_TO_METERS(1);
			}
			else
			{
				Velocity velocity = Actor::getVelocity(focusActor);

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

	Camera::setPosition(this->camera, cameraNewPosition);

	if(reachedTargetFlag.x && reachedTargetFlag.y)
	{
		return true;
	}

	return false;
}

// center world's this->camera in function of focus actor's position
bool PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached(uint32 checkIfFocusEntityIsMoving __attribute__ ((unused)), uint32 introFocusing __attribute__ ((unused)))
{
	if(PlatformerCameraMovementManager::doFocus(this, checkIfFocusEntityIsMoving, true))
	{
		EventManager::fireEvent(EventManager::getInstance(), kEventScreenFocused);
		NM_ASSERT(!isDeleted(EventManager::getInstance()), "PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached: deleted entity manager during kEventScreenFocused");

		return true;
	}

	return false;
}

void PlatformerCameraMovementManager::setPositionFlag(Vector3DFlag positionFlag)
{
	this->positionFlag = positionFlag;
}

Vector3DFlag PlatformerCameraMovementManager::getPositionFlag()
{
	return this->positionFlag;
}

void PlatformerCameraMovementManager::enable()
{
	this->focusFunction = this->previousFocusFunction;
	this->previousFocusFunction = this->focusFunction;
}

void PlatformerCameraMovementManager::disable()
{
	if(&PlatformerCameraMovementManager::dontFocus != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &PlatformerCameraMovementManager::dontFocus;
}

void PlatformerCameraMovementManager::enableFocusEasing()
{
	this->focusFunction = &PlatformerCameraMovementManager::doFocus;
	this->previousFocusFunction = this->focusFunction;
}

void PlatformerCameraMovementManager::disableFocusEasing()
{
	this->focusFunction = &PlatformerCameraMovementManager::doFocusWithNoEasing;
	this->previousFocusFunction = this->focusFunction;
}

void PlatformerCameraMovementManager::alertWhenTargetFocused()
{
	if(&PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &PlatformerCameraMovementManager::doFocusAndAlertWhenTargetReached;
}

void PlatformerCameraMovementManager::dontAlertWhenTargetFocused()
{
	this->focusFunction = this->previousFocusFunction;
}

void PlatformerCameraMovementManager::lockMovement(uint8 axisToLockUp, bool locked)
{
	if(!isDeleted(this->cameraTrigger))
	{
		PlatformerCameraTriggerEntity::lockMovement(this->cameraTrigger, axisToLockUp, locked);
	}
}

void PlatformerCameraMovementManager::configure(Entity focusEntity, uint32 focusEntityLayer, uint32 cameraTriggerLayer, PixelSize boundingBoxSize, Vector3D boundingBoxDisplacement, Vector3D screenDisplacement)
{
	this->platformerCameraTriggerEntityShapesSpec[0] = (ShapeSpec)
	{
		// shape
		__TYPE(InverseBox),

		// size (x, y, z)
		boundingBoxSize,

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{0, 0, 0},

		/// if true this shape checks for collisions against other shapes
		true,

		/// layers in which I live
		cameraTriggerLayer,

		/// layers to ignore when checking for collisions
		~(focusEntityLayer),
	};

	this->platformerCameraTriggerEntityShapesSpec[1] = (ShapeSpec) {NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone};

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
			
		// collision shapes
		(ShapeSpec*)this->platformerCameraTriggerEntityShapesSpec,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		!isDeleted(focusEntity) ? Entity::getInGameType(focusEntity) : kTypeNone,

		// physical specification
		(PhysicalSpecification*)NULL,
	};

	if(!isDeleted(focusEntity))
	{
		// Configure the camera
		Camera::setFocusGameEntity(Camera::getInstance(), focusEntity);
		Camera::setFocusEntityPositionDisplacement(Camera::getInstance(), screenDisplacement);

		// Configure the camera trigger
		this->cameraTrigger = Entity::addChildEntity(focusEntity, (EntitySpec*)&this->platformerCameraTriggerEntitySpec, 0, NULL, &boundingBoxDisplacement, NULL);

		// make sure that focusing gets completed immediately
		PlatformerCameraMovementManager::enable(this);
	}
}
