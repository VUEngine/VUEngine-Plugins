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

#include <PostProcessingDwarfPlanet.h>


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

/**
 * "Bends down" the left and right edges of the screen to make the world look like a very small planet.
 * This effect reads and write a fourth of the screen and is therefore quite heavy on hardware,
 * reducing the frame rate by about 50%.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
static void PostProcessingDwarfPlanet::dwarfPlanet(uint32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	// look up table of bitshifts performed on rows
	const uint32 lut[96] =
	{
		2,
		4,
		6,	6,
		8,	8,
		10, 10, 10,
		12, 12, 12,
		14, 14, 14, 14,
		16, 16, 16, 16, 16,
		18, 18, 18, 18, 18, 18,
		20, 20, 20, 20, 20, 20, 20,
		22, 22, 22, 22, 22, 22, 22, 22,
		24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
		26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
		28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
		30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
	};

	int lutEntries = sizeof(lut) / sizeof(uint32);
	// runtime working variables

	int counter = lutEntries;

	// loop columns of left fourth of screen
	for(; --counter;)
	{
		int x1 = (lutEntries - counter);
		int x2 = __SCREEN_WIDTH - counter;

		// get pointer to currently manipulated 32 bits of framebuffer
		uint32* columnSourcePointerLeft1 = (uint32*) (currentDrawingFrameBufferSet) + (x1 << 4);
		uint32* columnSourcePointerRight1 = (uint32*) (currentDrawingFrameBufferSet | 0x00010000) + (x1 << 4);
		uint32* columnSourcePointerLeft2 = (uint32*) (currentDrawingFrameBufferSet) + (x2 << 4);
		uint32* columnSourcePointerRight2 = (uint32*) (currentDrawingFrameBufferSet | 0x00010000) + (x2 << 4);

		// the shifted out pixels on top should be black
		uint32 previousSourcePointerValueLeft1 = 0;
		uint32 previousSourcePointerValueRight1 = 0;
		uint32 previousSourcePointerValueLeft2 = 0;
		uint32 previousSourcePointerValueRight2 = 0;

		uint16 y = 0;

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
		for(y = 0; y < 13; y++)
		{
			previousSourcePointerValueLeft1 = PostProcessingDwarfPlanet::writeToFrameBuffer(y, 32 - lut[lutEntries - counter], columnSourcePointerLeft1, previousSourcePointerValueLeft1);
			previousSourcePointerValueRight1 = PostProcessingDwarfPlanet::writeToFrameBuffer(y, 32 - lut[lutEntries - counter], columnSourcePointerRight1, previousSourcePointerValueRight1);
			previousSourcePointerValueLeft2 = PostProcessingDwarfPlanet::writeToFrameBuffer(y, 32 - lut[counter], columnSourcePointerLeft2, previousSourcePointerValueLeft2);
			previousSourcePointerValueRight2 = PostProcessingDwarfPlanet::writeToFrameBuffer(y, 32 - lut[counter], columnSourcePointerRight2, previousSourcePointerValueRight2);
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
static uint32 PostProcessingDwarfPlanet::writeToFrameBuffer(uint16 y, uint16 shift, uint32* columnSourcePointer, uint32 previousSourcePointerValue)
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
