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

#include <PostProcessingRhombus.h>
#include <Optics.h>
#include <Utilities.h>
#include <DirectDraw.h>
#include <VUEngine.h>
#include <Container.h>
#include <Entity.h>
#include <VIPManager.h>
#include <Camera.h>


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

/**
 * Helper function used by the rhombus emitter effect that prints a rhombus shape to the frame buffer
 *
 * @param radius
 * @param color
 * @param screenPixelPosition
 */
static void PostProcessingRhombus::drawRhombus(int32 radius, uint32 color, PixelVector screenPixelPosition, int32 parallax)
{
	DirectDraw::drawColorLine(
		(PixelVector) {screenPixelPosition.x - radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y - radius,	0, parallax},
		color,
		0,
		false
	);

	DirectDraw::drawColorLine(
		(PixelVector) {screenPixelPosition.x + radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y - radius,	0, parallax},
		color,
		0,
		false
	);

	DirectDraw::drawColorLine(
		(PixelVector) {screenPixelPosition.x + radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y + radius,	0, parallax},
		color,
		0,
		false
	);

	DirectDraw::drawColorLine(
		(PixelVector) {screenPixelPosition.x - radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y + radius,	0, parallax},
		color,
		0,
		false
	);
}

/**
 * Uses directdraw to draw a rhombus around the spatialObject.
 * This effect only writes to the framebuffers, but does not read them. Since write access is much quicker
 * than reading, and since only a few pixels are affected, this effect runs well on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
static void PostProcessingRhombus::rhombus(uint32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject)
{
	// runtime working variable
	static int32 radius = 4;

	if(isDeleted(spatialObject))
	{
		return;
	}

	PixelVector screenPixelPosition = PixelVector::project(Vector3D::getRelativeToCamera(*SpatialObject::getPosition(spatialObject)), 0);

	// increase radius by 1 in each cycle
	radius++;

	if(radius > 184)
	{
		// reset radius when reaching a certain length
		radius = 4;
	}
	else if(radius > 64)
	{
		// pause for a little bit before restarting
		return;
	}

	// draw a rhombus around object with given radius and color
	PostProcessingRhombus::drawRhombus((radius), __COLOR_BLACK, screenPixelPosition, -((radius + 4) >> 5));
//	PostProcessingRhombus::drawRhombus((radius >> 1), __COLOR_BLACK, screenPixelPosition, -(((radius >> 1) + 4) >> 5));
}
