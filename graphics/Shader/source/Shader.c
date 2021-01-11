/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Shader.h>
#include <Mem.h>
#include <Utilities.h>


friend class CharSet;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------


void Shader::constructor(const ShaderSpec* shaderSpec, Object owner)
{
	// construct base
	Base::constructor((BgmapSpriteSpec*)&shaderSpec->bgmapSpriteSpec, owner);
}

void Shader::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

u16 Shader::doRender(s16 index, bool evenFrame __attribute__((unused)))
{
	if(Base::doRender(this, index, evenFrame) == index)
	{
//		Shader::renderToTexture(this);
		return index;
	}

	return __NO_RENDER_INDEX;
}

//static u32 buffer[2][BYTES_PER_PIXELS(BUFFER_ROWS * BUFFER_COLS) / sizeof(u32)] __attribute__((section(".dram_bss")));

void Shader::renderToTexture()
{
	if(isDeleted(this->texture))
	{
		return;
	}

	CharSet charSet = Texture::getCharSet(this->texture, true);

	if(isDeleted(charSet))
	{
		return;
	}

	u16 numberOfChars = CharSet::getNumberOfChars(charSet);

	extern BYTE ShaderTiles[];

	Mem::copyWORD(
		(WORD*)(__CHAR_SPACE_BASE_ADDRESS + (((u32)charSet->offset) << 4)),
		(WORD*)(ShaderTiles),
		__BYTES_PER_CHARS(1) / sizeof(WORD)
	);

	PixelVector fromVertex2D = Vector3D::projectToPixelVector((Vector3D){__SCREEN_WIDTH_METERS >> 1, __SCREEN_HEIGHT_METERS >> 1, 0}, 0);

	static s16 angle = 0;
	angle = ++angle > 512 ? 0 : angle;

	fix10_6 sinAngle = __FIX7_9_TO_FIX10_6(__SIN(angle));
	fix10_6 cosAngle = __FIX7_9_TO_FIX10_6(__COS(angle));

	Vector3D toVector = 
	{
		__FIX10_6_MULT(__PIXELS_TO_METERS(64), cosAngle),
		__FIX10_6_MULT(__PIXELS_TO_METERS(64), sinAngle),
		0
	};


	PixelVector toVertex2D = Vector3D::projectToPixelVector(toVector, 0);

fromVertex2D.x = 0;
fromVertex2D.y = 0;
toVertex2D.x = 192;
toVertex2D.y = 112;


	Shader::drawLine(this, fromVertex2D, toVertex2D, __COLOR_BRIGHT_RED);

	
	/*
	HWORD newTile[__BYTES_PER_CHARS(1) / sizeof(HWORD)] = {0};

	for(u16 tile = 0; tile < limit; tile++)
	{
		// TODO: actually render 3D pixels
		for(u16 tileRow = 0; tileRow < __BYTES_PER_CHARS(1) / sizeof(HWORD); tileRow++)
		{
			newTile[tileRow] = Utilities::random(Utilities::randomSeed(), 1 << (15 - tileRow));
		}

		Mem::copyWORD(
			(WORD*)(__CHAR_SPACE_BASE_ADDRESS + ((((u32)charSet->offset) << 4) + (tile << 4))),
			(WORD*)newTile,
			__BYTES_PER_CHARS(1) / sizeof(WORD)
		);
	}
	*/
}

void Shader::drawPixel(u16 x, u16 y, int color)
{
	CharSet charSet = Texture::getCharSet(this->texture, true);

	int cols = Texture::getCols(this->texture);

	u16 col = x / 8;
	u16 row = y / 8;

	u16 tile = cols * row + col;  

//	tile = 0;

//	HWORD newTile[__BYTES_PER_CHARS(1) / sizeof(HWORD)] = {0x0F0F, 0, 0, 0x0F0F, 0, 0, 0x0F0F, 0};
//	HWORD newTile[__BYTES_PER_CHARS(1) / sizeof(HWORD)] = {0x0F0F, 0, 0, 0, 0, 0, 0, 0};
	HWORD newTile[__BYTES_PER_CHARS(1) / sizeof(HWORD)] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};

	// TODO: actually render 3D pixels
	for(u16 tileRow = 0; tileRow < __BYTES_PER_CHARS(1) / sizeof(HWORD); tileRow++)
	{
	//	newTile[tileRow] = *(HWORD*)(__CHAR_SPACE_BASE_ADDRESS + ((((u32)charSet->offset) << 4) + ((tile << 4) + tileRow)));
	//	newTile[tileRow] = 0x0F0F;
	}

	u16 limit = CharSet::getNumberOfChars(charSet);


	Mem::copyWORD(
		(WORD*)(__CHAR_SPACE_BASE_ADDRESS + ((((u32)charSet->offset) << 4) + (tile << 4))),
		(WORD*)newTile,
		__BYTES_PER_CHARS(1) / sizeof(WORD)
	);
}

void Shader::drawLine(PixelVector fromPoint, PixelVector toPoint, int color)
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

		Shader::drawPixel(this, (u16)__FIX19_13_TO_I(fromPointX - parallax), (u16)__FIX19_13_TO_I(fromPointY), color);

		fromPointX += stepX;
		fromPointY += stepY;
		auxParallax += parallaxStep;
	}
}