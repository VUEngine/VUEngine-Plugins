/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef SPLASH_SCREEN_STATE_H_
#define SPLASH_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S ENUMS
//---------------------------------------------------------------------------------------------------------

enum SplashScreenMessageTypes
{
	kMessageAllowUserInput = kMessageLastEngine + 1
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

abstract class SplashScreenState : GameState
{
	// state to enter after this one
	GameState nextState;
	// spec of screen's stage
	StageSpec* stageSpec;

	void constructor();
	void loadNextState();
	void setNextState(GameState nextState);
	virtual void initNextState();
	virtual void print();
	override bool processMessage(void* owner, Telegram telegram);
	override void enter(void* owner);
	override void exit(void* owner);
	override void suspend(void* owner);
	override void resume(void* owner);
	override void processUserInput(const UserInput* userInput);
}


#endif
