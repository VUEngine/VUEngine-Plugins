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

#include <PostProcessingWobble.h>
#include <Optics.h>
#include <Utilities.h>
#include <FrameBufferManager.h>
#include <VUEngine.h>
#include <Container.h>
#include <Actor.h>
#include <VIPManager.h>
#include <Camera.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/*
 * Applies a full screen wobble distortion that is reminiscent of water waves. This effect reads and write
 * almost the whole screen and is therefore not feasible on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
static void PostProcessingWobble::wobble
(
	uint32 currentDrawingFrameBufferSet, Entity entity __attribute__ ((unused))
)
{
	uint16 x = 0, y = 0;
	uint32 previousSourcePointerValueLeft = 0;
	uint32 previousSourcePointerValueRight = 0;

	// Runtime working variables
	static int32 waveLutIndex = 0;

	// Look up table of bitshifts performed on rows
	// Values must be multiples of 2
	const uint32 waveLut[128] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	// Write to framebuffers for both screens
	// Loop columns
	for(x = 0; x < 384; x++)
	{
		// Get pointer to currently manipulated 32 bits of framebuffer
		uint32* columnSourcePointerLeft = (uint32*) (currentDrawingFrameBufferSet) + (x << 4);
		uint32* columnSourcePointerRight = (uint32*) (currentDrawingFrameBufferSet | 0x00010000) + (x << 4);

		// The shifted out pixels on top should be black
		previousSourcePointerValueLeft = 0;
		previousSourcePointerValueRight = 0;

		// Increase look up table index, wrap around if necessary
		waveLutIndex += (waveLutIndex < 127) ? 1 : -127;

		// We can skip further processing for the current column if no shifting would be done on it
		if(waveLut[waveLutIndex] == 0)
		{
			continue;
		}

		// Loop current column in steps of 16 pixels (32 bits)
		// Ignore the bottom 16 pixels of the screen (gui)
		for(y = ((__PLUGIN_WOBBLE_STARTING_ROW * 2) / 8) / sizeof(uint32); y < ((__PLUGIN_WOBBLE_ENDING_ROW * 2) / 8) / sizeof(uint32); y++)
		{
			previousSourcePointerValueLeft = 
				PostProcessingWobble::writeToFrameBuffer
				(
					y, waveLut[waveLutIndex], columnSourcePointerLeft, previousSourcePointerValueLeft
				);
			
			previousSourcePointerValueRight = 
				PostProcessingWobble::writeToFrameBuffer
				(
					y, waveLut[waveLutIndex], columnSourcePointerRight, previousSourcePointerValueRight
				);
		}
	}

	// Move the wave one pixel in the next frame
	waveLutIndex++;
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
static uint32 PostProcessingWobble::writeToFrameBuffer
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
