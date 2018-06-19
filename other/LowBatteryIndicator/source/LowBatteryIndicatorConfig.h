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
#ifndef LOW_BATTERY_INDICATOR_CONFIG_H_
#define LOW_BATTERY_INDICATOR_CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

// Position of low battery indicator
#ifndef __LOW_BATTERY_INDICATOR_POS_X
#define __LOW_BATTERY_INDICATOR_POS_X			45
#endif
#ifndef __LOW_BATTERY_INDICATOR_POS_Y
#define __LOW_BATTERY_INDICATOR_POS_Y			1
#endif

// Delay between showing/not showing the low battery indicator (in milliseconds)
#ifndef __LOW_BATTERY_INDICATOR_BLINK_INTERVAL
#define __LOW_BATTERY_INDICATOR_BLINK_INTERVAL	500
#endif

// Check for the PWR signal every X milliseconds
#ifndef __LOW_BATTERY_CHECK_INTERVAL
#define __LOW_BATTERY_CHECK_INTERVAL			1000
#endif


#endif
