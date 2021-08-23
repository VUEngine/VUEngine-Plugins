/*
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef ShaderSprite_SPRITE_H_
#define ShaderSprite_SPRITE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <BgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

enum ShaderSide
{
	kShaderSideLeft = 0,
	kShaderSideRight
};

/**
 * Spec of a ShaderSprite
 *
 * @memberof 	ShaderSprite
 */
typedef struct ShaderSpriteSpec
{
	/// entity spec
	BgmapSpriteSpec bgmapSpriteSpec;

	/// display side
	int shaderDisplaySide;

} ShaderSpriteSpec;

/**
 * A ShaderSpriteSpec that is stored in ROM
 *
 * @memberof 	ShaderSprite
 */
typedef const ShaderSpriteSpec ShaderSpriteROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------


class ShaderSprite : BgmapSprite
{
	CharSet charSet;
	int buffer;

	/// @publicsection
	void constructor(const ShaderSpriteSpec* shaderSpriteSpec, Object owner);

	override u16 doRender(s16 index, bool evenFrame);
	override void processEffects();
	override bool hasSpecialEffects();
}


#endif
