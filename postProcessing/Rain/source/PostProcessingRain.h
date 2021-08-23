/*
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
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

static class PostProcessingRain : Object
{
	static void rain(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
	static void waterFall20x100(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
}

#endif
