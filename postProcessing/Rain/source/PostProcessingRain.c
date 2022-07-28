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

#include <PostProcessingRain.h>
#include <Optics.h>
#include <Utilities.h>
#include <DirectDraw.h>
#include <Game.h>
#include <Container.h>
#include <Entity.h>
#include <VIPManager.h>
#include <Camera.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define POST_PROCESSING_RAIN_SIZE_OF_uint16_POWER		1
#define POST_PROCESSING_RAIN_SIZE_OF_S16_POWER		1
#define POST_PROCESSING_RAIN_Y_STEP_SIZE			16
#define POST_PROCESSING_RAIN_Y_STEP_SIZE_2_EXP		4


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

static void PostProcessingRain::waterStream(
	uint32 currentDrawingFrameBufferSet,
	int16 xStart,
	int16 xEnd,
	int16 xDisplacement,
	uint16 xStep,
	int16 yStart,
	int16 yEnd,
	int16 yDisplacement,
	const uint16 yStep[],
	uint16 numberOfYSpeeds,
	uint16* yStepIndex,
	int16 yStepThrottle,
	int16 y[],
	uint16 numberOfYs,
	const uint16 dropletLength[],
	uint16 numberOfDropletSize,
	uint16* dropletLengthIndex,
	int32 minimumDropletLength,
	const int16 dropletParallax[],
	uint16 numberOfDropletParallax
)
{
	int32 yIndex = 0;

	if(xStart < _cameraFrustum->x0)
	{
		xStart = _cameraFrustum->x0;
	}

	if(xEnd > _cameraFrustum->x1 - 1)
	{
		xEnd = _cameraFrustum->x1 - 1;
	}

	if(yStart < _cameraFrustum->y0)
	{
		yStart = _cameraFrustum->y0;
	}

	if(yEnd > _cameraFrustum->y1 - 1)
	{
		yEnd = _cameraFrustum->y1 - 1;
	}

	int32 x = xDisplacement + xStart;

	if(x < _cameraFrustum->x0)
	{
		x = xEnd + x % xEnd;
	}

	if(x > xEnd)
	{
		x = x % xEnd;
	}

	// write to framebuffers for both screens
	int32 counter = 1;

	for(; counter <= xEnd; counter += xStep)
	{
		if(++yIndex >= numberOfYs)
		{
			yIndex = 0;
		}

		x += xStep;

		if(x >= xEnd)
		{
			x -= xEnd;
			x += xStart;
		}

		int32 leftColumn = x;
		int32 rightColumn = x;

		int16 dropletParallaxValue = dropletParallax[counter % numberOfDropletParallax];

		leftColumn -= dropletParallaxValue;
		rightColumn += dropletParallaxValue;

		if(0 >= leftColumn || 0 >= rightColumn)
		{
			continue;
		}
		else if(leftColumn >= xEnd || rightColumn >= xEnd)
		{
			continue;
		}

		// get pointer to currently manipulated 32 bits of framebuffer
		uint32* columnSourcePointerLeft = (uint32*) (currentDrawingFrameBufferSet) + (leftColumn << 4);
		uint32* columnSourcePointerRight = (uint32*) (currentDrawingFrameBufferSet | 0x00010000) + (rightColumn << 4);

		if(_cameraFrustum->y0 > y[yIndex] + yStart)
		{
			continue;
		}

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
		uint32 yStep = (y[yIndex] + yStart) >> POST_PROCESSING_RAIN_Y_STEP_SIZE_2_EXP;
		uint32 subY = __MODULO((y[yIndex] + yStart), POST_PROCESSING_RAIN_Y_STEP_SIZE);
		uint32 dropletMask = 0xFFFFFFFF << (subY << 1);

		if(++*dropletLengthIndex >= numberOfDropletSize)
		{
			*dropletLengthIndex = 0;
		}

		int32 effectiveDropletLength = (signed)dropletLength[*dropletLengthIndex] + yStepThrottle;

		if(minimumDropletLength > effectiveDropletLength)
		{
			continue;
		}

		if(effectiveDropletLength >= (signed)POST_PROCESSING_RAIN_Y_STEP_SIZE)
		{
			effectiveDropletLength = POST_PROCESSING_RAIN_Y_STEP_SIZE - 1;
		}

		int32 dropletLengthDifference = (POST_PROCESSING_RAIN_Y_STEP_SIZE - (subY + effectiveDropletLength)) << 1;

		if(0 < dropletLengthDifference)
		{
			dropletMask &= (0xFFFFFFFF >> dropletLengthDifference);
		}

		uint32* sourcePointerLeft = columnSourcePointerLeft + yStep;
		uint32* sourcePointerRight = columnSourcePointerRight + yStep;
		uint32 sourceValue = *sourcePointerLeft;

		if(!sourceValue)
		{
			if(__MODULO((int32)dropletLengthDifference, POST_PROCESSING_RAIN_Y_STEP_SIZE_2_EXP))
			{
				continue;
			}

			uint32 content = 0x55555555 & ((dropletMask & ~sourceValue) | (sourceValue & ~dropletMask));
			*sourcePointerLeft = content;
			*sourcePointerRight = content;
		}
		else
		{
			uint32 content = (dropletMask & ~sourceValue) | (sourceValue & ~dropletMask);
			*sourcePointerLeft = content;
			*sourcePointerRight = content;

			if(0 > dropletLengthDifference)
			{
				dropletMask = (0xFFFFFFFF << -dropletLengthDifference);
				sourceValue = *(sourcePointerLeft + 1);
				content = (~dropletMask & ~sourceValue) | (sourceValue & dropletMask);
				*(sourcePointerLeft + 1) = content;
				*(sourcePointerRight + 1) = content;
			}
		}
	}

	uint16 i = 0;

	for(; i < numberOfYs; i++)
	{
		if(++*yStepIndex >= numberOfYSpeeds)
		{
			*yStepIndex = 0;
		}

		y[i] += yStep[*yStepIndex] + yStepThrottle;

		int32 cumulativeY = y[i] + yStart + yDisplacement;

		if(yEnd - (POST_PROCESSING_RAIN_Y_STEP_SIZE >> 1) < cumulativeY)
		{
			y[i] = 0;
		}
	}
}

static void PostProcessingRain::calculateRainPrecipitation(fix19_13* yStepThrottle, fix19_13* xStep, fix19_13 maximumYThrottle, fix19_13 minimumYThrottle, fix19_13 maximumXStep, fix19_13 minimumXStep)
{
	static uint32 previousTime = 0;
	static uint8 timePeriodIndex = 0;
	static uint8 rainAccelerationIndex = 0;

	const uint8 timePeriod[] =
	{
		30, 25, 40, 35, 50, 50, 40, 45,
		30, 30, 35, 40, 50, 60, 20, 45,
	};

	const int8 rainAcceleration[] =
	{
		1, 0, -1, 0,
	};

	if(isDeleted(Game::getCurrentState(Game::getInstance())))
	{
		return;
	}

	uint32 currentTime = Clock::getTime(GameState::getClock(Game::getCurrentState(Game::getInstance())));

	if((currentTime - previousTime) / 1000 > timePeriod[timePeriodIndex])
	{
		previousTime = currentTime;

		if(++timePeriodIndex >= sizeof(timePeriod) / sizeof(uint8))
		{
			timePeriodIndex = 0;
		}

		if(++rainAccelerationIndex >= sizeof(rainAcceleration) / sizeof(int8))
		{
			rainAccelerationIndex = 0;
		}
	}

	// multiply by the game cycle per second
	int32 rainPeriod =  __I_TO_FIX19_13(((int32)timePeriod[timePeriodIndex] + previousTime % timePeriod[timePeriodIndex]) * 50);

	*yStepThrottle += __FIXED_TO_FIX19_13(__FIXED_DIV(__FIX19_13_TO_FIXED(rainAcceleration[rainAccelerationIndex] * (maximumYThrottle - minimumYThrottle)), __FIX19_13_TO_FIXED(rainPeriod)));
	*xStep -= __FIXED_TO_FIX19_13(__FIXED_DIV(__FIX19_13_TO_FIXED(rainAcceleration[rainAccelerationIndex] * (maximumXStep - minimumXStep)), __FIX19_13_TO_FIXED(rainPeriod)));

	if(*yStepThrottle < minimumYThrottle)
	{
		*yStepThrottle = minimumYThrottle;
	}
	else if(*yStepThrottle > maximumYThrottle)
	{
		*yStepThrottle = maximumYThrottle;
	}

	if(*xStep < minimumXStep)
	{
		*xStep = minimumXStep;
	}
	else if(*xStep > maximumXStep)
	{
		*xStep = maximumXStep;
	}
}

static void PostProcessingRain::rain(uint32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
 	#define POST_PROCESSING_RAIN_X_RANGE_1					383
 	#define POST_PROCESSING_RAIN_MINIMUM_DROPLET_LENGTH		3
 	#define POST_PROCESSING_RAIN_MINIMUM_Y_THROTTLE_1		__I_TO_FIX19_13(-5)
 	#define POST_PROCESSING_RAIN_MAXIMUM_Y_THROTTLE_1		__I_TO_FIX19_13(2)
 	#define POST_PROCESSING_RAIN_MINIMUM_X_STEP_1			__I_TO_FIX19_13(15)
 	#define POST_PROCESSING_RAIN_MAXIMUM_X_STEP_1			__I_TO_FIX19_13(90)
	static uint16 yStepIndex = 0;
	static uint16 dropletLengthIndex = 0;
	static fix19_13 yStepThrottle = POST_PROCESSING_RAIN_MINIMUM_Y_THROTTLE_1;
	static fix19_13 xStep = POST_PROCESSING_RAIN_MAXIMUM_X_STEP_1;
 	static Vector3D cameraPreviousPosition = {0, 0, 0};
 	static int32 cumulativeX = 0;
 	fix19_13 yScreenDisplacement = __I_TO_FIX19_13(__METERS_TO_PIXELS(_cameraPosition->y - cameraPreviousPosition.y));

 	cumulativeX += __METERS_TO_PIXELS(_cameraPosition->x - cameraPreviousPosition.x);
	PostProcessingRain::calculateRainPrecipitation(&yStepThrottle, &xStep, POST_PROCESSING_RAIN_MAXIMUM_Y_THROTTLE_1, POST_PROCESSING_RAIN_MINIMUM_Y_THROTTLE_1, POST_PROCESSING_RAIN_MAXIMUM_X_STEP_1, POST_PROCESSING_RAIN_MINIMUM_X_STEP_1);
	cameraPreviousPosition = *_cameraPosition;

 	const int16 dropletParallax[] =
 	{
 		0, 5, -2, 3, -3, 6, 9, -4, 0, 0, 8,
		7, -3, 2, -2, 0, 5, -3, 4, -4, 6, -7,
		0, 6, -6, 1, 0, 0, 5, -5, -7, 8, 9, 0
		,
 	};

 	const uint16 dropletLength[] =
 	{
 		3, 4, 5, 5, 4, 3, 6, 6, 5, 6, 8, 5, 5,
 	};

	static int16 y[] =
	{
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74, 59,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,
	};

	const uint16 yStep[] =
	{
		4, 5, 6, 6, 7, 8, 8, 6, 5, 4, 4, 5,
		6, 7, 8, 4, 5, 5, 5, 6, 7, 5, 4, 8,
		4, 4, 7, 8, 8, 5, 7, 3, 4, 7, 5, 3,
		6, 7, 4, 5, 6, 8, 5, 5, 6, 7, 8, 6,
		6, 7, 8, 4, 5, 6, 5, 4, 8, 5, 4, 4,
		8, 5, 7, 3, 4, 4, 7, 8, 4, 7, 5, 3,


/*		9, 7, 8, 7, 6, 7, 8, 5, 6, 8, 4, 5,
		5, 6, 8, 7, 7, 6, 5, 5, 6, 4, 7, 8,
		8, 7, 9, 6, 8, 7, 6, 6, 5, 7, 8, 7,
		7, 6, 7, 7, 6, 5, 6, 7, 6, 6, 5, 8,
		5, 6, 8, 4, 4, 6, 5, 5, 6, 6, 7, 8,
		6, 7, 8, 7, 6, 7, 8, 4, 6, 8, 6, 5,
		7, 6, 7, 5, 6, 5, 6, 7, 6, 9, 5, 8,
		*/
	};

	// must account for the camera displacement
	yStepThrottle -= yScreenDisplacement;

	PostProcessingRain::waterStream(
		currentDrawingFrameBufferSet,
		0,
		__SCREEN_WIDTH - 1,
		-cumulativeX,
		__FIX19_13_TO_I(xStep),
		_cameraFrustum->y0,
		_cameraFrustum->y1,
		0,
		yStep,
		sizeof(yStep) >> POST_PROCESSING_RAIN_SIZE_OF_uint16_POWER,
		&yStepIndex,
		__FIX19_13_TO_I(yStepThrottle),
		y,
		sizeof(y) >> POST_PROCESSING_RAIN_SIZE_OF_S16_POWER,
		dropletLength,
		sizeof(dropletLength) >> POST_PROCESSING_RAIN_SIZE_OF_uint16_POWER,
		&dropletLengthIndex,
		POST_PROCESSING_RAIN_MINIMUM_DROPLET_LENGTH,
		dropletParallax,
		sizeof(dropletParallax) >> POST_PROCESSING_RAIN_SIZE_OF_S16_POWER
	);

	yStepThrottle += yScreenDisplacement;
}

static void PostProcessingRain::waterFall(uint32 currentDrawingFrameBufferSet, Vector3D position, int32 width, int32 height, int32 yStepThrottle)
{
	static uint16 yStepIndex = 0;
	static uint16 dropletLengthIndex = 0;

 	const int16 dropletParallax[] =
 	{
 		-2
		,
 	};

 	const uint16 dropletLength[] =
 	{
 		5, 6, 9, 11, 4, 13, 11, 4, 7, 9, 5, 12, 9,
 		11, 10, 4, 7, 12, 12, 10, 8, 5, 4, 8, 10
 	};

	static int16 y[] =
	{
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74, 59,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74, 59,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,

	};

	const uint16 yStep[] =
	{
		4, 5, 6, 6, 7, 8, 8, 6, 5, 4, 4, 5,
		6, 7, 8, 4, 5, 5, 5, 6, 7, 5, 4, 8,
		4, 4, 7, 8, 8, 5, 7, 3, 4, 7, 5, 3,
		6, 7, 4, 5, 6, 8, 5, 5, 6, 7, 8, 6,
		6, 7, 8, 4, 5, 6, 5, 4, 8, 5, 4, 4,
		8, 5, 7, 3, 4, 4, 7, 8, 4, 7, 5, 3,
	};

	PostProcessingRain::waterStream(
		currentDrawingFrameBufferSet,
		__FIXED_TO_I(position.x) - (width >> 1),
		__FIXED_TO_I(position.x) + (width >> 1),
		0,
		1,
		__FIXED_TO_I(position.y) - (height >> 1),
		__FIXED_TO_I(position.y) + (height >> 1),
		0,
		yStep,
		sizeof(yStep) >> POST_PROCESSING_RAIN_SIZE_OF_uint16_POWER,
		&yStepIndex,
		yStepThrottle,
		y,
		sizeof(y) >> POST_PROCESSING_RAIN_SIZE_OF_S16_POWER,
		dropletLength,
		sizeof(dropletLength) >> POST_PROCESSING_RAIN_SIZE_OF_uint16_POWER,
		&dropletLengthIndex,
		1,
		dropletParallax,
		sizeof(dropletParallax) >> POST_PROCESSING_RAIN_SIZE_OF_S16_POWER
	);
}

static void PostProcessingRain::waterFall20x100(uint32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
	if(isDeleted(spatialObject))
	{
		return;
	}

	Vector3D spatialObjectPosition = Vector3D::getRelativeToCamera(*SpatialObject::getPosition(spatialObject));

	PostProcessingRain::waterFall(currentDrawingFrameBufferSet, spatialObjectPosition, 20, 100, 0);
}
