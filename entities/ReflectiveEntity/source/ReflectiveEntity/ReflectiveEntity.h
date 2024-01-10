/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef REFLECTIVE_ENTITY_H_
#define REFLECTIVE_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#ifndef REFLECTIVE_ENTITY_POINTER_TYPE
#define REFLECTIVE_ENTITY_POINTER_TYPE			uint32 // sizeof(uint32) + (sizeof(uint32) / sizeof(REFLECTIVE_ENTITY_POINTER_TYPE) / 2)
#endif

#ifndef REFLECTIVE_ENTITY_Y_SHIFT
#define REFLECTIVE_ENTITY_Y_SHIFT				4 // sizeof(REFLECTIVE_ENTITY_POINTER_TYPE) << 2
#endif

#ifndef REFLECTIVE_ENTITY_Y_STEP_SIZE
#define REFLECTIVE_ENTITY_Y_STEP_SIZE			16
#endif

#ifndef REFLECTIVE_ENTITY_Y_STEP_SIZE_2_EXP
#define REFLECTIVE_ENTITY_Y_STEP_SIZE_2_EXP		4 // sizeof(REFLECTIVE_ENTITY_POINTER_TYPE) << 3
#endif

#ifndef REFLECTIVE_ENTITY_BITS_PER_STEP
#define REFLECTIVE_ENTITY_BITS_PER_STEP 		32
#endif


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/**
 * Spec of a ReflectiveEntity
 *
 * @memberof 	ReflectiveEntity
 */
typedef struct ReflectiveEntitySpec
{
	/// entity spec
	EntitySpec entitySpec;

	/// the starting point from where start to reflect data
	/// relative to my position
	Point sourceDisplacement;

	/// the starting point from where start to draw data
	/// relative to my position
	Point outputDisplacement;

	/// width of the reflection
	uint16 width;

	/// height of the reflection
	uint16 height;

	/// mask to apply to the mirrored image
	uint32 reflectionMask;

	/// transparent
	bool transparent;

	/// reflect parallax info
	bool reflectParallax;

	/// axis for image reversing
	uint8 axisForReversing;

	/// pointer to table of vertical displacements
	/// if no displacement, leave as NULL
	const uint8* waveLut;

	/// number of wave lut entries
	uint16 numberOfWaveLutEntries;

	/// fixed_t throttle for the waving
	fixed_t waveLutThrottleFactor;

	/// parallax displacement applied to the reflection
	int16 parallaxDisplacement;

	/// flatten top?
	bool flattenTop;

	/// flatten bottom?
	bool flattenBottom;

	/// top border mask
	uint32 topBorder;

	/// bottom border mask
	uint32 bottomBorder;

	/// left border mask
	uint32 leftBorder;

	/// right border mask
	uint32 rightBorder;

	/// Noise passes: higher values means less noise
	int16 noisePasses;

} ReflectiveEntitySpec;

/**
 * A ReflectiveEntitySpec that is stored in ROM
 *
 * @memberof 	ReflectiveEntity
 */
typedef const ReflectiveEntitySpec ReflectiveEntityROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/**
 * An Entity that can mirror other parts of the screen.
 *
 * @ingroup vuengine-plugins-entities
 */
class ReflectiveEntity : Entity
{
	//
	fixed_t waveLutIndex;
	//
	fixed_t waveLutIndexIncrement;
	//
	Point position2D;
	//
	Point nextFramePosition2D;


	/// @publicsection

	/**
	 * Class constructor
	 *
	 * @param reflectiveEntitySpec
	 * @param id
	 * @param internalId
	 * @param name
	 */
	void constructor(ReflectiveEntitySpec* mirrorSpec, int16 internalId, const char* const name);

	/**
	 * Reflection algorithm that is called by the postprocessing effect
	 *
	 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
	 */
	virtual void applyReflection(uint32 currentDrawingFrameBufferSet);

	/**
	 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
     * @param xSourceStart
     * @param ySourceStart
     * @param xOutputStart
     * @param yOutputStart
     * @param width
     * @param height
     * @param reflectionMask
     * @param axisForReversing
     * @param transparent
     * @param reflectParallax
     * @param parallaxDisplacement
     * @param waveLut
     * @param numberOfWaveLutEntries
     * @param waveLutThrottleFactor
     * @param flattenTop
     * @param flattenBottom
     * @param topBorderMask
     * @param bottomBorderMask
     * @param leftBorderMask
     * @param rightBorderMask
     * @param noisePasses
     */
	virtual void drawReflection(uint32 currentDrawingFrameBufferSet, int16 xSourceStart, int16 ySourceStart, int16 xOutputStart, int16 yOutputStart, int16 width, int16 height, uint32 reflectionMask, uint16 axisForReversing, bool transparent, bool reflectParallax, int16 parallaxDisplacement, const uint8 waveLut[], int32 numberOfWaveLutEntries, fixed_t waveLutThrottleFactor, bool flattenTop, bool flattenBottom, uint32 topBorderMask, uint32 bottomBorderMask, uint32 leftBorderMask, uint32 rightBorderMask, int16 noisePasses);

	/**
	 * Entity is ready
	 *
	 * @param recursive
	 */
	override void ready(bool recursive);

	/**
	 * Resume after pause
	 */
	override void resume();

	/**
	 * @param pixelShift
     * @param sourceValue
     * @param nextSourceValue
     * @param remainderValue
     * @param overallMask
     * @param reflectionMask
     */
	static void shiftPixels(int32 pixelShift, REFLECTIVE_ENTITY_POINTER_TYPE* sourceValue, uint32 nextSourceValue, REFLECTIVE_ENTITY_POINTER_TYPE* remainderValue, uint32 reflectionMask, uint32 noise);

	/**
	 * Suspend for pause
	 */
	override void suspend();

	/// @privatesection

	/**
	 * @fn ReflectiveEntity::destructor
	 * Class destructor
	 */

	/**
	 * @fn ReflectiveEntity::reflect
	 * Postprocessing effect that does the actual reflection
	 *
	 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
	 * @param spatialObject					Spatial object relative to which the effect is positioned
	 */
}


#endif
