/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef ShaderSprite_SPRITE_H_
#define ShaderSprite_SPRITE_H_


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <BgmapSprite.h>


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

/// A ShaderSprite Spec
/// @memberof ShaderSprite
typedef struct ShaderSpriteSpec
{
	BgmapSpriteSpec bgmapSpriteSpec;

	/// Display side
	int32 shaderDisplaySide;

} ShaderSpriteSpec;

/// A ShaderSprite spec that is stored in ROM
/// @memberof ShaderSprite
typedef const ShaderSpriteSpec ShaderSpriteROMSpec;


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

///
/// Class Sprite
///
/// Inherits from VisualComponent
///
/// Displays a Texture on the screen.
class ShaderSprite : BgmapSprite
{
	/// @protectedsection

	/// CharSet to write into
	CharSet charSet;

	/// Frame buffer to use
	int32 buffer;

	/// @publicsection

	/// Class' constructor
	/// @param owner: GameObject to which the sprite attaches to
	/// @param shaderSpriteSpec: Specification that determines how to configure the sprite
	void constructor(GameObject owner, const ShaderSpriteSpec* shaderSpriteSpec);

	/// Render the sprite by configuring the DRAM assigned to it by means of the provided index.
	/// @param index: Determines the region of DRAM that this sprite is allowed to configure
	/// @return The index that determines the region of DRAM that this sprite manages
	override int16 doRender(int16 index);

	/// Check if the sprite has special effects.
	/// @return True if the sprite has special effects
	override bool hasSpecialEffects();

	/// Process special effects.
	override void processEffects();
}


#endif
