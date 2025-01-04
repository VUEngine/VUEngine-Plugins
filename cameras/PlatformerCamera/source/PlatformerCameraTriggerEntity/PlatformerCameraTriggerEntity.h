/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PLATFORMER_CAMERA_TRIGGER_ENTITY_H_
#define PLATFORMER_CAMERA_TRIGGER_ENTITY_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Entity.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// A PlatformerCameraTriggerEntity Spec
/// @memberof PlatformerCameraTriggerEntity
typedef struct PlatformerCameraTriggerEntitySpec
{
	Entity entitySpec;
};

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

///
/// Class PlatformerCameraTriggerEntity
///
/// Inherits from Entity
///
/// Entity that detectst when the camera's focus entity collides with it.
class PlatformerCameraTriggerEntity : Entity
{
	/// @protectedsection

	/// Flag to override the position in the flagged axis after transformation
	Vector3DFlag overridePositionFlag;

	/// @publicsection

	/// @param cameraEntitySpec: Specification that determines how to configure the actor
	/// @param internalId: ID to keep track internally of the new instance
	/// @param name: Name to assign to the new instance
	void constructor(PlatformerCameraTriggerEntitySpec* cameraEntitySpec, int16 internalId, const char* const name);

	/// Process a newly detected collision by one of the component colliders.
	/// @param collisionInformation: Information struct about the collision to resolve 
	/// @return True if the collider must keep track of the collision to detect if it persists and when it ends; false otherwise
	override bool collisionStarts(const CollisionInformation* collisionInformation);

	/// Make the animated entity ready to start operating once it has been completely intialized.
	/// @param recursive: If true, the ready call is propagated to its children, grand children, etc.
	override void ready(bool recursive);

	/// Compute the entity's global transformation.
	/// @param environmentTransform: Reference environment for the local transformation
	/// @param invalidateTransformationFlag: Flag that determines which transfomation's components 
	/// must be recomputed
	override void transform(const Transformation* environmentTransform, uint8 invalidateTransformationFlag);

	/// Update this instance's logic.
	override void update();

	/// Prepare to resume this instance's logic.
	override void resume();

	/// Set the flag to override the position in the flagged axis after transformation.
	/// @param overridePositionFlag: Flag to override the position in the flagged axis after transformation
	void setOverridePositionFlag(Vector3DFlag overridePositionFlag);
	
	/// Retrieve the flag to override the position in the flagged axis after transformation.
	/// Flag to override the position in the flagged axis after transformation
	Vector3DFlag getOverridePositionFlag();

	/// Lock the movement on the provided axis.
	/// @param axisToLockUp: Axis to lock the entity's position
	/// @param locked: If true, the entity's position is locked on the provided axis
	void lockMovement(uint8 axisToLockUp, bool locked);
}

#endif
