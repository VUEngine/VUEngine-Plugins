/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef AUTOMATIC_PAUSE_SELECTION_SCREEN_STATE_H_
#define AUTOMATIC_PAUSE_SELECTION_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SplashScreenState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

dynamic_singleton class AutomaticPauseSelectionScreenState: SplashScreenState
{
	bool selection;

	static AutomaticPauseSelectionScreenState getInstance();
	override void print();
	override void processUserInput(const UserInput* userInput);
}


#endif
