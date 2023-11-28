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

#include <GuiBgmapAnimatedSprite.h>
#include <BgmapTexture.h>
#include <VirtualList.h>
#include <VirtualNode.h>
#include <VIPManager.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void GuiBgmapAnimatedSprite::constructor(const GuiBgmapAnimatedSpriteSpec* guiBgmapAnimatedSpriteSpec, ListenerObject owner)
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

int16 GuiBgmapAnimatedSprite::doRender(int16 index, bool evenFrame)
{
	NM_ASSERT(!isDeleted(this->texture), "GuiBgmapAnimatedSprite::doRender: null texture");

	int16 result = Base::doRender(this, index, evenFrame);

	if(__NO_RENDER_INDEX == result)
	{
		return __NO_RENDER_INDEX;
	}

	WorldAttributes* worldPointer = &_worldAttributesCache[index];

	// set the head
	worldPointer->head = this->head | BgmapTexture::getSegment(this->texture);

	// get coordinates
	worldPointer->gx = this->position.x + this->displacement.x - this->halfWidth;
	worldPointer->gy = this->position.y + this->displacement.y - this->halfHeight;
	worldPointer->gp = this->position.parallax + this->displacement.parallax;

	worldPointer->mx = this->bgmapTextureSource.mx;
	worldPointer->my = this->bgmapTextureSource.my;
	worldPointer->mp = this->bgmapTextureSource.mp;

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

	return result;
}
