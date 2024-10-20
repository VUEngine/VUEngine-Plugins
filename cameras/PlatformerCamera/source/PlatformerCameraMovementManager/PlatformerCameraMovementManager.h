/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PLATFORMER_CAMERA_MOVEMENT_MANAGER_H_
#define PLATFORMER_CAMERA_MOVEMENT_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <CameraMovementManager.h>
#include <Telegram.h>
#include <Entity.h>
#include <Camera.h>
#include <PlatformerCameraTriggerEntity.h>


//---------------------------------------------------------------------------------------------------------
//												ENUMS
//---------------------------------------------------------------------------------------------------------

enum PlatformerCameraMovementManagerEvents
{
	kEventScreenFocused = kEventEngineLast + 1
};


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define SCREEN_EASING_X_DISPLACEMENT				200
#define SCREEN_POSITIVE_EASING_Y_DISPLACEMENT		250
#define SCREEN_NEGATIVE_EASING_Y_DISPLACEMENT		250
//#define SCREEN_EASING_Y_DISPLACEMENT				(3 << __FRAME_CYCLE)
#define SCREEN_HORIZONTAL_DISPLACEMENT 				30
#define SCREEN_VERTICAL_DISPLACEMENT 				(__SCREEN_HEIGHT / 2) + 30
#define SCREEN_WIDTH_REDUCTION						64
#define SCREEN_HEIGHT_REDUCTION						32


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

singleton class PlatformerCameraMovementManager : CameraMovementManager
{
	Camera camera;
	/* update axis flag */
	Vector3DFlag positionFlag;
	/* pointer to function that implements the required focusing */
	Vector3D (*focusFunction)(void*, Camera, bool, uint32);
	Vector3D (*previousFocusFunction)(void*, Camera, bool, uint32);
	PlatformerCameraTriggerEntitySpec platformerCameraTriggerEntitySpec;
	Vector3D boundingBoxDisplacement;
	ColliderSpec platformerCameraTriggerEntityCollidersSpec[2];
	Entity cameraTrigger;

	// declare a PlatformerCameraMovementManager
	static PlatformerCameraMovementManager getInstance();
	void setPositionFlag(Vector3DFlag positionFlag);
	Vector3DFlag getPositionFlag();
	void enable();
	void disable();
	void enableFocusEasing();
	void disableFocusEasing();
	void alertWhenTargetFocused();
	void dontAlertWhenTargetFocused();
	void lockMovement(uint8 axisToLockUp, bool locked);
	void configure(Entity focusEntity, uint32 focusEntityLayer, uint32 cameraTriggerLayer, PixelSize boundingBoxSize, Vector3D boundingBoxDisplacement, Vector3D screenDisplacement);
	override Vector3D focus(Camera camera);
}


#endif
