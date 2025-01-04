/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Camera.h>
#include <DirectDraw.h>
#include <Optics.h>
#include <Utilities.h>
#include <VUEngine.h>

#include "ReflectiveActor.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static inline uint32 ReflectiveActor::reverse(uint32 number, int32 bits)
{
    number = ((number & 0x55555555) << 1) | ((number & 0xAAAAAAAA) >> 1);
    number = ((number & 0x33333333) << 2) | ((number & 0xCCCCCCCC) >> 2);
    number = ((number & 0x0F0F0F0F) << 4) | ((number & 0xF0F0F0F0) >> 4);
    number = ((number & 0x00FF00FF) << 8) | ((number & 0xFF00FF00) >> 8);
    number = ((number & 0x0000FFFF) << 16) | ((number & 0xFFFF0000) >> 16);
    return number >> ((sizeof(uint32) << 3) - bits);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static uint32 ReflectiveActor::randomSeed()
{
	static uint32 seed = 7;

	if(!seed)
	{
		seed = 7;
	}

	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;

	return seed;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static void ReflectiveActor::reflect(uint32 currentDrawingFrameBufferSet, Entity entity)
{
	ASSERT(entity, "ReflectiveActor::reflect: null this");

	if(isDeleted(entity))
	{
		return;
	}

	ReflectiveActor this = ReflectiveActor::safeCast(entity);

	ReflectiveActor::applyReflection(this, currentDrawingFrameBufferSet);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static uint32 ReflectiveActor::getNoise(int16 passes)
{
	if(0 >= passes)
	{
		return 0;
	}

	uint32 noise = ReflectiveActor::randomSeed();

	for(; 0 < --passes;)
	{
		noise &= ReflectiveActor::randomSeed();
	}

	return noise;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static void ReflectiveActor::shiftPixels
(
	int32 pixelShift, REFLECTIVE_ACTOR_POINTER_TYPE* sourceValue, uint32 nextSourceValue, 
	REFLECTIVE_ACTOR_POINTER_TYPE* remainderValue, uint32 reflectionMask, uint32 noise
)
{
	*sourceValue &= reflectionMask;
	*remainderValue &= reflectionMask;

	if(0 < pixelShift)
	{
		REFLECTIVE_ACTOR_POINTER_TYPE remainderValueTemp = *remainderValue;
		*remainderValue = (*sourceValue >> (REFLECTIVE_ACTOR_BITS_PER_STEP - (pixelShift)));
		*sourceValue <<= (pixelShift);
		*sourceValue |= remainderValueTemp | noise;
	}
	else if(0 > pixelShift)
	{
		*sourceValue >>= (-pixelShift );
		*sourceValue |= (nextSourceValue << (REFLECTIVE_ACTOR_BITS_PER_STEP + pixelShift)) | noise;
		*remainderValue = nextSourceValue >> (-pixelShift);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void ReflectiveActor::drawReflection(uint32 currentDrawingFrameBufferSet,
	int16 xSourceStart, int16 ySourceStart,
	int16 xOutputStart, int16 yOutputStart,
	int16 width, int16 height,
	uint32 reflectionMask,
	uint16 axisForReversing, bool transparency, bool reflectParallax,
	int16 parallaxDisplacement,
	const uint8 waveLut[], int32 numberOfWaveLutEntries, fixed_t waveLutThrottleFactor,
	bool flattenTop __attribute__ ((unused)), bool flattenBottom,
	uint32 topBorderMask,
	uint32 bottomBorderMask,
	uint32 leftBorderMask,
	uint32 rightBorderMask,
	int16 noisePasses)
{
    int16 xSourceEnd = xSourceStart + width;
    int16 ySourceEnd = ySourceStart + height;
	int16 xOutputEnd = xOutputStart + width;
	int16 yOutputEnd = yOutputStart + height;

/*
    int16 xSourceStartTemp = xSourceStart;
    int16 ySourceStartTemp = ySourceStart;
	int16 xOutputStartTemp = xOutputStart;
	int16 yOutputStartTemp = yOutputStart;

    int16 xSourceEndTemp = xSourceEnd;
    int16 ySourceEndTemp = ySourceEnd;
	int16 xOutputEndTemp = xOutputEnd;
	int16 yOutputEndTemp = yOutputEnd;
*/
	// check if source and destination are not out of bounds
	if((xSourceStart > _cameraFrustum->x1) | (ySourceStart > _cameraFrustum->y1)
		|
		(xSourceEnd < _cameraFrustum->x0) | (ySourceEnd < _cameraFrustum->y0)
		|
		(xOutputStart > _cameraFrustum->x1) | (yOutputStart > _cameraFrustum->y1)
		|
		(xOutputStart > _cameraFrustum->x1) | (yOutputStart > _cameraFrustum->y1))
	{
		return;
	}

	fixed_t fixedNumberOfWaveLutEntries = __FIXED_MULT(waveLutThrottleFactor, __I_TO_FIXED(numberOfWaveLutEntries));

	uint32 transparentMask = transparency ? 0xFFFFFFFF : 0;

	int32 xClamping = 0;
	int32 xOutputStartSave = xOutputStart;

	// clamp values to not write out of the camera
	if(xSourceStart < _cameraFrustum->x0)
	{
		xClamping = _cameraFrustum->x0 - xSourceStart;
		xOutputStart += xClamping;
		xSourceStart = _cameraFrustum->x0;
	}

	if(xSourceEnd > _cameraFrustum->x1 - 1)
	{
		xClamping = xSourceEnd - _cameraFrustum->x1 + 1;
		xOutputEnd -= xClamping;
		xSourceEnd = _cameraFrustum->x1 - 1;
	}

	if(ySourceStart < _cameraFrustum->y0)
	{
		yOutputStart += _cameraFrustum->y0 - ySourceStart;
		ySourceStart = _cameraFrustum->y0;
	}

	if(ySourceEnd > _cameraFrustum->y1)
	{
		yOutputEnd -= (ySourceEnd - _cameraFrustum->y1);
		ySourceEnd = _cameraFrustum->y1;
	}

	// must clamp the output too, but moving the wave lut index accordingly
	if(xOutputStart < _cameraFrustum->x0)
	{
		xClamping = _cameraFrustum->x0 - xOutputStart;
		xSourceStart += xClamping;
		xOutputStart = _cameraFrustum->x0;
	}
	else if(xOutputStart >= _cameraFrustum->x1)
	{
		return;
	}

	if(xOutputEnd > _cameraFrustum->x1)
	{
		xClamping = xOutputEnd - _cameraFrustum->x1 + 1;

		if(__X_AXIS & axisForReversing)
		{
			xOutputStart += xClamping;
		}
		else
		{
			xSourceEnd -= xClamping;
		}

		xOutputEnd = _cameraFrustum->x1 - 1;
	}
	else if(xOutputEnd <= _cameraFrustum->x0)
	{
		return;
	}

	// must clamp the output too, but moving the wave lut index accordingly
	if(yOutputStart < _cameraFrustum->y0)
	{
		if(__Y_AXIS & axisForReversing)
		{
			ySourceEnd -= ((_cameraFrustum->y0 - yOutputStart) - REFLECTIVE_ACTOR_Y_STEP_SIZE);
		}
		else
		{
			ySourceStart += (_cameraFrustum->y0 - yOutputStart);
		}

		yOutputStart = _cameraFrustum->y0;
	}
	else if(yOutputStart >= _cameraFrustum->y1)
	{
		return;
	}

	if(yOutputEnd > _cameraFrustum->y1)
	{
		if(__Y_AXIS & axisForReversing)
		{
			ySourceStart += (yOutputEnd - _cameraFrustum->y1);
		}

		yOutputEnd = _cameraFrustum->y1;
	}
	else if(yOutputEnd <= _cameraFrustum->y0)
	{
		return;
	}

	int32 xSource = xSourceStart;
	int32 xOutput = xOutputStart;
	int32 xOutputLimit = xOutputEnd;
	int32 xOutputIncrement = 1;

	if(__X_AXIS & axisForReversing)
	{
		xOutput = xOutputEnd;
		xOutputLimit = xOutputStart;
		xOutputIncrement = -1;
	}

	uint32 reflectionMaskSave = reflectionMask;

	uint8 dummyWaveLut[] =
	{
		0
	};

	fixed_t waveLutIndexIncrement = this->waveLutIndexIncrement;

	if(!waveLut)
	{
		waveLutIndexIncrement = 0;
		this->waveLutIndex = 0;
		waveLut = dummyWaveLut;
		numberOfWaveLutEntries = 1;
	}

	int32 ySourceIncrement = 1;

	if(__Y_AXIS & axisForReversing)
	{
		int16 temp = ySourceEnd - REFLECTIVE_ACTOR_Y_STEP_SIZE;
		ySourceEnd = ySourceStart;
		ySourceStart = temp;
		ySourceIncrement = -1;
	}

    int32 ySourceStartHelper = ySourceStart >> REFLECTIVE_ACTOR_Y_STEP_SIZE_2_EXP;

	int32 xSourceDistance = __ABS(xSourceEnd - xSourceStart);
	int32 xOutputDistance = __ABS(xOutput - xOutputLimit);
	int32 xTotal = xOutputDistance > xSourceDistance ? xSourceDistance : xOutputDistance;

	this->waveLutIndex += waveLutIndexIncrement;

	if(0 > this->waveLutIndex)
	{
		this->waveLutIndex = fixedNumberOfWaveLutEntries - this->waveLutIndex;
	}
	else if(this->waveLutIndex >= fixedNumberOfWaveLutEntries)
	{
		this->waveLutIndex = 0;
	}

	int32 rightBorderSize = 0;
	uint32 temp = rightBorderMask;

	while(temp)
	{
		rightBorderSize++;
		temp >>= 2;
	}

	int32 xCounter = xOutputStart - xOutputStartSave;

	if(reflectParallax)
	{
		for(; xTotal--; xOutput += xOutputIncrement, xSource++, xCounter++)
		{
			uint32 border = leftBorderMask ? 0xFFFFFFFF : 0;
			leftBorderMask <<= 2;

			if(!border && xTotal < rightBorderSize)
			{
				border = rightBorderMask ? 0xFFFFFFFF : 0;
			}

			this->waveLutIndex += waveLutIndexIncrement;

			if(this->waveLutIndex >= fixedNumberOfWaveLutEntries)
			{
				this->waveLutIndex = 0;
			}

			int32 leftColumn = xOutput;
			int32 rightColumn = xOutput;

			if(parallaxDisplacement)
			{
//				leftColumn -= parallaxDisplacement;
				rightColumn += parallaxDisplacement;

				if((unsigned)(leftColumn - _cameraFrustum->x0) >= (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0))
				{
					continue;
				}

				if((unsigned)(rightColumn - _cameraFrustum->x0) >= (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0))
				{
					continue;
				}
			}

			int32 xRelativeCoordinate = (xCounter % width) + __FIXED_TO_I(this->waveLutIndex);
			int32 xIndex = (numberOfWaveLutEntries * xRelativeCoordinate) / width;

			if(xIndex >= numberOfWaveLutEntries)
			{
				xIndex = xIndex % numberOfWaveLutEntries;
			}

			int32 waveLutPixelDisplacement = waveLut[xIndex];

			int32 ySource = ySourceStartHelper;
			int32 yOutput = (yOutputStart + waveLutPixelDisplacement) >> REFLECTIVE_ACTOR_Y_STEP_SIZE_2_EXP;

			int32 pixelShift = 
				(
					__MODULO((yOutputStart + waveLutPixelDisplacement), 
					REFLECTIVE_ACTOR_Y_STEP_SIZE) - __MODULO(ySourceStart, REFLECTIVE_ACTOR_Y_STEP_SIZE)
				) << 1;

			reflectionMask = reflectionMaskSave;

			if(transparency && waveLutPixelDisplacement)
			{
				if(0 < pixelShift)
				{
					reflectionMask <<= pixelShift % waveLutPixelDisplacement;
				}
				else
				{
					reflectionMask >>= -pixelShift % waveLutPixelDisplacement;
				}
			}

			uint32 effectiveContentMaskDisplacement = 
				(__MODULO((yOutputStart + (flattenTop? 0 : waveLutPixelDisplacement)), REFLECTIVE_ACTOR_Y_STEP_SIZE) << 1);
			uint32 effectiveContentMask = 0xFFFFFFFF << effectiveContentMaskDisplacement;
			uint32 effectiveBackgroundMask = ~effectiveContentMask;
			effectiveContentMask &= ~(topBorderMask << effectiveContentMaskDisplacement);

			REFLECTIVE_ACTOR_POINTER_TYPE* columnSourcePointerLeft = 
				(REFLECTIVE_ACTOR_POINTER_TYPE*) (currentDrawingFrameBufferSet) + (xSource << REFLECTIVE_ACTOR_Y_SHIFT) + ySource;
			
			REFLECTIVE_ACTOR_POINTER_TYPE* columnSourcePointerRight = 
				(REFLECTIVE_ACTOR_POINTER_TYPE*) (currentDrawingFrameBufferSet | 0x00010000) + 
				(xSource << REFLECTIVE_ACTOR_Y_SHIFT) + ySource;
			
			REFLECTIVE_ACTOR_POINTER_TYPE* columnOutputPointerLeft = 
				(REFLECTIVE_ACTOR_POINTER_TYPE*) (currentDrawingFrameBufferSet) + (leftColumn << REFLECTIVE_ACTOR_Y_SHIFT) + yOutput;
			
			REFLECTIVE_ACTOR_POINTER_TYPE* columnOutputPointerRight = 
				(REFLECTIVE_ACTOR_POINTER_TYPE*) (currentDrawingFrameBufferSet | 0x00010000) + 
				(rightColumn << REFLECTIVE_ACTOR_Y_SHIFT) + yOutput;

			int32 columnSourcePointerLeftIncrement = ySourceIncrement;
			int32 columnSourcePointerRightIncrement = ySourceIncrement;

			REFLECTIVE_ACTOR_POINTER_TYPE sourceCurrentValueLeft = *columnSourcePointerLeft;
			columnSourcePointerLeft += columnSourcePointerLeftIncrement;
			REFLECTIVE_ACTOR_POINTER_TYPE sourceNextValueLeft = *columnSourcePointerLeft;

			REFLECTIVE_ACTOR_POINTER_TYPE sourceCurrentValueRight = *columnSourcePointerRight;
			columnSourcePointerRight += columnSourcePointerRightIncrement;

			REFLECTIVE_ACTOR_POINTER_TYPE sourceNextValueRight = *columnSourcePointerRight;

			REFLECTIVE_ACTOR_POINTER_TYPE outputValueLeft = *columnOutputPointerLeft;
			REFLECTIVE_ACTOR_POINTER_TYPE outputValueRight = *columnOutputPointerRight;

			if(__Y_AXIS & axisForReversing)
			{
				sourceCurrentValueLeft = ReflectiveActor::reverse(sourceCurrentValueLeft, REFLECTIVE_ACTOR_BITS_PER_STEP);
				sourceCurrentValueRight = ReflectiveActor::reverse(sourceCurrentValueRight, REFLECTIVE_ACTOR_BITS_PER_STEP);
				sourceNextValueLeft = ReflectiveActor::reverse(sourceNextValueLeft, REFLECTIVE_ACTOR_BITS_PER_STEP);
				sourceNextValueRight = ReflectiveActor::reverse(sourceNextValueRight, REFLECTIVE_ACTOR_BITS_PER_STEP);
			}

			waveLutPixelDisplacement =  flattenBottom ? 0 : waveLutPixelDisplacement;

			int32 yOutputRemainder = __MODULO((yOutputEnd + waveLutPixelDisplacement), REFLECTIVE_ACTOR_Y_STEP_SIZE) << 1;
			int32 yOutputLimit = (yOutputEnd + waveLutPixelDisplacement) >> REFLECTIVE_ACTOR_Y_STEP_SIZE_2_EXP;

			REFLECTIVE_ACTOR_POINTER_TYPE remainderLeftValue = yOutput >= yOutputLimit ? sourceCurrentValueLeft : 0;
			REFLECTIVE_ACTOR_POINTER_TYPE remainderRightValue = yOutput >= yOutputLimit ? sourceCurrentValueRight : 0;

			uint32 noise = ReflectiveActor::getNoise(noisePasses);

			for(; yOutput < yOutputLimit; yOutput++, ySource += ySourceIncrement)
			{
				ReflectiveActor::shiftPixels
				(
					pixelShift, &sourceCurrentValueLeft, sourceNextValueLeft, &remainderLeftValue, reflectionMask, noise
				);
				
				ReflectiveActor::shiftPixels
				(
					pixelShift, &sourceCurrentValueRight, sourceNextValueRight, &remainderRightValue, reflectionMask, noise
				);

				sourceCurrentValueLeft &= ~border;
				sourceCurrentValueRight &= ~border;
				sourceCurrentValueLeft |= transparentMask & outputValueLeft;
				sourceCurrentValueRight |= transparentMask & outputValueRight;
				sourceCurrentValueLeft &= effectiveContentMask;
				sourceCurrentValueRight &= effectiveContentMask;
				sourceCurrentValueLeft |= (outputValueLeft & effectiveBackgroundMask);
				sourceCurrentValueRight |= (outputValueRight & effectiveBackgroundMask);

				effectiveContentMask = 0xFFFFFFFF;
				effectiveBackgroundMask = 0;

				*columnOutputPointerLeft = sourceCurrentValueLeft;
				*columnOutputPointerRight = sourceCurrentValueRight;

				columnOutputPointerLeft++;
				columnOutputPointerRight++;

				if(transparency)
				{
					outputValueLeft = *columnOutputPointerLeft;
					outputValueRight = *columnOutputPointerRight;
				}

				sourceCurrentValueLeft = sourceNextValueLeft;
				sourceCurrentValueRight = sourceNextValueRight;

				columnSourcePointerLeft += columnSourcePointerLeftIncrement;
				columnSourcePointerRight += columnSourcePointerRightIncrement;

				sourceNextValueLeft = *columnSourcePointerLeft;
				sourceNextValueRight = *columnSourcePointerRight;

				if(__Y_AXIS & axisForReversing)
				{
					sourceNextValueLeft = ReflectiveActor::reverse(sourceNextValueLeft, REFLECTIVE_ACTOR_BITS_PER_STEP);
					sourceNextValueRight = ReflectiveActor::reverse(sourceNextValueRight, REFLECTIVE_ACTOR_BITS_PER_STEP);
				}
			}

			if(yOutputRemainder)
			{
				uint32 maskDisplacement = (REFLECTIVE_ACTOR_BITS_PER_STEP - yOutputRemainder);
				effectiveContentMask = 0xFFFFFFFF >> maskDisplacement;
				uint32 remainderContentMask = effectiveContentMask & ~(bottomBorderMask >> maskDisplacement);

				if(!transparency)
				{
					outputValueLeft = *columnOutputPointerLeft;
					outputValueRight = *columnOutputPointerRight;
				}

				if(0 <= pixelShift)
				{
					remainderLeftValue |= (sourceCurrentValueLeft << pixelShift);
					remainderRightValue |= (sourceCurrentValueRight << pixelShift);
				}
				else
				{
					remainderLeftValue |= (sourceNextValueLeft << (REFLECTIVE_ACTOR_BITS_PER_STEP + pixelShift));
					remainderRightValue |= (sourceNextValueRight << (REFLECTIVE_ACTOR_BITS_PER_STEP + pixelShift));
				}

				remainderLeftValue &= reflectionMask;
				remainderRightValue &= reflectionMask;

				remainderLeftValue |= transparentMask & outputValueLeft;
				remainderRightValue |= transparentMask & outputValueRight;

				uint32 finalLeftValue = 
					(outputValueLeft & ~effectiveContentMask) | (((remainderLeftValue | noise) & remainderContentMask) & ~border);
				uint32 finalRightValue = 
					(outputValueRight & ~effectiveContentMask) | (((remainderRightValue | noise) & remainderContentMask) & ~border);

				*columnOutputPointerLeft = finalLeftValue;
				*columnOutputPointerRight = finalRightValue;
			}
			else if(bottomBorderMask)
			{
				*(columnOutputPointerLeft - 1) &= ~(bottomBorderMask);
				*(columnOutputPointerRight - 1) &= ~(bottomBorderMask);
			}
		}
	}
	else
	{
		for(; xTotal--; xOutput += xOutputIncrement, xSource++, xCounter++)
		{
			uint32 border = leftBorderMask ? 0xFFFFFFFF : 0;
			leftBorderMask <<= 2;

			if(!border && xTotal < rightBorderSize)
			{
				border = rightBorderMask ? 0xFFFFFFFF : 0;
			}

			int32 leftColumn = xOutput;
			int32 rightColumn = xOutput;

			if(parallaxDisplacement)
			{
//				leftColumn -= parallaxDisplacement;
				rightColumn += parallaxDisplacement;

				if((unsigned)(leftColumn - _cameraFrustum->x0) >= (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0))
				{
					continue;
				}

				if((unsigned)(rightColumn - _cameraFrustum->x0) >= (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0))
				{
					continue;
				}
			}

			int32 xRelativeCoordinate = (xCounter % width) + __FIXED_TO_I(this->waveLutIndex);
			int32 xIndex = (numberOfWaveLutEntries * xRelativeCoordinate) / width;

			if(xIndex >= numberOfWaveLutEntries)
			{
				xIndex = xIndex % numberOfWaveLutEntries;
			}

			int32 waveLutPixelDisplacement = waveLut[xIndex];

			int32 ySource = ySourceStartHelper;
			int32 yOutput = (yOutputStart + waveLutPixelDisplacement) >> REFLECTIVE_ACTOR_Y_STEP_SIZE_2_EXP;

			int32 pixelShift = 
				(
					__MODULO((yOutputStart + waveLutPixelDisplacement), REFLECTIVE_ACTOR_Y_STEP_SIZE) 
					- __MODULO(ySourceStart, REFLECTIVE_ACTOR_Y_STEP_SIZE)
				) << 1;

			reflectionMask = reflectionMaskSave;

			if(transparency && waveLutPixelDisplacement)
			{
				if(0 < pixelShift)
				{
					reflectionMask <<= pixelShift % waveLutPixelDisplacement;
				}
				else
				{
					reflectionMask >>= -pixelShift % waveLutPixelDisplacement;
				}
			}

			uint32 effectiveContentMaskDisplacement = 
				(__MODULO((yOutputStart + (flattenTop? 0 : waveLutPixelDisplacement)), REFLECTIVE_ACTOR_Y_STEP_SIZE) << 1);
			uint32 effectiveContentMask = 0xFFFFFFFF << effectiveContentMaskDisplacement;
			uint32 effectiveBackgroundMask = ~effectiveContentMask;
			effectiveContentMask &= ~(topBorderMask << effectiveContentMaskDisplacement);

			REFLECTIVE_ACTOR_POINTER_TYPE* columnSourcePointerLeft = 
				(REFLECTIVE_ACTOR_POINTER_TYPE*) (currentDrawingFrameBufferSet) + (xSource << REFLECTIVE_ACTOR_Y_SHIFT) + ySource;
			
			REFLECTIVE_ACTOR_POINTER_TYPE* columnSourcePointerRight = 
				(REFLECTIVE_ACTOR_POINTER_TYPE*) (currentDrawingFrameBufferSet | 0x00010000) + 
				(xSource << REFLECTIVE_ACTOR_Y_SHIFT) + ySource;
			
			REFLECTIVE_ACTOR_POINTER_TYPE* columnOutputPointerLeft = 
				(REFLECTIVE_ACTOR_POINTER_TYPE*) (currentDrawingFrameBufferSet) + (leftColumn << REFLECTIVE_ACTOR_Y_SHIFT) + yOutput;
			
			REFLECTIVE_ACTOR_POINTER_TYPE* columnOutputPointerRight = 
				(REFLECTIVE_ACTOR_POINTER_TYPE*) (currentDrawingFrameBufferSet | 0x00010000) + 
				(rightColumn << REFLECTIVE_ACTOR_Y_SHIFT) + yOutput;

			int32 columnSourcePointerLeftIncrement = ySourceIncrement;

			REFLECTIVE_ACTOR_POINTER_TYPE sourceCurrentValueLeft = *columnSourcePointerLeft;
			REFLECTIVE_ACTOR_POINTER_TYPE sourceCurrentValueRight = *columnSourcePointerRight;
			columnSourcePointerLeft += columnSourcePointerLeftIncrement;
			REFLECTIVE_ACTOR_POINTER_TYPE sourceNextValueLeft = *columnSourcePointerLeft;

			REFLECTIVE_ACTOR_POINTER_TYPE outputValueLeft = *columnOutputPointerLeft;
			REFLECTIVE_ACTOR_POINTER_TYPE outputValueRight = *columnOutputPointerRight;

			if(__Y_AXIS & axisForReversing)
			{
				sourceCurrentValueLeft = ReflectiveActor::reverse(sourceCurrentValueLeft, REFLECTIVE_ACTOR_BITS_PER_STEP);
				sourceNextValueLeft = ReflectiveActor::reverse(sourceNextValueLeft, REFLECTIVE_ACTOR_BITS_PER_STEP);
			}

			waveLutPixelDisplacement =  flattenBottom ? 0 : waveLutPixelDisplacement;

			int32 yOutputRemainder = __MODULO((yOutputEnd + waveLutPixelDisplacement), REFLECTIVE_ACTOR_Y_STEP_SIZE) << 1;

			int32 yOutputLimit = (yOutputEnd + waveLutPixelDisplacement) >> REFLECTIVE_ACTOR_Y_STEP_SIZE_2_EXP;

			REFLECTIVE_ACTOR_POINTER_TYPE remainderLeftValue = yOutput < yOutputLimit ? 0 : sourceCurrentValueLeft;

			uint32 noise = ReflectiveActor::getNoise(noisePasses);

			for(; yOutput < yOutputLimit; yOutput++, ySource += ySourceIncrement)
			{
				ReflectiveActor::shiftPixels
				(
					pixelShift, &sourceCurrentValueLeft, sourceNextValueLeft, &remainderLeftValue, reflectionMask, noise
				);

				sourceCurrentValueLeft &= ~border;
				sourceCurrentValueLeft |= transparentMask & outputValueLeft;
				sourceCurrentValueLeft &= effectiveContentMask;
				sourceCurrentValueRight = sourceCurrentValueLeft;
				sourceCurrentValueLeft |= (outputValueLeft & effectiveBackgroundMask);
				sourceCurrentValueRight |= (outputValueRight & effectiveBackgroundMask);

				effectiveContentMask = 0xFFFFFFFF;
				effectiveBackgroundMask = 0;

				*columnOutputPointerLeft = sourceCurrentValueLeft;
				*columnOutputPointerRight = sourceCurrentValueRight;

				columnOutputPointerLeft++;
				columnOutputPointerRight++;

				if(transparency)
				{
					outputValueLeft = *columnOutputPointerLeft;
				}

				sourceCurrentValueLeft = sourceNextValueLeft;

				columnSourcePointerLeft += columnSourcePointerLeftIncrement;

				sourceNextValueLeft = *columnSourcePointerLeft;

				if(__Y_AXIS & axisForReversing)
				{
					sourceNextValueLeft = ReflectiveActor::reverse(sourceNextValueLeft, REFLECTIVE_ACTOR_BITS_PER_STEP);
				}
			}

			if(yOutputRemainder)
			{
				uint32 maskDisplacement = (REFLECTIVE_ACTOR_BITS_PER_STEP - yOutputRemainder);
				effectiveContentMask = 0xFFFFFFFF >> maskDisplacement;
				uint32 remainderContentMask = effectiveContentMask & ~(bottomBorderMask >> maskDisplacement);

				if(!transparency)
				{
					outputValueLeft = *columnOutputPointerLeft;
				}

				if(0 <= pixelShift)
				{
					remainderLeftValue |= (sourceCurrentValueLeft << pixelShift);
				}
				else
				{
					remainderLeftValue |= (sourceNextValueLeft << (REFLECTIVE_ACTOR_BITS_PER_STEP + pixelShift));
				}

				remainderLeftValue &= reflectionMask;
				remainderLeftValue |= transparentMask & outputValueLeft;

				uint32 finalLeftValue =
					(outputValueLeft & ~effectiveContentMask) | (((remainderLeftValue | noise) & remainderContentMask) & ~border);
				uint32 finalRightValue = 
					(*columnOutputPointerRight & ~effectiveContentMask) | (((remainderLeftValue | noise) & remainderContentMask) & ~border);

				*columnOutputPointerLeft = finalLeftValue;
				*columnOutputPointerRight = finalRightValue;
			}
			else if(bottomBorderMask)
			{
				*(columnOutputPointerLeft - 1) &= ~(bottomBorderMask);
				*(columnOutputPointerRight - 1) &= ~(bottomBorderMask);
			}
		}
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void ReflectiveActor::constructor(ReflectiveActorSpec* reflectiveActorSpec, int16 internalId, const char* const name)
{
	// Always explicitly call the base's constructor 
	Base::constructor(&reflectiveActorSpec->actorSpec, internalId, name);

	this->waveLutIndex = 0;
	this->waveLutIndexIncrement = 
		__FIXED_MULT
		(
			reflectiveActorSpec->waveLutThrottleFactor, 
			__FIXED_DIV(__I_TO_FIXED(reflectiveActorSpec->numberOfWaveLutEntries), __I_TO_FIXED(reflectiveActorSpec->width))
		);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void ReflectiveActor::destructor()
{
	// remove post processing effect
	VUEngine::removePostProcessingEffect(VUEngine::getInstance(), ReflectiveActor::reflect, Entity::safeCast(this));

	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void ReflectiveActor::ready(bool recursive)
{
	Base::ready(this, recursive);

	// add post processing effect
	VUEngine::pushFrontPostProcessingEffect(VUEngine::getInstance(), ReflectiveActor::reflect, Entity::safeCast(this));
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void ReflectiveActor::suspend()
{
	Base::suspend(this);

	// remove post processing effect
	VUEngine::removePostProcessingEffect(VUEngine::getInstance(), ReflectiveActor::reflect, Entity::safeCast(this));
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void ReflectiveActor::resume()
{
	Base::resume(this);

	// add post processing effect
	VUEngine::pushFrontPostProcessingEffect(VUEngine::getInstance(), ReflectiveActor::reflect, Entity::safeCast(this));
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void ReflectiveActor::applyReflection(uint32 currentDrawingFrameBufferSet)
{
	ReflectiveActorSpec* reflectiveActorSpec = (ReflectiveActorSpec*)this->actorSpec;

/*
	static fixed_t index = 0;

	const int16 displ[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
		9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1,
		-2, -3, -4, -5, -6, -7, -8, -9, -10,
		-9, -8, -7, -6, -5, -4, -3, -2, -1,
	};

	index += this->waveLutIndexIncrement;

	if(__FIXED_TO_I(index) >= sizeof(displ) / sizeof(int16))
	{
		index = 0;
	}
*/

	ReflectiveActor::drawReflection(this,
		currentDrawingFrameBufferSet,
		this->position2D.x + reflectiveActorSpec->sourceDisplacement.x,
		this->position2D.y + reflectiveActorSpec->sourceDisplacement.y,
		this->position2D.x + reflectiveActorSpec->outputDisplacement.x,
		this->position2D.y + reflectiveActorSpec->outputDisplacement.y,
		reflectiveActorSpec->width,
		reflectiveActorSpec->height,
		reflectiveActorSpec->reflectionMask,
		reflectiveActorSpec->axisForReversing,
		reflectiveActorSpec->transparency,
		reflectiveActorSpec->reflectParallax,
		reflectiveActorSpec->parallaxDisplacement,
		reflectiveActorSpec->waveLut,
		reflectiveActorSpec->numberOfWaveLutEntries,
		reflectiveActorSpec->waveLutThrottleFactor,
		reflectiveActorSpec->flattenTop, reflectiveActorSpec->flattenBottom,
		reflectiveActorSpec->topBorder, reflectiveActorSpec->bottomBorder,
		reflectiveActorSpec->leftBorder, reflectiveActorSpec->rightBorder,
		reflectiveActorSpec->noisePasses
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
