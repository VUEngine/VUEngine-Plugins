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

#ifndef AUTOMATIC_PAUSE_MANAGER_H_
#define AUTOMATIC_PAUSE_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Object.h>
#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

// Amount of time after which to show auto pause (in milliseconds)
#define __AUTO_PAUSE_DELAY						3000
//#define __AUTO_PAUSE_DELAY						(30 * 60 * 1000)

// The automatic pause state is not pushed until there is only one state in the game's stack.
// The following defines the time between checks whether the condition is met (in milliseconds)
#define __AUTO_PAUSE_RECHECK_DELAY				(30 * 1000)


//---------------------------------------------------------------------------------------------------------
//												ENUMS
//---------------------------------------------------------------------------------------------------------

/**
 * Automatic Pause Manager messages
 *
 * @memberof AutoPauseManager
 */
enum AutoPauseManagerMessages
{
	kAutoPause = 0,
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/**
 * Shows an indicator on screen when the system power is low
 *
 * @ingroup vuengine-components-other
 */
singleton class AutoPauseManager : Object
{
	/// @protectedsection

	// auto pause state
	GameState automaticPauseState;
	// auto pause last checked time
	u32 lastAutoPauseCheckTime;


	/// @publicsection

	/**
	 * Get instance.
	 *
	 * @return	AutoPauseManager instance
	 */
	static AutoPauseManager getInstance();

	GameState getAutomaticPauseState();
	void setAutomaticPauseState(GameState automaticPauseState);
	override bool handleMessage(Telegram telegram);


	/// @privatesection
}


#endif
