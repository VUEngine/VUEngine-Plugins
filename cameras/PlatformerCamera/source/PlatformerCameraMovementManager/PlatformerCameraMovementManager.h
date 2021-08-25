/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
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
	bool (*focusFunction)(void*, u32, u32);
	bool (*previousFocusFunction)(void*, u32, u32);
	PlatformerCameraTriggerEntitySpec platformerCameraTriggerEntitySpec;
	Vector3D boundingBoxDisplacement;
	ShapeSpec platformerCameraTriggerEntityShapesSpec[2];
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
	void lockMovement(u8 axisToLockUp, bool locked);
	void configure(Entity focusEntity, u32 focusEntityLayer, u32 cameraTriggerLayer, PixelSize boundingBoxSize, Vector3D boundingBoxDisplacement, Vector3D screenDisplacement);
	override void focus(u32 checkIfFocusEntityIsMoving);
}


#endif
