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
#include <DirectDraw.h>
#include <VUEngine.h>
#include <Container.h>
#include <Entity.h>
#include <VIPManager.h>
#include <Camera.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' STATIC METHODS
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
	uint32 currentDrawingFrameBufferSet, GameObject gameObject __attribute__ ((unused))
)
{
	uint16 x = 0, y = 0;
	uint32 previousSourcePointerValueLeft = 0;
	uint32 previousSourcePointerValueRight = 0;

	// runtime working variables
	static int32 waveLutIndex = 0;

	// look up table of bitshifts performed on rows
	// values must be multiples of 2
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

	// write to framebuffers for both screens
	// loop columns
	for(x = 0; x < 384; x++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		uint32* columnSourcePointerLeft = (uint32*) (currentDrawingFrameBufferSet) + (x << 4);
		uint32* columnSourcePointerRight = (uint32*) (currentDrawingFrameBufferSet | 0x00010000) + (x << 4);

		// the shifted out pixels on top should be black
		previousSourcePointerValueLeft = 0;
		previousSourcePointerValueRight = 0;

		// increase look up table index, wrap around if necessary
		waveLutIndex += (waveLutIndex < 127) ? 1 : -127;

		// we can skip further processing for the current column if no shifting would be done on it
		if(waveLut[waveLutIndex] == 0)
		{
			continue;
		}

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
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

	// move the wave one pixel in the next frame
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
	// pointer to currently manipulated 32 bits of framebuffer
	uint32* sourcePointer = columnSourcePointer + y;

	// save current pointer value to temp var and shift highest x bits of it, according to lut,
	// to the lowest bits, since we want to insert these
	uint32 sourcePointerCurrentValue = *sourcePointer;
	uint32 previousSourcePointerLeftValueTemp = sourcePointerCurrentValue >> (32 - shift);

	// manipulate current 32 bits in frame buffer
	*sourcePointer =
		// shift bits according to wave lut
		// it's two bits per pixel, so 2 bits shifted left = 1 pixel shifted down on screen
		(sourcePointerCurrentValue << shift)

		// since the above shifting creates black pixels, we need to carry over these pixels
		// from the previous loop
		| previousSourcePointerValue;

	// we need the current source pointer value from _before_ we modified it, therefore we save it
	// it to a temp variable while modifying
	return previousSourcePointerLeftValueTemp;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
