/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef __PLUGIN_SAVE_DATA_MANAGER_CONFIG_H_
#define __PLUGIN_SAVE_DATA_MANAGER_CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//											CONFIGURATION MACROS
//---------------------------------------------------------------------------------------------------------

#ifndef	__PLUGIN_SAVE_DATA_MANAGER_CRC_MASK
#define __PLUGIN_SAVE_DATA_MANAGER_CRC_MASK					(0xEDB88320)
#endif

#ifndef __PLUGIN_SAVE_DATA_MANAGER_CRC_CHECK_RANGE
#define __PLUGIN_SAVE_DATA_MANAGER_CRC_CHECK_RANGE			(512)
#endif

#ifndef	__PLUGIN_SAVE_DATA_MANAGER_SAVE_STAMP
#define __PLUGIN_SAVE_DATA_MANAGER_SAVE_STAMP				("VUEngine")
#endif

#ifndef __PLUGIN_SAVE_DATA_MANAGER_SAVE_STAMP_LENGTH
#define __PLUGIN_SAVE_DATA_MANAGER_SAVE_STAMP_LENGTH		(8)
#endif


#endif
