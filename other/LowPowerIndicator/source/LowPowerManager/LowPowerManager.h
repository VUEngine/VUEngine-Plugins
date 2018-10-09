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

#ifndef LOW_POWER_MANAGER_H_
#define LOW_POWER_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Object.h>
#include "../config.h"


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/**
 * Shows an indicator on screen when the system power is low
 *
 * @ingroup vuengine-plugins-other
 */
singleton class LowPowerManager : Object
{
	/// @protectedsection

	// low power indicator active flag
	bool isActive;
	// low power indicator showing flag
	bool isShowingIndicator;
	// x position of the low power indicator
	u8 indicatorXPos;
	// y position of the low power indicator
	u8 indicatorYPos;
	// number of seconds of receiving the low power signal
	u8 lowPowerDuration;


	/// @publicsection

	/**
	 * Get instance.
	 *
	 * @return	LowPowerManager instance
	 */
	static LowPowerManager getInstance();

	/**
     * De/activate indicator
     *
     * @param active	Set as active or inactive?
     */
    void setActive(bool active);

	/**
     * Sets the position of the low power indicator.
     *
     * @param x		X position (in tiles)
     * @param y		Y position (in tiles)
     */
    void setPosition(u8 x, u8 y);


	/// @privatesection

	/**
	 * Class constructor.
	 *
	 * @fn 			void LowPowerManager::constructor()
     * @memberof 	LowPowerManager
	 */

	/**
	 * Class destructor.
	 *
	 * @fn			void LowPowerManager::destructor()
     * @memberof 	LowPowerManager
	 */

	/**
	 *
	 *
	 * @fn			void LowPowerManager::checkLowPower()
     * @memberof 	LowPowerManager
	 */

	/**
	 *
	 *
	 * @fn					void LowPowerManager::onSecondChange(Object eventFirer)
     * @memberof 			LowPowerManager
     * @param eventFirer	Object that has fired the event
	 */
}


#endif
