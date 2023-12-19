/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Container.h>
#include <Camera.h>

#include "PostProcessingLantern.h"


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define POST_PROCESSING_LANTERN_SIZE_OF_S16_POWER		1
#define POST_PROCESSING_LANTERN_Y_STEP_SIZE				16
#define POST_PROCESSING_LANTERN_Y_STEP_SIZE_2_EXP		4


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

static void PostProcessingLantern::applyMask(uint32 currentDrawingFrameBufferSet, int32 xStart, int32 xEnd, int32 yStart, int32 yEnd, uint32 mask)
{
	if(xEnd < xStart || yEnd < yStart)
	{
		return;
	}

	if(xStart < _cameraFrustum->x0)
	{
		xStart = _cameraFrustum->x0;
	}

	if(xEnd > _cameraFrustum->x1)
	{
		xEnd = _cameraFrustum->x1;
	}

	if(yStart < _cameraFrustum->y0)
	{
		yStart = _cameraFrustum->y0;
	}

	if(yEnd > _cameraFrustum->y1)
	{
		yEnd = _cameraFrustum->y1;
	}

	for(; xStart <= xEnd; xStart++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		uint32* columnSourcePointerLeft = (uint32*) (currentDrawingFrameBufferSet) + (xStart << 4);
		uint32* columnSourcePointerRight = (uint32*) (currentDrawingFrameBufferSet | 0x00010000) + (xStart << 4);

		int32 y = yStart;

		for(; y < yEnd; y++)
		{
			uint32* sourcePointerLeft = columnSourcePointerLeft + y;
			uint32* sourcePointerRight = columnSourcePointerRight + y;
			*sourcePointerLeft &= mask;
			*sourcePointerRight &= mask;
		}
	}
}

static void PostProcessingLantern::ellipticalWindow(uint32 currentDrawingFrameBufferSet, PixelVector position, int16 ellipsisArc[], uint16 ellipsisHorizontalAxisSize, uint32 penumbraMask, bool roundBorder)
{
 	int32 xPosition = position.x;
 	int32 yPosition = position.y;
	// move y position to the closest 16 multiple
	int32 tempYPosition = yPosition + (POST_PROCESSING_LANTERN_Y_STEP_SIZE >> 1);
	yPosition = tempYPosition - __MODULO(tempYPosition, POST_PROCESSING_LANTERN_Y_STEP_SIZE);

	int32 ellipsisArcIndex = 0 > xPosition - ellipsisHorizontalAxisSize ? (ellipsisHorizontalAxisSize - xPosition) : 0;
	int32 ellipsisArcIndexDelta = 1;
	int32 x = 0;

	for(x = _cameraFrustum->x0; x < _cameraFrustum->x1; x++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		uint32* columnSourcePointerLeft = (uint32*) (currentDrawingFrameBufferSet) + (x << 4);
		uint32* columnSourcePointerRight = (uint32*) (currentDrawingFrameBufferSet | 0x00010000) + (x << 4);

		int32 yStart = _cameraFrustum->y0 >> POST_PROCESSING_LANTERN_Y_STEP_SIZE_2_EXP;
		int32 yEnd = (_cameraFrustum->y1 - 16) >> POST_PROCESSING_LANTERN_Y_STEP_SIZE_2_EXP; // do not write over GUI
		int32 y = yStart;

		int32 ellipsisY = ellipsisArc[ellipsisArcIndex];
		int32 maskDisplacement = __MODULO(ellipsisY, POST_PROCESSING_LANTERN_Y_STEP_SIZE) << 1;
		uint32 upperMask = roundBorder ? ~(0xFFFFFFFF >> maskDisplacement) : 0xFFFFFFFF;
		uint32 lowerMask = roundBorder ? ~(0xFFFFFFFF << maskDisplacement) : 0xFFFFFFFF;

		int32 yLowerLimit =  (yPosition + ellipsisY) >> POST_PROCESSING_LANTERN_Y_STEP_SIZE_2_EXP;
		int32 yUpperLimit = (yPosition >> POST_PROCESSING_LANTERN_Y_STEP_SIZE_2_EXP) - (yLowerLimit - (yPosition >> POST_PROCESSING_LANTERN_Y_STEP_SIZE_2_EXP));

		if(yUpperLimit > yEnd)
		{
			yUpperLimit = yEnd;
		}

		if(yLowerLimit < yStart)
		{
			yLowerLimit = yStart;
		}

		uint32* sourcePointerLeft = columnSourcePointerLeft + y;
		uint32* sourcePointerRight = columnSourcePointerRight + y;

		if((unsigned)(x - (xPosition - ellipsisHorizontalAxisSize)) < (unsigned)(ellipsisHorizontalAxisSize << 1))
		{
			for(; y < yUpperLimit; y++)
			{
				sourcePointerLeft = columnSourcePointerLeft + y;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft = 0;
				*sourcePointerRight = 0;
			}

			if(y == yUpperLimit && y < yEnd)
			{
				sourcePointerLeft = columnSourcePointerLeft + y;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft &= upperMask & penumbraMask;
				*sourcePointerRight &= upperMask & penumbraMask;
			}

			if(penumbraMask)
			{
				y = yUpperLimit + 1;

				if(y >= yStart && y < yEnd)
				{
					uint32* sourcePointerLeft = columnSourcePointerLeft + y;
					uint32* sourcePointerRight = columnSourcePointerRight + y;
					*sourcePointerLeft &= penumbraMask | upperMask;
					*sourcePointerRight &= penumbraMask | upperMask;
				}

				y = yLowerLimit - 1;

				if(y >= yStart && y < yEnd)
				{
					uint32* sourcePointerLeft = columnSourcePointerLeft + y;
					uint32* sourcePointerRight = columnSourcePointerRight + y;
					*sourcePointerLeft &= penumbraMask | lowerMask;
					*sourcePointerRight &= penumbraMask | lowerMask;
				}
			}

			y = yLowerLimit;

			if(y >= yStart && y < yEnd)
			{
				sourcePointerLeft = columnSourcePointerLeft + y;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft &= lowerMask & penumbraMask;
				*sourcePointerRight &= lowerMask & penumbraMask;
			}

			for(; ++y < yEnd;)
			{
				uint32* sourcePointerLeft = columnSourcePointerLeft + y;
				uint32* sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft = 0;
				*sourcePointerRight = 0;
			}

			ellipsisArcIndex += ellipsisArcIndexDelta;

			if(ellipsisArcIndex >= ellipsisHorizontalAxisSize)
			{
				ellipsisArcIndexDelta = -1;
				ellipsisArcIndex = ellipsisHorizontalAxisSize - 1;
			}
			else if(0 > ellipsisArcIndex)
			{
				ellipsisArcIndexDelta = 1;
				ellipsisArcIndex = 0;
			}
		}
		else
		{
			for(; y < yEnd; y++)
			{
				sourcePointerLeft = columnSourcePointerLeft + y ;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft = 0;
				*sourcePointerRight = 0;
			}
		}
	}
}

static void PostProcessingLantern::lantern(uint32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
 	static bool ellipsisArcCalculated = false;

	if(isDeleted(spatialObject))
	{
 		if(ellipsisArcCalculated)
 		{
 			PostProcessingLantern::applyMask(currentDrawingFrameBufferSet, _cameraFrustum->x0, _cameraFrustum->x1, _cameraFrustum->y0, _cameraFrustum->y1, 0);
 		}
 		return;
	}

	PixelVector screenPixelPosition = PixelVector::project(Vector3D::getRelativeToCamera(*SpatialObject::getPosition(spatialObject)), 0);

 	screenPixelPosition.y -= 10;

 	#define ELLIPSIS_X_AXIS_LENGTH		65
 	#define ELLIPSIS_Y_AXIS_LENGTH		70
	#define PENUMBRA_MASK				0x55555555

 	static int16 ellipsisArc[ELLIPSIS_X_AXIS_LENGTH];

 	if(!ellipsisArcCalculated)
	{
		ellipsisArcCalculated = true;

		uint16 i = 0;
		float x = 0;

		for(i = sizeof(ellipsisArc) >> POST_PROCESSING_LANTERN_SIZE_OF_S16_POWER; --i; x++)
		{
			ellipsisArc[i] = ELLIPSIS_Y_AXIS_LENGTH * Math::squareRoot(((ELLIPSIS_X_AXIS_LENGTH * ELLIPSIS_X_AXIS_LENGTH) - (x * x)) / (ELLIPSIS_X_AXIS_LENGTH * ELLIPSIS_X_AXIS_LENGTH));
		}
	}

	PostProcessingLantern::ellipticalWindow(currentDrawingFrameBufferSet, screenPixelPosition, ellipsisArc, ELLIPSIS_X_AXIS_LENGTH, PENUMBRA_MASK, true);
}

