/* VUEngine - Virtual Utopia Engine <https://www.vuengine.dev>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>, 2007-2020
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
