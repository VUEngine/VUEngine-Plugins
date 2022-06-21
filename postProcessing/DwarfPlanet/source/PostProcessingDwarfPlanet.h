/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef POST_PROCESSING_DWARF_PLANET_H_
#define POST_PROCESSING_DWARF_PLANET_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SpatialObject.h>


//---------------------------------------------------------------------------------------------------------
//										FUNCTIONS
//---------------------------------------------------------------------------------------------------------

static class PostProcessingDwarfPlanet : ListenerObject
{
	static void dwarfPlanet(uint32 currentDrawingFrameBufferSet, SpatialObject spatialObject);
}


#endif
