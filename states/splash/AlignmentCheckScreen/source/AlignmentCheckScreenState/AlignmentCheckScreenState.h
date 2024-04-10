/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef ALIGNMENT_CHECK_SCREEN_STATE_H_
#define ALIGNMENT_CHECK_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SplashScreenState.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define __PLUGIN_ALIGNMENT_CHECK_BUTTON_SEQUENCE_LENGTH		5


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

dynamic_singleton class AlignmentCheckScreenState : SplashScreenState
{
	static AlignmentCheckScreenState getInstance(void);
	override void enter(void* owner);
	override void processUserInput(const UserInput*  userInput);
}


#endif
