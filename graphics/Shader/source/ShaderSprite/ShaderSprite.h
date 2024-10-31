/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
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
	int32 shaderDisplaySide;

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
	int32 buffer;

	/// @publicsection
	void constructor(SpatialObject owner, const ShaderSpriteSpec* shaderSpriteSpec);

	/// Render the sprite by configuring the DRAM assigned to it by means of the provided index.
	/// @param index: Determines the region of DRAM that this sprite is allowed to configure
	/// @return The index that determines the region of DRAM that this sprite configured
	override int16 doRender(int16 index);
	override void processEffects();
	override bool hasSpecialEffects();
}


#endif
