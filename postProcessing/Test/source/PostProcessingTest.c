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

#include "PostProcessingTest.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/*
 * Increases the palette index within a rectangular area around the entity, effectively
 * "lightening" it up. This effect reads and write only a small portion of the screen and is therefore
 * semi-feasible on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
static void PostProcessingTest::lighting(uint32 currentDrawingFrameBufferSet, Entity entity)
{
	// The currentDrawingFrameBufferSet dictates which frame buffer set (remember that there are 4 frame
	// Buffers, 2 per eye) has been written by the VPU and you can work on.

	if(isDeleted(entity))
	{
		return;
	}

	PixelVector screenPixelPosition = 
		PixelVector::projectVector3D(Vector3D::getRelativeToCamera(*Entity::getPosition(entity)), 0);

	// The pixel in screen coordinates (x: 0 - 383, y: 0 - 223)
	int32 x = 0;
	int32 y = 0;

	// These will be used to dictate the size of the screen portion to be affected
	int32 xCounter = 0;
	int32 yCounter = 0;

/*
	// This is just a test, so that's why these are static
	static bool vibrate = false;
	static int32 wait = 0;
*/

	// Write to framebuffers for both screens
	uint32 buffer = 0;
	for(; buffer < 2; buffer++)
	{
		for(xCounter = 64, x = screenPixelPosition.x - (xCounter >> 1); xCounter--; x++)
		{
			for(yCounter = 64, y = screenPixelPosition.y - (yCounter >> 1); yCounter >= 0; yCounter -= 4, y += 4)
			{
				BYTE* sourcePointer = (BYTE*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0));
				sourcePointer += ((x << 6) + (y >> 2));

/*
				// Negative
				*sourcePointer = ~*sourcePointer;
*/

/*
				// Noise
				if(vibrate)
				{
					if(xCounter & 1)
					{
						// Shift down one pixel
						*sourcePointer = (*sourcePointer & 0x03) | (*sourcePointer << 2);
					}
					else
					{
						// Shift up one pixel
						*sourcePointer = (*sourcePointer & 0xC0) | (*sourcePointer >> 2);
					}
				}
*/

				// Add 1 to each pixel's color to "light it up"
				*sourcePointer |= 0x55;
			}
		}
	}

/*
	// This just creates a simple delay to not shift the pixels on each cycle
	if(--wait < 0)
	{
		wait = 4;
		vibrate = !vibrate;
	}
*/
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static void PostProcessingTest::dummy
(
	uint32 currentDrawingFrameBufferSet, Entity entity __attribute__ ((unused))
)
{
	uint16 x = 0, y = 0;
	uint32 previousSourcePointerValueLeft = 0;
	uint32 previousSourcePointerValueRight = 0;

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

		// Loop current column in steps of 16 pixels (32 bits)
		// Ignore the bottom 16 pixels of the screen (gui)
		for(y = 0; y < 13; y++)
		{
			previousSourcePointerValueLeft = 
				PostProcessingTest::writeToFrameBuffer(y, 1, columnSourcePointerLeft, previousSourcePointerValueLeft);
			previousSourcePointerValueRight = 
				PostProcessingTest::writeToFrameBuffer(y, 1, columnSourcePointerRight, previousSourcePointerValueRight);
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
static uint32 PostProcessingTest::writeToFrameBuffer
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
