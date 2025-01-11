/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PLATFORMER_CAMERA_TRIGGER_ACTOR_H_
#define PLATFORMER_CAMERA_TRIGGER_ACTOR_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Actor.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// A PlatformerCameraTriggerActor Spec
/// @memberof PlatformerCameraTriggerActor
typedef struct PlatformerCameraTriggerActorSpec
{
	Actor actorSpec;
};

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class PlatformerCameraTriggerActor
///
/// Inherits from Actor
///
/// Actor that detectst when the camera's focus actor collides with it.
class PlatformerCameraTriggerActor : Actor
{
	/// @protectedsection

	/// Flag to override the position in the flagged axis after transformation
	Vector3DFlag overridePositionFlag;

	/// @publicsection

	/// @param cameraActorSpec: Specification that determines how to configure the actor
	/// @param internalId: ID to keep track internally of the new instance
	/// @param name: Name to assign to the new instance
	void constructor(const PlatformerCameraTriggerActorSpec* cameraActorSpec, int16 internalId, const char* const name);

	/// Process a newly detected collision by one of the component colliders.
	/// @param collisionInformation: Information struct about the collision to resolve 
	/// @return True if the collider must keep track of the collision to detect if it persists and when it ends; false otherwise
	override bool collisionStarts(const CollisionInformation* collisionInformation);

	/// Make the animated actor ready to start operating once it has been completely intialized.
	/// @param recursive: If true, the ready call is propagated to its children, grand children, etc.
	override void ready(bool recursive);

	/// Compute the actor's global transformation.
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
	/// @param axisToLockUp: Axis to lock the actor's position
	/// @param locked: If true, the actor's position is locked on the provided axis
	void lockMovement(uint8 axisToLockUp, bool locked);
}

#endif
