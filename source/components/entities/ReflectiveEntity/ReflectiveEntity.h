/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef __VUENGINE_COMPONENT_REFLECTIVE_ENTITY
#ifndef REFLECTIVE_ENTITY_H_
#define REFLECTIVE_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define POINTER_TYPE			u32 // sizeof(u32) + (sizeof(u32) / sizeof(POINTER_TYPE) / 2)
#define Y_SHIFT					4 // sizeof(POINTER_TYPE) << 2
#define Y_STEP_SIZE				16
#define Y_STEP_SIZE_2_EXP		4 // sizeof(POINTER_TYPE) << 3
#define BITS_PER_STEP 			32


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/**
 * Definition of a ReflectiveEntity
 *
 * @memberof 	ReflectiveEntity
 */
typedef struct ReflectiveEntityDefinition
{
	// entity definition
	EntityDefinition entityDefinition;

	// the starting point from where start to reflect data
	// relative to my position
	Point sourceDisplacement;

	// the starting point from where start to draw data
	// relative to my position
	Point outputDisplacement;

	// width of the reflection
	u16 width;

	// height of the reflection
	u16 height;

	// mask to apply to the whole reflection
	u32 overallMask;

	// mask to apply to the mirrored image
	u32 reflectionMask;

	// mask to apply to the image behind the reflection
	u32 backgroundMask;

	// transparent
	bool transparent;

	// reflect parallax info
	bool reflectParallax;

	// axis for image reversing
	u8 axisForReversing;

	// pointer to table of vertical displacements
	// if no displacement, leave as NULL
	const u8* waveLut;

	// number of wave lut entries
	u16 numberOfWaveLutEntries;

	// fix10_6 throttle for the waving
	fix10_6 waveLutThrottleFactor;

	// parallax displacement applied to the reflection
	s16 parallaxDisplacement;

	// flatten top?
	bool flattenTop;

	// flatten bottom?
	bool flattenBottom;

	// top border mask
	u32 topBorder;

	// bottom border mask
	u32 bottomBorder;

	// left border mask
	u32 leftBorder;

	// right border mask
	u32 rightBorder;

} ReflectiveEntityDefinition;

/**
 * A ReflectiveEntityDefinition that is stored in ROM
 *
 * @memberof	ReflectiveEntity
 */
typedef const ReflectiveEntityDefinition ReflectiveEntityROMDef;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// An Entity that can mirror other parts of the virtual screen
class ReflectiveEntity : Entity
{
	fix10_6 waveLutIndex;
	fix10_6 waveLutIndexIncrement;
	Point position2D;
	Point nextFramePosition2D;

	void constructor(ReflectiveEntityDefinition* mirrorDefinition, s16 id, s16 internalId, const char* const name);
	virtual void applyReflection(u32 currentDrawingFrameBufferSet);
	void drawReflection(u32 currentDrawingFrameBufferSet, s16 xSourceStart, s16 ySourceStart, s16 xOutputStart, s16 yOutputStart, s16 width, s16 height, u32 overallMask, u32 reflectionMask, u32 backgroundMask, u16 axisForReversing, bool transparent, bool reflectParallax, s16 parallaxDisplacement, const u8 waveLut[], int numberOfWaveLutEntries, fix10_6 waveLutThrottleFactor, bool flattenTop, bool flattenBottom, u32 topBorderMask, u32 bottomBorderMask, u32 leftBorderMask, u32 rightBorderMask);
	override void ready(bool recursive);
	override void resume();
	static void shiftPixels(int pixelShift, POINTER_TYPE* sourceValue, u32 nextSourceValue, POINTER_TYPE* remainderValue, u32 overallMask, u32 reflectionMask);
	override void suspend();
	override void synchronizeGraphics();
}


#endif
#endif
