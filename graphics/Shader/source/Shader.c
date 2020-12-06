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
		Shader::renderToTexture(this);
		return index;
	}

	return __NO_RENDER_INDEX;
}

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

	int cols = Texture::getCols(this->texture);
	int rows = Texture::getRows(this->texture);

	u16 limit = CharSet::getNumberOfChars(charSet);
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
}
