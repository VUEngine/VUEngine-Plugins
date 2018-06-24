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
#ifndef SPLASH_SCREENS_CONFIG_H_
#define SPLASH_SCREENS_CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

// ADJUSTMENT SCREEN

// adjustment screen variant to use (0: VUEngine, 1: Planet Virtual Boy, 2: Nintendo or 3: Prototype)
#ifndef __ADJUSTMENT_SCREEN_VARIANT
#define __ADJUSTMENT_SCREEN_VARIANT								0
#endif

// AUTO PAUSE SELECT SCREEN

#ifndef __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_GAP
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_GAP			3
#endif

#ifndef __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS		15
#endif

#ifndef __AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT			"AUTOMATIC PAUSE"
#endif

#ifndef __AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT_FONT
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT_FONT		NULL
#endif

#ifndef __AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT			"The Automatic Pause feature will\nremind you to take a break from\nplaying approx. every 30 minutes"
#endif

#ifndef __AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT_FONT
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT_FONT		NULL
#endif

#ifndef __AUTOMATIC_PAUSE_SELECTION_SCREEN_ON_TEXT
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_ON_TEXT				"On"
#endif

#ifndef __AUTOMATIC_PAUSE_SELECTION_SCREEN_OFF_TEXT
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_OFF_TEXT				"Off"
#endif

#ifndef __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT
#define __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT	NULL
#endif

// LANGUAGE SELECTION SCREEN

#ifndef __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT
#define __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT					"LANGUAGE SELECT"
#endif

#ifndef __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT
#define __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT				NULL
#endif

#ifndef __LANGUAGE_SELECTION_SCREEN_OPTIONS_FONT
#define __LANGUAGE_SELECTION_SCREEN_OPTIONS_FONT				NULL
#endif

// PRECAUTION SCREEN

#ifndef __PRECAUTION_SCREEN_TEXT
#define __PRECAUTION_SCREEN_TEXT								"     IMPORTANT\n\nREAD INSTRUCTION AND\n\nPRECAUTION BOOKLETS\n\n  BEFORE OPERATING"
#endif

#ifndef __PRECAUTION_SCREEN_TEXT_FONT
#define __PRECAUTION_SCREEN_TEXT_FONT							NULL
#endif


#endif
