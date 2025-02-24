/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PLATFORMER_CAMERA_MOVEMENT_MANAGER_H_
#define PLATFORMER_CAMERA_MOVEMENT_MANAGER_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <CameraMovementManager.h>
#include <Telegram.h>
#include <Actor.h>
#include <Camera.h>
#include <PlatformerCameraTriggerActor.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// FORWARD DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

class Camera;
class Actor;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' MACROS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#define SCREEN_EASING_X_DISPLACEMENT				200
#define SCREEN_POSITIVE_EASING_Y_DISPLACEMENT		250
#define SCREEN_NEGATIVE_EASING_Y_DISPLACEMENT		250
#define SCREEN_HORIZONTAL_DISPLACEMENT 				30
#define SCREEN_VERTICAL_DISPLACEMENT 				(__SCREEN_HEIGHT / 2) + 30
#define SCREEN_WIDTH_REDUCTION						64
#define SCREEN_HEIGHT_REDUCTION						32

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

enum PlatformerCameraMovementManagerEvents
{
	kEventPlatformerCameraScreenFocused = kEventPluginsFirst + 1
};

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class PlatformerCameraMovementManager
///
/// Inherits from CameraMovementManager
///
/// Implements a camera manager for platformer games.
singleton class PlatformerCameraMovementManager : CameraMovementManager
{
	/// Cache the camera instance's reference
	Camera camera;

	/// Flag to signal the axis to update
	Vector3DFlag positionFlag;

	/// Pointer to function that implements the required focusing
	Vector3D (*focusFunction)(void*, Camera, bool, uint32);

	/// Pointer to the previous function that implements the required focusing
	Vector3D (*previousFocusFunction)(void*, Camera, bool, uint32);

	/// Actor spec used to configure the camera's trigger actor
	PlatformerCameraTriggerActorSpec platformerCameraTriggerActorSpec;

	/// Displacement to add to the bounding box
	Vector3D boundingBoxDisplacement;

	/// Array of colliders for the camera's trigger actor
	ColliderSpec platformerCameraTriggerActorCollidersSpec[2];

	/// Actor that triggers the camera's focusing when colliding with the focus actor
	Actor cameraTrigger;

	/// @publicsection

	/// Focus the camera on the focus actor if any.
	/// @param camera: Camera to focus
	override Vector3D focus(Camera camera);

	/// Enable the focusing of the camera.
	void enable();

	/// Disable the focusing of the camera.
	void disable();

	/// Enable the easing of the focusing.
	void enableFocusEasing();

	/// Disable the easing of the focusing.
	void disableFocusEasing();

	/// Alert when the camera is fully focused on the target actor.
	void alertWhenTargetFocused();

	/// Don't when the camera is fully focused on the target actor.
	void dontAlertWhenTargetFocused();

	/// Set the flags that enable the update of the camera's position.
	/// @param positionFlag: Flag to signal the axis to update
	void setPositionFlag(Vector3DFlag positionFlag);

	/// Retrieve the flags that enable the update of the camera's position.
	/// @return Flag that signals the axis to update
	Vector3DFlag getPositionFlag();

	/// Lock the camera's focusing on the provided axis.
	/// @param axisToLockUp: Axis to lock the camera's focusing
	/// @param locked: If true, the camera's focusing is locked on the provided axis
	void lockMovement(uint8 axisToLockUp, bool locked);

	/// Configure the camera manager.
	/// @param focusActor: Actor on which focus the camera
	/// @param focusActorLayer: Layer in which live the focus actor's colliders
	/// @param cameraTriggerLayer: Layer in which live the camera trgger actor's colliders
	/// @param boundingBoxSize: Bounding box inside of which the fouse actor can move without
	/// triggering the focusing of the camera
	/// @param boundingBoxDisplacement: Displacement to add to the bounding box
	/// @param screenDisplacement: Displacement to add to the camera when focusing
	void configure(Actor focusActor, uint32 focusActorLayer, uint32 cameraTriggerLayer, PixelSize boundingBoxSize, Vector3D boundingBoxDisplacement, Vector3D screenDisplacement);
}

#endif
