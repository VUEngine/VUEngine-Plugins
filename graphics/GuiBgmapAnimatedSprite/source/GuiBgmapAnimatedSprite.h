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

#ifndef GUI_BGMAP_ANIMATED_SPRITE_H_
#define GUI_BGMAP_ANIMATED_SPRITE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <BgmapAnimatedSprite.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------


/**
 * A BgmapAnimatedSprite spec
 *
 * @memberof BgmapAnimatedSprite
 */
typedef struct GuiBgmapAnimatedSpriteSpec
{
	/// it has a Sprite spec at the beginning
	BgmapAnimatedSpriteSpec bgmapAnimatedSpriteSpec;

} GuiBgmapAnimatedSpriteSpec;

/**
 * A BgmapAnimatedSprite spec that is stored in ROM
 *
 * @memberof BgmapAnimatedSprite
 */
typedef const GuiBgmapAnimatedSpriteSpec GuiBgmapAnimatedSpriteROMSpec;

/**
 * Manages printing layer and offers various functions to write to it.
 */
class GuiBgmapAnimatedSprite : BgmapAnimatedSprite
{
	/// @publicsection

	/**
	 * Class constructor
	 *
	 * @param guiBgmapAnimatedSpriteSpec		Sprite spec
	 * @param owner						Owner
	 */
	void constructor(const GuiBgmapAnimatedSpriteSpec* guiBgmapAnimatedSpriteSpec, Object owner);

	/**
     * Class destructor
     */
    void destructor();

	/**
     * Render
     *
     * @param evenFrame
     */
	override u16 doRender(s16 index, bool evenFrame);
}


#endif
