/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PRECAUTION_SCREEN_STATE_H_
#define PRECAUTION_SCREEN_STATE_H_


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <SplashScreenState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

dynamic_singleton class PrecautionScreenState : SplashScreenState
{
	static PrecautionScreenState getInstance();
	override void print();
	override void enter(void* owner);
	override bool processMessage(void* owner, Telegram telegram);
}


#endif
