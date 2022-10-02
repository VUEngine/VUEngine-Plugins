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

#include <ReflectiveEntity.h>
#include <VUEngine.h>
#include <Optics.h>
#include <Camera.h>
#include <Utilities.h>
#include <DirectDraw.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

static uint32 ReflectiveEntity::randomSeed()
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

void ReflectiveEntity::constructor(ReflectiveEntitySpec* reflectiveEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(&reflectiveEntitySpec->entitySpec, internalId, name);

	this->waveLutIndex = 0;
	this->waveLutIndexIncrement = __FIXED_MULT(reflectiveEntitySpec->waveLutThrottleFactor, __FIXED_DIV(__I_TO_FIXED(reflectiveEntitySpec->numberOfWaveLutEntries), __I_TO_FIXED(reflectiveEntitySpec->width)));
	this->nextFramePosition2D = this->position2D = (Point){_cameraFrustum->x1 + 1, _cameraFrustum->y1 + 1};
}

void ReflectiveEntity::destructor()
{
	// remove post processing effect
	VUEngine::removePostProcessingEffect(VUEngine::getInstance(), ReflectiveEntity::reflect, SpatialObject::safeCast(this));

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void ReflectiveEntity::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// add post processing effect
	VUEngine::pushFrontPostProcessingEffect(VUEngine::getInstance(), ReflectiveEntity::reflect, SpatialObject::safeCast(this));
}

void ReflectiveEntity::suspend()
{
	Base::suspend(this);

	// remove post processing effect
	VUEngine::removePostProcessingEffect(VUEngine::getInstance(), ReflectiveEntity::reflect, SpatialObject::safeCast(this));
}

void ReflectiveEntity::resume()
{
	Base::resume(this);

	// add post processing effect
	VUEngine::pushFrontPostProcessingEffect(VUEngine::getInstance(), ReflectiveEntity::reflect, SpatialObject::safeCast(this));
}

void ReflectiveEntity::synchronizeGraphics()
{
	Base::synchronizeGraphics(this);
	
	Vector3D position3D = Vector3D::getRelativeToCamera(this->transformation.globalPosition);

	PixelVector position2D = PixelVector::project(position3D, 0);

	this->position2D = this->nextFramePosition2D;
	this->nextFramePosition2D.x = position2D.x;
	this->nextFramePosition2D.y = position2D.y;
}

static void ReflectiveEntity::reflect(uint32 currentDrawingFrameBufferSet, SpatialObject spatialObject)
{
	ASSERT(spatialObject, "ReflectiveEntity::reflect: null this");

	if(isDeleted(spatialObject))
	{
		return;
	}

	ReflectiveEntity this = ReflectiveEntity::safeCast(spatialObject);

	ReflectiveEntity::applyReflection(this, currentDrawingFrameBufferSet);
}

void ReflectiveEntity::applyReflection(uint32 currentDrawingFrameBufferSet)
{
	ReflectiveEntitySpec* reflectiveEntitySpec = (ReflectiveEntitySpec*)this->entitySpec;

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

	ReflectiveEntity::drawReflection(this,
		currentDrawingFrameBufferSet,
		this->position2D.x + reflectiveEntitySpec->sourceDisplacement.x,
		this->position2D.y + reflectiveEntitySpec->sourceDisplacement.y,
		this->position2D.x + reflectiveEntitySpec->outputDisplacement.x,
		this->position2D.y + reflectiveEntitySpec->outputDisplacement.y,
		reflectiveEntitySpec->width,
		reflectiveEntitySpec->height,
		reflectiveEntitySpec->reflectionMask,
		reflectiveEntitySpec->axisForReversing,
		reflectiveEntitySpec->transparent,
		reflectiveEntitySpec->reflectParallax,
		reflectiveEntitySpec->parallaxDisplacement,
		reflectiveEntitySpec->waveLut,
		reflectiveEntitySpec->numberOfWaveLutEntries,
		reflectiveEntitySpec->waveLutThrottleFactor,
		reflectiveEntitySpec->flattenTop, reflectiveEntitySpec->flattenBottom,
		reflectiveEntitySpec->topBorder, reflectiveEntitySpec->bottomBorder,
		reflectiveEntitySpec->leftBorder, reflectiveEntitySpec->rightBorder,
		reflectiveEntitySpec->noisePasses
	);
}

static uint32 ReflectiveEntity::getNoise(int16 passes)
{
	if(0 >= passes)
	{
		return 0;
	}

	uint32 noise = ReflectiveEntity::randomSeed();

	for(; 0 < --passes;)
	{
		noise &= ReflectiveEntity::randomSeed();
	}

	return noise;
}

static void ReflectiveEntity::shiftPixels(int32 pixelShift, REFLECTIVE_ENTITY_POINTER_TYPE* sourceValue, uint32 nextSourceValue, REFLECTIVE_ENTITY_POINTER_TYPE* remainderValue, uint32 reflectionMask, uint32 noise)
{
	*sourceValue &= reflectionMask;
	*remainderValue &= reflectionMask;

	if(0 < pixelShift)
	{
		REFLECTIVE_ENTITY_POINTER_TYPE remainderValueTemp = *remainderValue;
		*remainderValue = (*sourceValue >> (REFLECTIVE_ENTITY_BITS_PER_STEP - (pixelShift)));
		*sourceValue <<= (pixelShift);
		*sourceValue |= remainderValueTemp | noise;
	}
	else if(0 > pixelShift)
	{
		*sourceValue >>= (-pixelShift );
		*sourceValue |= (nextSourceValue << (REFLECTIVE_ENTITY_BITS_PER_STEP + pixelShift)) | noise;
		*remainderValue = nextSourceValue >> (-pixelShift);
	}
}

void ReflectiveEntity::drawReflection(uint32 currentDrawingFrameBufferSet,
	int16 xSourceStart, int16 ySourceStart,
	int16 xOutputStart, int16 yOutputStart,
	int16 width, int16 height,
	uint32 reflectionMask,
	uint16 axisForReversing, bool transparent, bool reflectParallax,
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

	uint32 transparentMask = transparent ? 0xFFFFFFFF : 0;

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
			ySourceEnd -= ((_cameraFrustum->y0 - yOutputStart) - REFLECTIVE_ENTITY_Y_STEP_SIZE);
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
		int16 temp = ySourceEnd - REFLECTIVE_ENTITY_Y_STEP_SIZE;
		ySourceEnd = ySourceStart;
		ySourceStart = temp;
		ySourceIncrement = -1;
	}

    int32 ySourceStartHelper = ySourceStart >> REFLECTIVE_ENTITY_Y_STEP_SIZE_2_EXP;

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
			int32 yOutput = (yOutputStart + waveLutPixelDisplacement) >> REFLECTIVE_ENTITY_Y_STEP_SIZE_2_EXP;

			int32 pixelShift = (__MODULO((yOutputStart + waveLutPixelDisplacement), REFLECTIVE_ENTITY_Y_STEP_SIZE) - __MODULO(ySourceStart, REFLECTIVE_ENTITY_Y_STEP_SIZE)) << 1;

			reflectionMask = reflectionMaskSave;

			if(transparent && waveLutPixelDisplacement)
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

			uint32 effectiveContentMaskDisplacement = (__MODULO((yOutputStart + (flattenTop? 0 : waveLutPixelDisplacement)), REFLECTIVE_ENTITY_Y_STEP_SIZE) << 1);
			uint32 effectiveContentMask = 0xFFFFFFFF << effectiveContentMaskDisplacement;
			uint32 effectiveBackgroundMask = ~effectiveContentMask;
			effectiveContentMask &= ~(topBorderMask << effectiveContentMaskDisplacement);

			REFLECTIVE_ENTITY_POINTER_TYPE* columnSourcePointerLeft = (REFLECTIVE_ENTITY_POINTER_TYPE*) (currentDrawingFrameBufferSet) + (xSource << REFLECTIVE_ENTITY_Y_SHIFT) + ySource;
			REFLECTIVE_ENTITY_POINTER_TYPE* columnSourcePointerRight = (REFLECTIVE_ENTITY_POINTER_TYPE*) (currentDrawingFrameBufferSet | 0x00010000) + (xSource << REFLECTIVE_ENTITY_Y_SHIFT) + ySource;
			REFLECTIVE_ENTITY_POINTER_TYPE* columnOutputPointerLeft = (REFLECTIVE_ENTITY_POINTER_TYPE*) (currentDrawingFrameBufferSet) + (leftColumn << REFLECTIVE_ENTITY_Y_SHIFT) + yOutput;
			REFLECTIVE_ENTITY_POINTER_TYPE* columnOutputPointerRight = (REFLECTIVE_ENTITY_POINTER_TYPE*) (currentDrawingFrameBufferSet | 0x00010000) + (rightColumn << REFLECTIVE_ENTITY_Y_SHIFT) + yOutput;

			int32 columnSourcePointerLeftIncrement = ySourceIncrement;
			int32 columnSourcePointerRightIncrement = ySourceIncrement;

			REFLECTIVE_ENTITY_POINTER_TYPE sourceCurrentValueLeft = *columnSourcePointerLeft;
			columnSourcePointerLeft += columnSourcePointerLeftIncrement;
			REFLECTIVE_ENTITY_POINTER_TYPE sourceNextValueLeft = *columnSourcePointerLeft;

			REFLECTIVE_ENTITY_POINTER_TYPE sourceCurrentValueRight = *columnSourcePointerRight;
			columnSourcePointerRight += columnSourcePointerRightIncrement;

			REFLECTIVE_ENTITY_POINTER_TYPE sourceNextValueRight = *columnSourcePointerRight;

			REFLECTIVE_ENTITY_POINTER_TYPE outputValueLeft = *columnOutputPointerLeft;
			REFLECTIVE_ENTITY_POINTER_TYPE outputValueRight = *columnOutputPointerRight;

			if(__Y_AXIS & axisForReversing)
			{
				sourceCurrentValueLeft = Utilities::reverse(sourceCurrentValueLeft, REFLECTIVE_ENTITY_BITS_PER_STEP);
				sourceCurrentValueRight = Utilities::reverse(sourceCurrentValueRight, REFLECTIVE_ENTITY_BITS_PER_STEP);
				sourceNextValueLeft = Utilities::reverse(sourceNextValueLeft, REFLECTIVE_ENTITY_BITS_PER_STEP);
				sourceNextValueRight = Utilities::reverse(sourceNextValueRight, REFLECTIVE_ENTITY_BITS_PER_STEP);
			}

			waveLutPixelDisplacement =  flattenBottom ? 0 : waveLutPixelDisplacement;

			int32 yOutputRemainder = __MODULO((yOutputEnd + waveLutPixelDisplacement), REFLECTIVE_ENTITY_Y_STEP_SIZE) << 1;
			int32 yOutputLimit = (yOutputEnd + waveLutPixelDisplacement) >> REFLECTIVE_ENTITY_Y_STEP_SIZE_2_EXP;

			REFLECTIVE_ENTITY_POINTER_TYPE remainderLeftValue = yOutput >= yOutputLimit ? sourceCurrentValueLeft : 0;
			REFLECTIVE_ENTITY_POINTER_TYPE remainderRightValue = yOutput >= yOutputLimit ? sourceCurrentValueRight : 0;

			uint32 noise = ReflectiveEntity::getNoise(noisePasses);

			for(; yOutput < yOutputLimit; yOutput++, ySource += ySourceIncrement)
			{
				ReflectiveEntity::shiftPixels(pixelShift, &sourceCurrentValueLeft, sourceNextValueLeft, &remainderLeftValue, reflectionMask, noise);
				ReflectiveEntity::shiftPixels(pixelShift, &sourceCurrentValueRight, sourceNextValueRight, &remainderRightValue, reflectionMask, noise);

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

				if(transparent)
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
					sourceNextValueLeft = Utilities::reverse(sourceNextValueLeft, REFLECTIVE_ENTITY_BITS_PER_STEP);
					sourceNextValueRight = Utilities::reverse(sourceNextValueRight, REFLECTIVE_ENTITY_BITS_PER_STEP);
				}
			}

			if(yOutputRemainder)
			{
				uint32 maskDisplacement = (REFLECTIVE_ENTITY_BITS_PER_STEP - yOutputRemainder);
				effectiveContentMask = 0xFFFFFFFF >> maskDisplacement;
				uint32 remainderContentMask = effectiveContentMask & ~(bottomBorderMask >> maskDisplacement);

				if(!transparent)
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
					remainderLeftValue |= (sourceNextValueLeft << (REFLECTIVE_ENTITY_BITS_PER_STEP + pixelShift));
					remainderRightValue |= (sourceNextValueRight << (REFLECTIVE_ENTITY_BITS_PER_STEP + pixelShift));
				}

				remainderLeftValue &= reflectionMask;
				remainderRightValue &= reflectionMask;

				remainderLeftValue |= transparentMask & outputValueLeft;
				remainderRightValue |= transparentMask & outputValueRight;

				uint32 finalLeftValue = (outputValueLeft & ~effectiveContentMask) | (((remainderLeftValue | noise) & remainderContentMask) & ~border);
				uint32 finalRightValue = (outputValueRight & ~effectiveContentMask) | (((remainderRightValue | noise) & remainderContentMask) & ~border);

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
			int32 yOutput = (yOutputStart + waveLutPixelDisplacement) >> REFLECTIVE_ENTITY_Y_STEP_SIZE_2_EXP;

			int32 pixelShift = (__MODULO((yOutputStart + waveLutPixelDisplacement), REFLECTIVE_ENTITY_Y_STEP_SIZE) - __MODULO(ySourceStart, REFLECTIVE_ENTITY_Y_STEP_SIZE)) << 1;

			reflectionMask = reflectionMaskSave;

			if(transparent && waveLutPixelDisplacement)
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

			uint32 effectiveContentMaskDisplacement = (__MODULO((yOutputStart + (flattenTop? 0 : waveLutPixelDisplacement)), REFLECTIVE_ENTITY_Y_STEP_SIZE) << 1);
			uint32 effectiveContentMask = 0xFFFFFFFF << effectiveContentMaskDisplacement;
			uint32 effectiveBackgroundMask = ~effectiveContentMask;
			effectiveContentMask &= ~(topBorderMask << effectiveContentMaskDisplacement);

			REFLECTIVE_ENTITY_POINTER_TYPE* columnSourcePointerLeft = (REFLECTIVE_ENTITY_POINTER_TYPE*) (currentDrawingFrameBufferSet) + (xSource << REFLECTIVE_ENTITY_Y_SHIFT) + ySource;
			REFLECTIVE_ENTITY_POINTER_TYPE* columnSourcePointerRight = (REFLECTIVE_ENTITY_POINTER_TYPE*) (currentDrawingFrameBufferSet | 0x00010000) + (xSource << REFLECTIVE_ENTITY_Y_SHIFT) + ySource;
			REFLECTIVE_ENTITY_POINTER_TYPE* columnOutputPointerLeft = (REFLECTIVE_ENTITY_POINTER_TYPE*) (currentDrawingFrameBufferSet) + (leftColumn << REFLECTIVE_ENTITY_Y_SHIFT) + yOutput;
			REFLECTIVE_ENTITY_POINTER_TYPE* columnOutputPointerRight = (REFLECTIVE_ENTITY_POINTER_TYPE*) (currentDrawingFrameBufferSet | 0x00010000) + (rightColumn << REFLECTIVE_ENTITY_Y_SHIFT) + yOutput;

			int32 columnSourcePointerLeftIncrement = ySourceIncrement;

			REFLECTIVE_ENTITY_POINTER_TYPE sourceCurrentValueLeft = *columnSourcePointerLeft;
			REFLECTIVE_ENTITY_POINTER_TYPE sourceCurrentValueRight = *columnSourcePointerRight;
			columnSourcePointerLeft += columnSourcePointerLeftIncrement;
			REFLECTIVE_ENTITY_POINTER_TYPE sourceNextValueLeft = *columnSourcePointerLeft;

			REFLECTIVE_ENTITY_POINTER_TYPE outputValueLeft = *columnOutputPointerLeft;
			REFLECTIVE_ENTITY_POINTER_TYPE outputValueRight = *columnOutputPointerRight;

			if(__Y_AXIS & axisForReversing)
			{
				sourceCurrentValueLeft = Utilities::reverse(sourceCurrentValueLeft, REFLECTIVE_ENTITY_BITS_PER_STEP);
				sourceNextValueLeft = Utilities::reverse(sourceNextValueLeft, REFLECTIVE_ENTITY_BITS_PER_STEP);
			}

			waveLutPixelDisplacement =  flattenBottom ? 0 : waveLutPixelDisplacement;

			int32 yOutputRemainder = __MODULO((yOutputEnd + waveLutPixelDisplacement), REFLECTIVE_ENTITY_Y_STEP_SIZE) << 1;

			int32 yOutputLimit = (yOutputEnd + waveLutPixelDisplacement) >> REFLECTIVE_ENTITY_Y_STEP_SIZE_2_EXP;

			REFLECTIVE_ENTITY_POINTER_TYPE remainderLeftValue = yOutput < yOutputLimit ? 0 : sourceCurrentValueLeft;

			uint32 noise = ReflectiveEntity::getNoise(noisePasses);

			for(; yOutput < yOutputLimit; yOutput++, ySource += ySourceIncrement)
			{
				ReflectiveEntity::shiftPixels(pixelShift, &sourceCurrentValueLeft, sourceNextValueLeft, &remainderLeftValue, reflectionMask, noise);

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

				if(transparent)
				{
					outputValueLeft = *columnOutputPointerLeft;
				}

				sourceCurrentValueLeft = sourceNextValueLeft;

				columnSourcePointerLeft += columnSourcePointerLeftIncrement;

				sourceNextValueLeft = *columnSourcePointerLeft;

				if(__Y_AXIS & axisForReversing)
				{
					sourceNextValueLeft = Utilities::reverse(sourceNextValueLeft, REFLECTIVE_ENTITY_BITS_PER_STEP);
				}
			}

			if(yOutputRemainder)
			{
				uint32 maskDisplacement = (REFLECTIVE_ENTITY_BITS_PER_STEP - yOutputRemainder);
				effectiveContentMask = 0xFFFFFFFF >> maskDisplacement;
				uint32 remainderContentMask = effectiveContentMask & ~(bottomBorderMask >> maskDisplacement);

				if(!transparent)
				{
					outputValueLeft = *columnOutputPointerLeft;
				}

				if(0 <= pixelShift)
				{
					remainderLeftValue |= (sourceCurrentValueLeft << pixelShift);
				}
				else
				{
					remainderLeftValue |= (sourceNextValueLeft << (REFLECTIVE_ENTITY_BITS_PER_STEP + pixelShift));
				}

				remainderLeftValue &= reflectionMask;
				remainderLeftValue |= transparentMask & outputValueLeft;

				uint32 finalLeftValue = (outputValueLeft & ~effectiveContentMask) | (((remainderLeftValue | noise) & remainderContentMask) & ~border);
				uint32 finalRightValue = (*columnOutputPointerRight & ~effectiveContentMask) | (((remainderLeftValue | noise) & remainderContentMask) & ~border);

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
