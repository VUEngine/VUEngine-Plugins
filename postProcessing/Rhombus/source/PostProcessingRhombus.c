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
#include <FrameBufferManager.h>
#include <Optics.h>
#include <Utilities.h>
#include <VIPManager.h>
#include <VUEngine.h>

#include "PostProcessingRhombus.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/*
 * Uses FrameBufferManager to draw a rhombus around the entity.
 * This effect only writes to the framebuffers, but does not read them. Since write access is much quicker
 * than reading, and since only a few pixels are affected, this effect runs well on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
static void PostProcessingRhombus::rhombus
(
	uint32 currentDrawingFrameBufferSet __attribute__ ((unused)), Entity entity
)
{
	// Runtime working variable
	static int32 radius = 4;

	if(isDeleted(entity))
	{
		return;
	}

	PixelVector screenPixelPosition = 
		PixelVector::projectVector3D(Vector3D::getRelativeToCamera(*Entity::getPosition(entity)), 0);

	// Increase radius by 1 in each cycle
	radius++;

	if(radius > 184)
	{
		// Reset radius when reaching a certain length
		radius = 4;
	}
	else if(radius > 64)
	{
		// Pause for a little bit before restarting
		return;
	}

	// Draw a rhombus around object with given radius and color
	PostProcessingRhombus::drawRhombus((radius), __COLOR_BLACK, screenPixelPosition, -((radius + 4) >> 5));
//	PostProcessingRhombus::drawRhombus((radius >> 1), __COLOR_BLACK, screenPixelPosition, -(((radius >> 1) + 4) >> 5));
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/*
 * Helper function used by the rhombus emitter effect that prints a rhombus collider to the frame buffer
 *
 * @param radius
 * @param color
 * @param screenPixelPosition
 */
static void PostProcessingRhombus::drawRhombus(int32 radius, uint32 color, PixelVector screenPixelPosition, int32 parallax)
{
	FrameBufferManager::drawLine
	(
		(PixelVector) {screenPixelPosition.x - radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y - radius,	0, parallax},
		color,
		0,
		false
	);

	FrameBufferManager::drawLine
	(
		(PixelVector) {screenPixelPosition.x + radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y - radius,	0, parallax},
		color,
		0,
		false
	);

	FrameBufferManager::drawLine
	(
		(PixelVector) {screenPixelPosition.x + radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y + radius,	0, parallax},
		color,
		0,
		false
	);

	FrameBufferManager::drawLine
	(
		(PixelVector) {screenPixelPosition.x - radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y + radius,	0, parallax},
		color,
		0,
		false
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
