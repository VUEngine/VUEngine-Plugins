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

#ifndef __AUTOMATIC_PAUSE_MANAGER_ENABLED
#define __AUTOMATIC_PAUSE_MANAGER_ENABLED
#endif


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
	// auto pause active flag
	bool isActive;
	// after this many minutes the auto pause kicks in
	u8 autoPauseDelay;
	// minutes elapsed since last automatic pause
	u8 elapsedTime;


	/// @publicsection

	/**
	 * Get instance.
	 *
	 * @return	AutoPauseManager instance
	 */
	static AutoPauseManager getInstance();

	GameState getAutomaticPauseState();
	void setAutomaticPauseState(GameState automaticPauseState);
	void setAutomaticPauseDelay(u8 automaticPauseDelay);
	bool isActive();

	/**
     * De/activate
     *
     * @param active	Set as active or inactive?
     */
    void setActive(bool active);


	/// @privatesection
}


#endif
