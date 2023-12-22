/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef POST_PROCESSING_RAIN_CONFIG_H_
#define POST_PROCESSING_RAIN_CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//											CONFIGURATION MACROS
//---------------------------------------------------------------------------------------------------------

#ifndef __WATERFALL_X_POSITION
#define __WATERFALL_X_POSITION								(__HALF_SCREEN_WIDTH_METERS)
#endif

#ifndef __WATERFALL_Y_POSITION
#define __WATERFALL_Y_POSITION								(__HALF_SCREEN_HEIGHT_METERS)
#endif

#ifndef __WATERFALL_WIDTH
#define __WATERFALL_WIDTH									(200)
#endif

#ifndef __WATERFALL_HEIGHT
#define __WATERFALL_HEIGHT									(100)
#endif

#ifndef __WATERFALL_Y_STEP_THROTTLE
#define __WATERFALL_Y_STEP_THROTTLE							(0)
#endif


#endif

