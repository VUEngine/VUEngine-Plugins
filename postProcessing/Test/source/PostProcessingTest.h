/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef POST_PROCESSING_TEST_H_
#define POST_PROCESSING_TEST_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SpatialObject.h>


//---------------------------------------------------------------------------------------------------------
//										FUNCTIONS
//---------------------------------------------------------------------------------------------------------

static class PostProcessingTest : Object
{
	static void lighting(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
	static void dummy(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
}


#endif
