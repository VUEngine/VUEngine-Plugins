/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef POST_PROCESSING_RAIN_H_
#define POST_PROCESSING_RAIN_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SpatialObject.h>


//---------------------------------------------------------------------------------------------------------
//										FUNCTIONS
//---------------------------------------------------------------------------------------------------------

static class PostProcessingRain : ListenerObject
{
	static void rain(uint32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
	static void waterFall(uint32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
}


#endif
