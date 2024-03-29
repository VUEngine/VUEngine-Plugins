/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LANGUAGE_SELECTION_SCREEN_STATE_H_
#define LANGUAGE_SELECTION_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SplashScreenState.h>
#include <OptionsSelector.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

dynamic_singleton class LanguageSelectionScreenState: SplashScreenState
{
	Entity flagCursorEntity;
	OptionsSelector languageSelector;
	uint8 selection;
	uint8 flagsTotalHalfWidth;

	static LanguageSelectionScreenState getInstance();
	override void enter(void* owner);
	override void processUserInput(const UserInput* userInput);
	override void print();
}


#endif
