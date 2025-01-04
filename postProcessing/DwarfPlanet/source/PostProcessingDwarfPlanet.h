/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef POST_PROCESSING_DWARF_PLANET_H_
#define POST_PROCESSING_DWARF_PLANET_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <GameObject.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class PostProcessingDwarfPlanet
///
/// Inherits from ListenerObject
///
/// Implements a "bending down" of the left and right edges of the screen to make the 
/// game world look like a very small planet.
static class PostProcessingDwarfPlanet : ListenerObject
{
	/// Apply the post processing effect.
	/// @param currentDrawingFrameBufferSet: The framebuffer set that's currently being accessed
	/// @param gameObject: Post-processing effect function's scope
	static void dwarfPlanet(uint32 currentDrawingFrameBufferSet, GameObject gameObject);
}

#endif
