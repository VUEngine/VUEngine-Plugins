/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef __PLUGIN_LOW_POWER_ENTITY_CONFIG_H_
#define __PLUGIN_LOW_POWER_ENTITY_CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//											CONFIGURATION MACROS
//---------------------------------------------------------------------------------------------------------

#ifndef __PLUGIN_LOW_POWER_ENTITY_USE_GUI_BGMAP_ANIMATED_SPRITE
#define __PLUGIN_LOW_POWER_ENTITY_USE_GUI_BGMAP_ANIMATED_SPRITE		(0)
#endif

#ifndef	__PLUGIN_LOW_POWER_ENTITY_X_POSITION
	#ifdef __LEGACY_COORDINATE_PROJECTION
		#define __PLUGIN_LOW_POWER_ENTITY_X_POSITION				(16)
	#else
		#define __PLUGIN_LOW_POWER_ENTITY_X_POSITION				(-176)
	#endif
#endif

#ifndef	__PLUGIN_LOW_POWER_ENTITY_Y_POSITION
	#ifdef __LEGACY_COORDINATE_PROJECTION
		#define __PLUGIN_LOW_POWER_ENTITY_Y_POSITION				(12)
	#else
		#define __PLUGIN_LOW_POWER_ENTITY_Y_POSITION				(-100)
	#endif
#endif

#ifndef	__PLUGIN_LOW_POWER_ENTITY_Z_POSITION
#define __PLUGIN_LOW_POWER_ENTITY_Z_POSITION						(0)
#endif

#ifndef	__PLUGIN_LOW_POWER_ENTITY_Z_DISPLACEMENT
#define __PLUGIN_LOW_POWER_ENTITY_Z_DISPLACEMENT					(0)
#endif


#endif
