/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef SAVE_DATA_MANAGER_CONFIG_H_
#define SAVE_DATA_MANAGER_CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//											CONFIGURATION MACROS
//---------------------------------------------------------------------------------------------------------


#ifndef	__SAVE_DATA_MANAGER_CRC_MASK
#define __SAVE_DATA_MANAGER_CRC_MASK				0xEDB88320
#endif

#ifndef	__SAVE_DATA_MANAGER_SAVE_STAMP
#define __SAVE_DATA_MANAGER_SAVE_STAMP				"VUEngine"
#endif

#ifndef __SAVE_DATA_MANAGER_CRC_CHECK_RANGE
#define __SAVE_DATA_MANAGER_CRC_CHECK_RANGE			512
#endif

#ifndef __SAVE_DATA_MANAGER_SAVE_STAMP_LENGTH
#define __SAVE_DATA_MANAGER_SAVE_STAMP_LENGTH		8
#endif


#endif
