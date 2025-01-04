/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef POST_PROCESSING_TEST_H_
#define POST_PROCESSING_TEST_H_

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
/// Implements a simple test effect that lights up a rectangular area around any Entity.
static class PostProcessingTest : ListenerObject
{
	/// Apply the post processing effect.
	/// @param currentDrawingFrameBufferSet: The framebuffer set that's currently being accessed
	/// @param entity: Post-processing effect function's scope
	static void lighting(uint32 currentDrawingFrameBufferSet, Entity entity);

	static void dummy(uint32 currentDrawingFrameBufferSet, Entity entity);
}

#endif
