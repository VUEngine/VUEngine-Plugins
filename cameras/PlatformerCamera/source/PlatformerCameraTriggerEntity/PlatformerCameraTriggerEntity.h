/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PLATFORMER_CAMERA_TRIGGER_ENTITY_H_
#define PLATFORMER_CAMERA_TRIGGER_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef EntitySpec PlatformerCameraTriggerEntitySpec;
typedef const PlatformerCameraTriggerEntitySpec PlatformerCameraTriggerEntityROMSpec;

class PlatformerCameraTriggerEntity : Entity
{
	/* update axis flag */
	Vector3DFlag overridePositionFlag;
	Direction direction;
	Vector3D previousGlobalPosition;

	void constructor(PlatformerCameraTriggerEntitySpec* cameraEntitySpec, s16 internalId, const char* const name);
	void setOverridePositionFlag(Vector3DFlag overridePositionFlag);
	Vector3DFlag getOverridePositionFlag();
	void lockMovement(u8 axisToLockUp, bool locked);
	override void ready(bool recursive);
	override void transform(const Transformation* environmentTransform, u8 invalidateTransformationFlag);
	override void update(u32 elapsedTime);
	override void resume();
	override bool enterCollision(const CollisionInformation* collisionInformation);
}


#endif
