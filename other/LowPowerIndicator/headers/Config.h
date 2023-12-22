/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LOW_POWER_INDICATOR_CONFIG_H_
#define LOW_POWER_INDICATOR_CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//											CONFIGURATION MACROS
//---------------------------------------------------------------------------------------------------------

// show low power indicator after this many seconds of receiving the low power signal
#ifndef __LOW_POWER_INDICATOR_FLASH_DELAY
#define __LOW_POWER_INDICATOR_FLASH_DELAY			2
#endif

#ifndef __LOW_POWER_INDICATOR_FONT
#define __LOW_POWER_INDICATOR_FONT					NULL
#endif

#ifndef	__LOW_POWER_INDICATOR_ON_TEXT
#define __LOW_POWER_INDICATOR_ON_TEXT				"\x01\x02"
#endif

#ifndef	__LOW_POWER_INDICATOR_OFF_TEXT
#define __LOW_POWER_INDICATOR_OFF_TEXT				"  "
#endif

#ifndef	__LOW_POWER_INDICATOR_X_POSITION
#define __LOW_POWER_INDICATOR_X_POSITION			1
#endif

#ifndef	__LOW_POWER_INDICATOR_Y_POSITION
#define __LOW_POWER_INDICATOR_Y_POSITION			1
#endif


#endif
