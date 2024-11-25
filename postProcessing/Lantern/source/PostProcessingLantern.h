/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef POST_PROCESSING_LANTERN_H_
#define POST_PROCESSING_LANTERN_H_


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
/// Adds a lantern like effect to any SpatialObject, where everything outside of a 
/// certain radius around the SpatialObject is rendered black.
static class PostProcessingLantern : ListenerObject
{
	/// Apply the post processing effect.
	/// @param currentDrawingFrameBufferSet: The framebuffer set that's currently being accessed
	/// @param spatialObject: Post-processing effect function's scope
	static void lantern(uint32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
}

#endif
