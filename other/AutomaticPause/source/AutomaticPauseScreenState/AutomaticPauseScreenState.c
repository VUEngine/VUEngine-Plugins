/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <string.h>
#include <Game.h>
#include <Camera.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <PhysicalWorld.h>
#include <I18n.h>
#include <Languages.h>
#include <AutomaticPauseScreenState.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec AUTOMATIC_PAUSE_SCREEN_STAGE;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void AutomaticPauseScreenState::constructor()
{
	Base::constructor();
}

// class's destructor
void AutomaticPauseScreenState::destructor()
{
	// destroy base
	Base::destructor();
}

// state's enter
void AutomaticPauseScreenState::enter(void* owner __attribute__ ((unused)))
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(this, (StageSpec*)&AUTOMATIC_PAUSE_SCREEN_STAGE, NULL, true, false);

	// print text
	FontSize strAutomaticPauseSize = Printing::getTextSize(
		Printing::getInstance(),
		__AUTOMATIC_PAUSE_SCREEN_TITLE_TEXT,
		__AUTOMATIC_PAUSE_SCREEN_TITLE_TEXT_FONT
	);
	FontSize strAutomaticPauseTextSize = Printing::getTextSize(
		Printing::getInstance(),
		__AUTOMATIC_PAUSE_SCREEN_BODY_TEXT,
		__AUTOMATIC_PAUSE_SCREEN_BODY_TEXT_FONT
	);

	u8 strHeaderXPos = ((__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseSize.x >> 1));
	Printing::text(
		Printing::getInstance(),
		__AUTOMATIC_PAUSE_SCREEN_TITLE_TEXT,
		strHeaderXPos,
		18,
		__AUTOMATIC_PAUSE_SCREEN_TITLE_TEXT_FONT
	);

	u8 strTextXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseTextSize.x >> 1);
	Printing::text(
		Printing::getInstance(),
		__AUTOMATIC_PAUSE_SCREEN_BODY_TEXT,
		strTextXPos,
		19 + strAutomaticPauseSize.y,
		__AUTOMATIC_PAUSE_SCREEN_BODY_TEXT_FONT
	);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// start clocks to start animations
	GameState::startClocks(this);

	// fade in screen
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))AutomaticPauseScreenState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

// state's exit
void AutomaticPauseScreenState::exit(void* owner __attribute__ ((unused)))
{
	// call base
	Base::exit(this, owner);
}

void AutomaticPauseScreenState::processUserInput(UserInput userInput)
{
	if(K_STA & userInput.pressedKey)
	{
		// disable user input
		Game::disableKeypad(Game::getInstance());

		// fade out screen
		Brightness brightness = (Brightness){0, 0, 0};
		Camera::startEffect(Camera::getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))AutomaticPauseScreenState::onFadeOutComplete, // callback function
			Object::safeCast(this) // callback scope
		);
	}
}

// handle event
void AutomaticPauseScreenState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	// re-enable user input
	Game::enableKeypad(Game::getInstance());
}

// handle event
void AutomaticPauseScreenState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// re-enable user input
	Game::enableKeypad(Game::getInstance());

	// resume game
	Game::unpause(Game::getInstance(), GameState::safeCast(this));
}
