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
	NormalizedDirection normalizedDirection;
	Vector3D previousGlobalPosition;


	void constructor(PlatformerCameraTriggerEntitySpec* cameraEntitySpec, int16 internalId, const char* const name);
	void setOverridePositionFlag(Vector3DFlag overridePositionFlag);
	Vector3DFlag getOverridePositionFlag();
	void lockMovement(uint8 axisToLockUp, bool locked);
	override void ready(bool recursive);
	override void transform(const Transformation* environmentTransform, uint8 invalidateTransformationFlag);
	override void update();
	override void resume();
	override bool enterCollision(const CollisionInformation* collisionInformation);
}


#endif
