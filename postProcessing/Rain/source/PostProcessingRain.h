/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef POST_PROCESSING_RAIN_H_
#define POST_PROCESSING_RAIN_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Entity.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class PostProcessingDwarfPlanet
///
/// Inherits from ListenerObject
///
/// Implements a dynamic full screen rain effect.
static class PostProcessingRain : ListenerObject
{
	/// Apply the post processing effect.
	/// @param currentDrawingFrameBufferSet: The framebuffer set that's currently being accessed
	/// @param entity: Post-processing effect function's scope
	static void rain(uint32 currentDrawingFrameBufferSet, Entity entity);

	/// Apply a shrinked post processing effect.
	/// @param currentDrawingFrameBufferSet: The framebuffer set that's currently being accessed
	/// @param entity: Post-processing effect function's scope
	static void thinRain(uint32 currentDrawingFrameBufferSet, Entity entity);
}

#endif
