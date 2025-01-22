/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Camera.h>
#include <Optics.h>
#include <Utilities.h>
#include <VIPManager.h>
#include <VUEngine.h>

#include "PostProcessingTilt.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/*
 * "Tilts" the game image by a few percent by gradually shifting columns. This effect reads and write
 * almost the whole screen and is therefore not feasible on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
static void PostProcessingTilt::tiltScreen
(
	uint32 currentDrawingFrameBufferSet, Entity entity __attribute__ ((unused))
)
{
	uint8 buffer = 0, currentShift = 0;
	uint16 x = 0, y = 0;
	uint32 previousSourcePointerValue = 0;

	// Write to framebuffers for both screens
	for(; buffer < 2; buffer++)
	{
		// Loop columns that shall be shifted
		for(x = 0; x < 360; x++)
		{
			// Get pointer to currently manipulated 32 bits of framebuffer
			uint32* columnSourcePointer = (uint32*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0)) + (x << 4);

			// The shifted out pixels on top should be black
			previousSourcePointerValue = 0;

			// Get shift for current column
			currentShift = 30 - ((x / 24) << 1);

			// Loop current column in steps of 16 pixels (32 bits)
			// Ignore the bottom 16 pixels of the screen (gui)
			for
			(
				y = ((__PLUGIN_TILT_STARTING_ROW * 2) / 8) / sizeof(uint32); 
				y < ((__PLUGIN_TILT_ENDING_ROW * 2) / 8) / sizeof(uint32); 
				y++
			)
			{
				previousSourcePointerValue = 
					PostProcessingTilt::writeToFrameBuffer(y, currentShift, columnSourcePointer, previousSourcePointerValue);
			}
		}
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/*
 * Helper function to write a 32 bit value to the framebuffer
 * (16 pixels)
 *
 * @param y								Y coordinate (true y value = y * 16)
 * @param shift							Number of bits to shift the pixels by
 * @param columnSourcePointer			Framebuffer address of the current column (x value)
 * @param previousSourcePointerValue	Value from the loop's previous cycle (effectively where y - 1)
 */
static uint32 PostProcessingTilt::writeToFrameBuffer
(
	uint16 y, uint16 shift, uint32* columnSourcePointer, uint32 previousSourcePointerValue
)
{
	// Pointer to currently manipulated 32 bits of framebuffer
	uint32* sourcePointer = columnSourcePointer + y;

	// Save current pointer value to temp var and shift highest x bits of it, according to lut,
	// To the lowest bits, since we want to insert these
	uint32 sourcePointerCurrentValue = *sourcePointer;
	uint32 previousSourcePointerLeftValueTemp = sourcePointerCurrentValue >> (32 - shift);

	// Manipulate current 32 bits in frame buffer
	*sourcePointer =
		// Shift bits according to wave lut
		// It's two bits per pixel, so 2 bits shifted left = 1 pixel shifted down on screen
		(sourcePointerCurrentValue << shift)

		// Since the above shifting creates black pixels, we need to carry over these pixels
		// From the previous loop
		| previousSourcePointerValue;

	// We need the current source pointer value from _before_ we modified it, therefore we save it
	// It to a temp variable while modifying
	return previousSourcePointerLeftValueTemp;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
