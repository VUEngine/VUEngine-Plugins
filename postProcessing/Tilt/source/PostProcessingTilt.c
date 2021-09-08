/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <PostProcessingTilt.h>
#include <Optics.h>
#include <Utilities.h>
#include <DirectDraw.h>
#include <Game.h>
#include <Container.h>
#include <Entity.h>
#include <VIPManager.h>
#include <Camera.h>


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

/**
 * "Tilts" the game image by a few percent by gradually shifting columns. This effect reads and write
 * almost the whole screen and is therefore not feasible on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
static void PostProcessingTilt::tiltScreen(uint32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	uint8 buffer = 0, currentShift = 0;
	uint16 x = 0, y = 0;
	uint32 previousSourcePointerValue = 0;

	// write to framebuffers for both screens
	for(; buffer < 2; buffer++)
	{
		// loop columns that shall be shifted
		for(x = 0; x < 360; x++)
		{
			// get pointer to currently manipulated 32 bits of framebuffer
			uint32* columnSourcePointer = (uint32*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0)) + (x << 4);

			// the shifted out pixels on top should be black
			previousSourcePointerValue = 0;

			// get shift for current column
			currentShift = 30 - ((x / 24) << 1);

			// loop current column in steps of 16 pixels (32 bits)
			// ignore the bottom 16 pixels of the screen (gui)
			for(y = 0; y < 13; y++)
			{
				previousSourcePointerValue = PostProcessingTilt::writeToFrameBuffer(y, currentShift, columnSourcePointer, previousSourcePointerValue);
			}
		}
	}
}

/**
 * Helper function to write a 32 bit value to the framebuffer
 * (16 pixels)
 *
 * @param y								Y coordinate (true y value = y * 16)
 * @param shift							Number of bits to shift the pixels by
 * @param columnSourcePointer			Framebuffer address of the current column (x value)
 * @param previousSourcePointerValue	Value from the loop's previous cycle (effectively where y - 1)
 */
static uint32 PostProcessingTilt::writeToFrameBuffer(uint16 y, uint16 shift, uint32* columnSourcePointer, uint32 previousSourcePointerValue)
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
