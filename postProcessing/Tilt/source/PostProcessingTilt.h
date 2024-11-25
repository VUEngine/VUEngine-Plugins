/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef POST_PROCESSING_TILT_H_
#define POST_PROCESSING_TILT_H_


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <SpatialObject.h>


//=========================================================================================================
// CLASS' DECLARATION
//=========================================================================================================

///
/// Class PostProcessingDwarfPlanet
///
/// Inherits from ListenerObject
///
/// Implements a "tilting" effect of the game image by a few percent by gradually shifting columns.
static class PostProcessingTilt : ListenerObject
{
	/// Apply the post processing effect.
	/// @param currentDrawingFrameBufferSet: The framebuffer set that's currently being accessed
	/// @param spatialObject: Post-processing effect function's scope
	static void tiltScreen(uint32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
}

#endif
