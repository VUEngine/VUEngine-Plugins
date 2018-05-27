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

#ifndef LOW_BATTERY_INDICATOR_MANAGER_H_
#define LOW_BATTERY_INDICATOR_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Object.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

// Position of low battery indicator
#define __LOW_BATTERY_INDICATOR_POS_X			45
#define __LOW_BATTERY_INDICATOR_POS_Y			1

// Delay between showing/not showing the low battery indicator (in milliseconds)
#define __LOW_BATTERY_INDICATOR_BLINK_INTERVAL	500

// Check for the PWR signal every X milliseconds
#define __LOW_BATTERY_CHECK_INTERVAL			1000


//---------------------------------------------------------------------------------------------------------
//												ENUMS
//---------------------------------------------------------------------------------------------------------

/**
 * Low Battery Manager messages
 *
 * @memberof LowBatteryIndicatorManager
 */
enum LowBatteryIndicatorManagerMessages
{
	kLowBatteryIndicatorCheck = 0,
	kLowBatteryIndicatorBlink,
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/**
 * Shows an indicator on screen when the system power is low
 *
 * @ingroup vuengine-components-other
 */
singleton class LowBatteryIndicatorManager : Object
{
	/// @protectedsection

	// low battery indicator showing flag
	bool isShowingIndicator;


	/// @publicsection

	/**
	 * Get instance.
	 *
	 * @return	LowBatteryIndicatorManager instance
	 */
	static LowBatteryIndicatorManager getInstance();

	/**
     * Process a telegram
     *
     * @param telegram	Received telegram
     * @return			True if successfully processed, false otherwise
     */
    override bool handleMessage(Telegram telegram);

	/**
     * De/activate indicator
     *
     * @param active	Set as active or inactive?
     */
    void setActive(bool active);


	/// @privatesection

	/**
	 * Class constructor.
	 *
	 * @fn 			void LowBatteryIndicatorManager::constructor()
     * @memberof 	LowBatteryIndicatorManager
	 */

	/**
	 * Class destructor.
	 *
	 * @fn			void LowBatteryIndicatorManager::destructor()
     * @memberof 	LowBatteryIndicatorManager
	 */

	/**
	 *
	 *
	 * @fn			void LowBatteryIndicatorManager::checkLowBattery()
     * @memberof 	LowBatteryIndicatorManager
	 */

	/**
	 *
	 *
	 * @fn					void LowBatteryIndicatorManager::printLowBatteryIndicator(bool showIndicator)
     * @memberof 			LowBatteryIndicatorManager
     * @param showIndicator	Whether to print or remove indicator
	 */

	/**
	 *
	 *
	 * @fn			void LowBatteryIndicatorManager::queueNextCheck()
     * @memberof 	LowBatteryIndicatorManager
	 */

	/**
	 *
	 *
	 * @fn					void LowBatteryIndicatorManager::queueNextBlink(bool showIndicator)
     * @memberof 			LowBatteryIndicatorManager
     * @param showIndicator	Whether to print or remove indicator
	 */

	/**
     * Show indicator if it's not already being shown
     *
     * @fn			void LowBatteryIndicatorManager::startShowingIndicator()
     * @memberof 	LowBatteryIndicatorManager
	 */

	/**
     * Remove indicator if it's currently being shown
     *
     * @fn			void LowBatteryIndicatorManager::stopShowingIndicator()
     * @memberof 	LowBatteryIndicatorManager
	 */
	 //
}


#endif
