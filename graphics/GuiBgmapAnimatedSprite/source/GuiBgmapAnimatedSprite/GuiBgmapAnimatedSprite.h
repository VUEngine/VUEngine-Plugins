/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
	void constructor(SpatialObject owner, const GuiBgmapAnimatedSpriteSpec* guiBgmapAnimatedSpriteSpec);

	/**
     * Class destructor
     */
    void destructor();

	/**
     * Render
     *
     * @param index
     */
	override int16 doRender(int16 index);
}


#endif
