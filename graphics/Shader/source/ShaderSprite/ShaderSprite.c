/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Mem.h>
#include <Utilities.h>

#include "ShaderSprite.h"


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

friend class CharSet;


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' MACROS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

#define CHARS_PER_BUFFER (__CHAR_MEMORY_TOTAL_CHARS / 2)


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void ShaderSprite::constructor(GameObject owner, const ShaderSpriteSpec* shaderSpriteSpec)
{
	// construct base
	// Always explicitly call the base's constructor 
	Base::constructor(owner, &shaderSpriteSpec->bgmapSpriteSpec);

	this->buffer = shaderSpriteSpec->shaderDisplaySide;
	this->charSet = NULL;

	if(!isDeleted(this->texture))
	{
		this->charSet = Texture::getCharSet(this->texture, true);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void ShaderSprite::destructor()
{
	this->charSet = NULL;

	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

int16 ShaderSprite::doRender(int16 index)
{
	if(Base::doRender(this, index) == index)
	{
//		ShaderSprite::renderToTexture(this, (WORD*)(buffer[this->buffer]));
		return index;
	}

	return __NO_RENDER_INDEX;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

bool ShaderSprite::hasSpecialEffects()
{
	return true;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void ShaderSprite::processEffects()
{
	if(isDeleted(this->charSet))
	{
		return;
	}

	ShaderSprite::renderToTexture(this, (WORD*)(__CHAR_SPACE_BASE_ADDRESS + (((uint32)this->charSet->offset) << 4)));
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void ShaderSprite::copyBufferTo(WORD* bufferAddress, WORD* destinationAddress)
{
	Mem::copyWORD(
		destinationAddress,
		bufferAddress,
		__BYTES_PER_CHARS(CharSet::getNumberOfChars(this->charSet)) / sizeof(WORD)
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// TODO: Should use the Mem::copyWORD, but this is way faster on hardware somehow
static void ShaderSprite::addWORD(WORD* destination, const WORD* source, uint32 numberOfWORDS, uint32 increment)
{
	for(; 0 < numberOfWORDS; numberOfWORDS--)
	{
		*destination++ = *source++ + increment;
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void ShaderSprite::clear(WORD* destinationAddress)
{
	extern uint32 ShaderTiles[];

	ShaderSprite::addWORD(
		destinationAddress,
		(WORD*)(ShaderTiles),
		__BYTES_PER_CHARS(CharSet::getNumberOfChars(this->charSet)) / sizeof(WORD),
		0
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void ShaderSprite::drawRandom(WORD* destinationAddress)
{
	extern uint32 ShaderTiles[];

	static int32 increment = 0;
	increment++;

	ShaderSprite::addWORD(
		destinationAddress,
		(WORD*)(ShaderTiles),
		__BYTES_PER_CHARS(CharSet::getNumberOfChars(this->charSet)) / sizeof(WORD),
		increment
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void ShaderSprite::renderToTexture(WORD* bufferAddress)
{
	if(isDeleted(this->charSet))
	{
		return;
	}

	ShaderSprite::clear(this, bufferAddress);
	ShaderSprite::drawRandom(this, bufferAddress);

	for(int32 i = 0; i < 12; i++)
	{
		ShaderSprite::renderClock(this, bufferAddress);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void ShaderSprite::renderClock(WORD* bufferAddress)
{
	Vector3D fromVector = 
	{
		__SCREEN_WIDTH_METERS >> 1,
		__SCREEN_HEIGHT_METERS >> 1,
		0
	};

	static int16 angle = 0;
	angle = angle > 512 ? 0 : angle;
	angle += 4;

	fixed_t sinAngle = __FIX7_9_TO_FIXED(__SIN(angle));
	fixed_t cosAngle = __FIX7_9_TO_FIXED(__COS(angle));

	Vector3D toVector = 
	{
		fromVector.x + __FIXED_MULT(__PIXELS_TO_METERS(64), cosAngle),
		fromVector.y + __FIXED_MULT(__PIXELS_TO_METERS(64), sinAngle),
		0
	};

	PixelVector fromVertex2D = PixelVector::projectVector3D(fromVector, 0);
	PixelVector toVertex2D = PixelVector::projectVector3D(toVector, 0);

	ShaderSprite::drawLine(this, bufferAddress, fromVertex2D, toVertex2D, __COLOR_BRIGHT_RED);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void ShaderSprite::drawPixel(WORD* bufferAddress, uint16 x, uint16 y, int32 color)
{
	int32 cols = Texture::getCols(this->texture);

	uint16 col = x >> 3;
	uint16 row = y >> 3;

	uint16 tile = cols * row + col;  

//	tile = 0;

//	HWORD newTile[__BYTES_PER_CHARS(1) / sizeof(HWORD)] = {0x0F0F, 0, 0, 0x0F0F, 0, 0, 0x0F0F, 0};
//	HWORD newTile[__BYTES_PER_CHARS(1) / sizeof(HWORD)] = {0x0F0F, 0, 0, 0, 0, 0, 0, 0};
	static HWORD newTile[__BYTES_PER_CHARS(1) / sizeof(HWORD)] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};

	// TODO: actually render 3D pixels
//	for(uint16 tileRow = 0; tileRow < __BYTES_PER_CHARS(1) / sizeof(HWORD); tileRow++)
	{
	//	newTile[tileRow] = *(HWORD*)(__CHAR_SPACE_BASE_ADDRESS + ((((uint32)charSet->offset) << 4) + ((tile << 4) + tileRow)));
	//	newTile[tileRow] = 0x0F0F;
	}

	Mem::copyWORD(
		(WORD*)(bufferAddress + (tile << 2)),
		(WORD*)newTile,
		__BYTES_PER_CHARS(1) / sizeof(WORD)
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void ShaderSprite::drawLine(WORD* bufferAddress, PixelVector fromPoint, PixelVector toPoint, int32 color)
{
	fix19_13 fromPointX = __I_TO_FIX19_13(fromPoint.x);
	fix19_13 fromPointY = __I_TO_FIX19_13(fromPoint.y);

	fix19_13 toPointX = __I_TO_FIX19_13(toPoint.x);
	fix19_13 toPointY = __I_TO_FIX19_13(toPoint.y);

	fix19_13 dx = __ABS(toPointX - fromPointX);
	fix19_13 dy = __ABS(toPointY - fromPointY);

	if(0 == dx && 0 == dy)
	{
		return;
	}

	fix19_13 stepX = dx ? __I_TO_FIX19_13(1) : 0;
	fix19_13 stepY = dy ? __I_TO_FIX19_13(1) : 0;
	fix19_13 parallax = __I_TO_FIX19_13(fromPoint.parallax);
	fix19_13 parallaxDelta = __I_TO_FIX19_13(toPoint.parallax - fromPoint.parallax);

	fix19_13* fromCoordinate = NULL;
	fix19_13* toCoordinate = NULL;
	fix19_13 parallaxStep = 0;

	if(dy == dx || dy < dx || 0 == dy)
	{
		fromCoordinate = &fromPointX;
		toCoordinate = &toPointX;

		stepX = __I_TO_FIX19_13(1);
		stepY = __FIXED_TO_FIX19_13(__FIXED_DIV(__FIX19_13_TO_FIXED(dy), __FIX19_13_TO_FIXED(dx)));

		if(toPointX < fromPointX)
		{
			fix19_13 aux = toPointX;
			toPointX = fromPointX;
			fromPointX = aux;

			aux = toPointY;
			toPointY = fromPointY;
			fromPointY = aux;
		}

		if(toPointY < fromPointY)
		{
			stepY = -stepY;
		}

		parallaxStep = __FIXED_TO_FIX19_13(__FIXED_DIV(__FIX19_13_TO_FIXED(parallaxDelta), __FIX19_13_TO_FIXED(dx)));
	}
	else if(dx < dy || 0 == dx)
	{
		fromCoordinate = &fromPointY;
		toCoordinate = &toPointY;

		// make sure that no software based divisions is introduced
		stepX = __FIXED_TO_FIX19_13(__FIXED_DIV(__FIX19_13_TO_FIXED(dx), __FIX19_13_TO_FIXED(dy)));
		stepY = __I_TO_FIX19_13(1);

		if(toPointY < fromPointY)
		{
			fix19_13 aux = toPointX;
			toPointX = fromPointX;
			fromPointX = aux;

			aux = toPointY;
			toPointY = fromPointY;
			fromPointY = aux;
		}

		if(toPointX < fromPointX)
		{
			stepX = -stepX;
		}

		parallaxStep = __FIXED_TO_FIX19_13(__FIXED_DIV(__FIX19_13_TO_FIXED(parallaxDelta), __FIX19_13_TO_FIXED(dy)));
	}

	fix19_13 auxParallax = parallax;

	while(*fromCoordinate <= *toCoordinate)
	{
		parallax = auxParallax;

		ShaderSprite::drawPixel(this, bufferAddress, (uint16)__FIX19_13_TO_I(fromPointX - parallax), (uint16)__FIX19_13_TO_I(fromPointY), color);

		fromPointX += stepX;
		fromPointY += stepY;
		auxParallax += parallaxStep;
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

