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

#include <ShaderSprite.h>
#include <Mem.h>
#include <Utilities.h>


friend class CharSet;

#define CHARS_PER_BUFFER (__CHAR_MEMORY_TOTAL_CHARS / 2)


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------


void ShaderSprite::constructor(const ShaderSpriteSpec* shaderSpriteSpec, Object owner)
{
	// construct base
	Base::constructor((BgmapSpriteSpec*)&shaderSpriteSpec->bgmapSpriteSpec, owner);

	this->buffer = shaderSpriteSpec->shaderDisplaySide;
	this->charSet = NULL;

	if(!isDeleted(this->texture))
	{
		this->charSet = Texture::getCharSet(this->texture, true);
	}
}

void ShaderSprite::destructor()
{
	this->charSet = NULL;

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}


bool ShaderSprite::hasSpecialEffects()
{
	return true;
}

int16 ShaderSprite::doRender(int16 index, bool evenFrame __attribute__((unused)))
{
	if(Base::doRender(this, index, evenFrame) == index)
	{
//		ShaderSprite::renderToTexture(this, (WORD*)(buffer[this->buffer]));
		return index;
	}

	return __NO_RENDER_INDEX;
}


void ShaderSprite::processEffects()
{
	if(isDeleted(this->charSet))
	{
		return;
	}

	ShaderSprite::renderToTexture(this, (WORD*)(__CHAR_SPACE_BASE_ADDRESS + (((uint32)this->charSet->offset) << 4)));
}

void ShaderSprite::copyBufferTo(WORD* bufferAddress, WORD* destinationAddress)
{
	Mem::copyWORD(
		destinationAddress,
		bufferAddress,
		__BYTES_PER_CHARS(CharSet::getNumberOfChars(this->charSet)) / sizeof(WORD)
	);
}

// TODO: Should use the Mem::copyWORD, but this is way faster on hardware somehow
static void ShaderSprite::addWORD(WORD* destination, const WORD* source, uint32 numberOfWORDS, uint32 increment)
{
	for(; 0 < numberOfWORDS; numberOfWORDS--)
	{
		*destination++ = *source++ + increment;
	}
}

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

const int32 pad[8192*8*4] = {0};

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

	fix10_6 sinAngle = __FIX7_9_TO_FIX10_6(__SIN(angle));
	fix10_6 cosAngle = __FIX7_9_TO_FIX10_6(__COS(angle));

	Vector3D toVector = 
	{
		fromVector.x + __FIX10_6_MULT(__PIXELS_TO_METERS(64), cosAngle),
		fromVector.y + __FIX10_6_MULT(__PIXELS_TO_METERS(64), sinAngle),
		0
	};

	PixelVector fromVertex2D = Vector3D::projectToPixelVector(fromVector, 0);
	PixelVector toVertex2D = Vector3D::projectToPixelVector(toVector, 0);

	ShaderSprite::drawLine(this, bufferAddress, fromVertex2D, toVertex2D, __COLOR_BRIGHT_RED);
}

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
		stepY = __FIX10_6_TO_FIX19_13(__FIX10_6_DIV(__FIX19_13_TO_FIX10_6(dy), __FIX19_13_TO_FIX10_6(dx)));

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

		parallaxStep = __FIX10_6_TO_FIX19_13(__FIX10_6_DIV(__FIX19_13_TO_FIX10_6(parallaxDelta), __FIX19_13_TO_FIX10_6(dx)));
	}
	else if(dx < dy || 0 == dx)
	{
		fromCoordinate = &fromPointY;
		toCoordinate = &toPointY;

		// make sure that no software based divisions is introduced
		stepX = __FIX10_6_TO_FIX19_13(__FIX10_6_DIV(__FIX19_13_TO_FIX10_6(dx), __FIX19_13_TO_FIX10_6(dy)));
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

		parallaxStep = __FIX10_6_TO_FIX19_13(__FIX10_6_DIV(__FIX19_13_TO_FIX10_6(parallaxDelta), __FIX19_13_TO_FIX10_6(dy)));
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