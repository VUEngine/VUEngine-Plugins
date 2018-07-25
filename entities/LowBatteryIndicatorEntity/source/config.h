/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LOW_BATTERY_INDICATOR_ENTITY_CONFIG_H_
#define LOW_BATTERY_INDICATOR_ENTITY_CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//											ESSENTIAL MACROS
//---------------------------------------------------------------------------------------------------------

#define __LOW_BATTERY_INDICATOR_ENTITY_ENABLED


//---------------------------------------------------------------------------------------------------------
//											CONFIGURATION MACROS
//---------------------------------------------------------------------------------------------------------

// show low battery indicator after this many seconds of receiving the low power signal
#ifndef __LOW_BATTERY_INDICATOR_ENTITY_BLINK_DELAY
#define __LOW_BATTERY_INDICATOR_ENTITY_BLINK_DELAY		3
#endif

#ifndef	__LOW_BATTERY_INDICATOR_ENTITY_X_POSITION
#define __LOW_BATTERY_INDICATOR_ENTITY_X_POSITION		16
#endif

#ifndef	__LOW_BATTERY_INDICATOR_ENTITY_Y_POSITION
#define __LOW_BATTERY_INDICATOR_ENTITY_Y_POSITION		12
#endif

#ifndef	__LOW_BATTERY_INDICATOR_ENTITY_Z_POSITION
#define __LOW_BATTERY_INDICATOR_ENTITY_Z_POSITION		0
#endif

#ifndef	__LOW_BATTERY_INDICATOR_ENTITY_Z_DISPLACEMENT
#define __LOW_BATTERY_INDICATOR_ENTITY_Z_DISPLACEMENT	0
#endif


#endif
