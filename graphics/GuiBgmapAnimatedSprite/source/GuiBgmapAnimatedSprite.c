/* VUEngine - Virtual Utopia Engine <https://www.vuengine.dev>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>, 2007-2020
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

#include <GuiBgmapAnimatedSprite.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void GuiBgmapAnimatedSprite::constructor(const GuiBgmapAnimatedSpriteSpec* guiBgmapAnimatedSpriteSpec, Object owner)
{
	// construct base object
	Base::constructor(&guiBgmapAnimatedSpriteSpec->bgmapAnimatedSpriteSpec, owner);
}

void GuiBgmapAnimatedSprite::destructor()
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void GuiBgmapAnimatedSprite::render()
{
	Base::render(this);

	if(!this->positioned)
	{
		return;
	}

	if(!this->worldLayer)
	{
		return;
	}

	static WorldAttributes* worldPointer = NULL;
	worldPointer = &_worldAttributesBaseAddress[this->worldLayer];

	// set the head
	worldPointer->head = this->head | BgmapTexture::getSegment(this->texture);

	// get coordinates
	worldPointer->gx = this->position.x + this->displacement.x - this->halfWidth;
	worldPointer->gy = this->position.y + this->displacement.y - this->halfHeight;
	worldPointer->gp = this->position.parallax + this->displacement.parallax;

	worldPointer->mx = this->drawSpec.textureSource.mx;
	worldPointer->my = this->drawSpec.textureSource.my;
	worldPointer->mp = this->drawSpec.textureSource.mp;

	worldPointer->w = this->halfWidth << 1;
	worldPointer->h = this->halfHeight << 1;

	if(0 < worldPointer->w)
	{
		worldPointer->w -= __WORLD_SIZE_DISPLACEMENT;
	}

	if(0 < worldPointer->h)
	{
		worldPointer->h -= __WORLD_SIZE_DISPLACEMENT;
	}
}
