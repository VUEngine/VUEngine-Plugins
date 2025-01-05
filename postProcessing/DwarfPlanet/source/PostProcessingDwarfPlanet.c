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

#include "PostProcessingDwarfPlanet.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/*
 * "Bends down" the left and right edges of the screen to make the world look like a very small planet.
 * This effect reads and write a fourth of the screen and is therefore quite heavy on hardware,
 * reducing the frame rate by about 50%.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
static void PostProcessingDwarfPlanet::dwarfPlanet
(
	uint32 currentDrawingFrameBufferSet, Entity entity __attribute__ ((unused))
)
{
	// Look up table of bitshifts performed on rows
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

	int32 lutEntries = sizeof(lut) / sizeof(uint32);

	// Loop columns of outer fourths of affected area
	int32 counter = lutEntries;
	for(; --counter;)
	{
		int32 x1 = __PLUGIN_DWARF_PLANET_STARTING_COLUMN - 1 + lutEntries - counter;
		int32 x2 = __PLUGIN_DWARF_PLANET_ENDING_COLUMN - counter;

		// Get pointer to currently manipulated 32 bits of framebuffer
		uint32* columnSourcePointerLeft1 = (uint32*) (currentDrawingFrameBufferSet) + (x1 << 4);
		uint32* columnSourcePointerRight1 = (uint32*) (currentDrawingFrameBufferSet | 0x00010000) + (x1 << 4);
		uint32* columnSourcePointerLeft2 = (uint32*) (currentDrawingFrameBufferSet) + (x2 << 4);
		uint32* columnSourcePointerRight2 = (uint32*) (currentDrawingFrameBufferSet | 0x00010000) + (x2 << 4);

		// The shifted out pixels on top should be black
		uint32 previousSourcePointerValueLeft1 = 0;
		uint32 previousSourcePointerValueRight1 = 0;
		uint32 previousSourcePointerValueLeft2 = 0;
		uint32 previousSourcePointerValueRight2 = 0;

		// Loop current column in steps of 16 pixels (32 bits)
		for(uint16 y = (__PLUGIN_DWARF_PLANET_STARTING_ROW / 16); y < (__PLUGIN_DWARF_PLANET_ENDING_ROW / 16); y++)
		{
			previousSourcePointerValueLeft1 = 
				PostProcessingDwarfPlanet::writeToFrameBuffer
				(
					y, 32 -lut[lutEntries - counter], columnSourcePointerLeft1, previousSourcePointerValueLeft1
				);
			
			previousSourcePointerValueRight1 = 
				PostProcessingDwarfPlanet::writeToFrameBuffer
				(
					y, 32 -lut[lutEntries - counter], columnSourcePointerRight1, previousSourcePointerValueRight1
				);
			
			previousSourcePointerValueLeft2 = 
				PostProcessingDwarfPlanet::writeToFrameBuffer
				(
					y, 32 -lut[counter], columnSourcePointerLeft2, previousSourcePointerValueLeft2
				);
			
			previousSourcePointerValueRight2 = 
				PostProcessingDwarfPlanet::writeToFrameBuffer
				(
					y, 32 -lut[counter], columnSourcePointerRight2, previousSourcePointerValueRight2
				);
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
static uint32 PostProcessingDwarfPlanet::writeToFrameBuffer
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
