/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef __PLUGIN_LANGUAGE_SELECTION_SCREEN_CONFIG_H_
#define __PLUGIN_LANGUAGE_SELECTION_SCREEN_CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//											CONFIGURATION MACROS
//---------------------------------------------------------------------------------------------------------

// lang select screen variant to use (0: simple list, 1: flags)
#ifndef __PLUGIN_LANGUAGE_SELECTION_SCREEN_VARIANT
#define __PLUGIN_LANGUAGE_SELECTION_SCREEN_VARIANT				    0
#endif

#ifndef __PLUGIN_LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT
#define __PLUGIN_LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT 			NULL
#endif

#ifndef __PLUGIN_LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT
#define __PLUGIN_LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT  		NULL
#endif

#ifndef __PLUGIN_LANGUAGE_SELECTION_SCREEN_IMAGE_WIDTH
#define __PLUGIN_LANGUAGE_SELECTION_SCREEN_IMAGE_WIDTH 				(5 * 8) + 4
#endif

#ifndef __PLUGIN_LANGUAGE_SELECTION_SCREEN_IMAGE_HEIGHT
#define __PLUGIN_LANGUAGE_SELECTION_SCREEN_IMAGE_HEIGHT    			(4 * 8)
#endif

#ifndef __PLUGIN_LANGUAGE_SELECTION_SCREEN_USE_LOW_POWER_ENTITY
#define __PLUGIN_LANGUAGE_SELECTION_SCREEN_USE_LOW_POWER_ENTITY		false
#endif



#endif
