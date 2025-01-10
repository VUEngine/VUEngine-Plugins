/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef REFLECTIVE_ACTOR_H_
#define REFLECTIVE_ACTOR_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Actor.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//												MACROS

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#ifndef REFLECTIVE_ACTOR_POINTER_TYPE
#define REFLECTIVE_ACTOR_POINTER_TYPE			uint32 // sizeof(uint32) + (sizeof(uint32) / sizeof(REFLECTIVE_ACTOR_POINTER_TYPE) / 2)
#endif

#ifndef REFLECTIVE_ACTOR_Y_SHIFT
#define REFLECTIVE_ACTOR_Y_SHIFT				4 // sizeof(REFLECTIVE_ACTOR_POINTER_TYPE) << 2
#endif

#ifndef REFLECTIVE_ACTOR_Y_STEP_SIZE
#define REFLECTIVE_ACTOR_Y_STEP_SIZE			16
#endif

#ifndef REFLECTIVE_ACTOR_Y_STEP_SIZE_2_EXP
#define REFLECTIVE_ACTOR_Y_STEP_SIZE_2_EXP		4 // sizeof(REFLECTIVE_ACTOR_POINTER_TYPE) << 3
#endif

#ifndef REFLECTIVE_ACTOR_BITS_PER_STEP
#define REFLECTIVE_ACTOR_BITS_PER_STEP 		32
#endif

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// A ReflectiveActor Spec
/// @memberof ReflectiveActor
typedef struct ReflectiveActorSpec
{
	ActorSpec actorSpec;

	/// Starting point from where start to reflect data
	/// relative to my position
	Point sourceDisplacement;

	/// Starting point from where start to draw data
	/// relative to my position
	Point outputDisplacement;

	/// Width of the reflection
	uint16 width;

	/// Weight of the reflection
	uint16 height;

	/// Mask to apply to the mirrored image
	uint32 reflectionMask;

	/// Transparency
	bool transparency;

	/// Reflect parallax info
	bool reflectParallax;

	/// Axis for image reversing
	uint8 axisForReversing;

	/// Pointer to table of vertical displacements
	/// if no displacement, leave as NULL
	const uint8* waveLut;

	/// Number of wave lut entries
	uint16 numberOfWaveLutEntries;

	/// Throttle for the waving
	fixed_t waveLutThrottleFactor;

	/// Parallax displacement applied to the reflection
	int16 parallaxDisplacement;

	/// Flatten top?
	bool flattenTop;

	/// Flatten bottom?
	bool flattenBottom;

	/// Top border mask
	uint32 topBorder;

	/// Bottom border mask
	uint32 bottomBorder;

	/// Left border mask
	uint32 leftBorder;

	/// Right border mask
	uint32 rightBorder;

	/// Noise passes: higher values means less noise
	int16 noisePasses;

} ReflectiveActorSpec;

/// A ReflectiveActor Spec that is stored in ROM
/// @memberof ReflectiveActor
typedef const ReflectiveActorSpec ReflectiveActorROMSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class Sprite
///
/// Inherits from Actor
///
/// Implements an actor that can mirror other parts of the screen.
class ReflectiveActor : Actor
{
	/// @protectedsection

	/// Index of the lookup table
	fixed_t waveLutIndex;

	/// Increment for the index of the lookup table
	fixed_t waveLutIndexIncrement;

	/// Position in screen space where to show the reflection
	Point position2D;

	/// @publicsection

	/// @param reflectiveActorSpec: Specification that determines how to configure the actor
	/// @param internalId: ID to keep track internally of the new instance
	/// @param name: Name to assign to the new instance
	void constructor(ReflectiveActorSpec* reflectiveActorSpec, int16 internalId, const char* const name);

	/// Make the actor ready to start operating once it has been completely intialized.
	/// @param recursive: If true, the ready call is propagated to its children, grand children, etc.
	override void ready(bool recursive);

	/// Prepare to suspend this instance's logic.
	override void suspend();

	/// Prepare to resume this instance's logic.
	override void resume();

	/// Reflection algorithm that is called by the postprocessing effect
	/// @param currentDrawingFrameBufferSet: The framebuffer set that's currently being accessed
	virtual void applyReflection(uint32 currentDrawingFrameBufferSet);
}

#endif
