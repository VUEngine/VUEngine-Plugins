/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef POST_PROCESSING_RHOMBUS_H_
#define POST_PROCESSING_RHOMBUS_H_


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
/// Implements the drawing of a growing rhombus emitted from any SpatialObject.
static class PostProcessingRhombus : ListenerObject
{
	/// Apply the post processing effect.
	/// @param currentDrawingFrameBufferSet: The framebuffer set that's currently being accessed
	/// @param spatialObject: Post-processing effect function's scope
	static void rhombus(uint32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
}


#endif
