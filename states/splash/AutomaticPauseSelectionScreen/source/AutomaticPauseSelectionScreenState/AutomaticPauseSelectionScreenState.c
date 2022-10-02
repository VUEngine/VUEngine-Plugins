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

#include <VUEngine.h>
#include <Camera.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <AutomaticPauseSelectionScreenState.h>
#include <KeypadManager.h>
#include <SoundManager.h>
#include <I18n.h>
#include <Languages.h>
#include <AutomaticPauseManager.h>
#include <SaveDataManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec AutomaticPauseSelectionScreenStage;
extern Sound AutomaticPauseSelectSound;
extern Sound AutomaticPauseConfirmSound;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void AutomaticPauseSelectionScreenState::constructor()
{
	Base::constructor();

	this->stageSpec = (StageSpec*)&AutomaticPauseSelectionScreenStage;
	this->selection = true;
}

// class's destructor
void AutomaticPauseSelectionScreenState::destructor()
{
	// destroy base
	Base::destructor();
}

void AutomaticPauseSelectionScreenState::print()
{
	ListenerObject saveDataManager = VUEngine::getSaveDataManager(VUEngine::getInstance());

	this->selection = saveDataManager
		? SaveDataManager::getAutomaticPauseStatus(saveDataManager)
		: 0;

	const char* strAutomaticPauseTitle = I18n::getText(I18n::getInstance(), kStringAutomaticPauseSelectionTitle);
	FontSize strAutomaticPauseSize = Printing::getTextSize(Printing::getInstance(), strAutomaticPauseTitle, __AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT_FONT);

	const char* strAutomaticPauseExplanation = I18n::getText(I18n::getInstance(), kStringAutomaticPauseSelectionBody);
	FontSize strAutomaticPauseExplanationSize = Printing::getTextSize(Printing::getInstance(), strAutomaticPauseExplanation, __AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT_FONT);

	uint8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseSize.x >> 1);
	Printing::text(
		Printing::getInstance(),
		strAutomaticPauseTitle,
		strHeaderXPos,
		8,
		__AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT_FONT
	);

	uint8 strExplanationXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseExplanationSize.x >> 1);
	Printing::text(Printing::getInstance(), strAutomaticPauseExplanation, strExplanationXPos, 9 + strAutomaticPauseSize.y, __AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT_FONT);

	AutomaticPauseSelectionScreenState::renderSelection(this);
}

void AutomaticPauseSelectionScreenState::renderSelection()
{
	// get strings and determine sizes
	const char* strOn = I18n::getText(I18n::getInstance(), kStringAutomaticPauseSelectionOn);
	const char* strOff = I18n::getText(I18n::getInstance(), kStringAutomaticPauseSelectionOff);
	FontSize strOnSize = Printing::getTextSize(Printing::getInstance(), strOn, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT);
	FontSize strOffSize = Printing::getTextSize(Printing::getInstance(), strOff, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT);
	uint8 selectionStart = (48 - (strOnSize.x + __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_GAP + strOffSize.x)) >> 1;

	// clear options area
	Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS, NULL);
	Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, NULL);
	Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 2, NULL);
	if(strOnSize.y > 1) {
		Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 3, NULL);
		if(strOnSize.y > 2) {
			Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 4, NULL);
			if(strOnSize.y > 3) {
				Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 5, NULL);
			}
		}
	}

	// print options
	Printing::text(Printing::getInstance(), strOn, selectionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT);
	Printing::text(Printing::getInstance(), strOff, selectionStart + 3 + strOnSize.x, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT);

	// print selector
	uint8 optionStart = this->selection ? selectionStart : selectionStart + __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_GAP + strOnSize.x;
	uint8 optionEnd = this->selection ? optionStart + strOnSize.x : optionStart + strOffSize.x;
	optionStart--;
	Printing::text(Printing::getInstance(), "\x03\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS, NULL);
	Printing::text(Printing::getInstance(), "\x04               ", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS, NULL);
	Printing::text(Printing::getInstance(), "\x07", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, NULL);
	Printing::text(Printing::getInstance(), "\x07", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, NULL);
	if(strOnSize.y > 1) {
		Printing::text(Printing::getInstance(), "\x07", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 2, NULL);
		Printing::text(Printing::getInstance(), "\x07", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 2, NULL);
		if(strOnSize.y > 2) {
			Printing::text(Printing::getInstance(), "\x07", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 3, NULL);
			Printing::text(Printing::getInstance(), "\x07", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 3, NULL);
			if(strOnSize.y > 3) {
				Printing::text(Printing::getInstance(), "\x07", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 4, NULL);
				Printing::text(Printing::getInstance(), "\x07", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 4, NULL);
			}
		}
	}
	Printing::text(Printing::getInstance(), "\x05\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1 + strOnSize.y, NULL);
	Printing::text(Printing::getInstance(), "\x06               ", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1 + strOnSize.y, NULL);
}

void AutomaticPauseSelectionScreenState::processUserInput(UserInput userInput)
{
	if(userInput.pressedKey & (K_LL | K_LR))
	{
		this->selection = !this->selection;
		AutomaticPauseSelectionScreenState::renderSelection(this);

		Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
		SoundManager::playSound(SoundManager::getInstance(), &AutomaticPauseSelectSound, kPlayAll, (const Vector3D*)&position, kSoundWrapperPlaybackNormal, NULL, NULL);
	}
	else if(userInput.pressedKey & (K_A | K_STA))
	{
		ListenerObject saveDataManager = VUEngine::getSaveDataManager(VUEngine::getInstance());

		AutomaticPauseManager::setActive(AutomaticPauseManager::getInstance(), this->selection);
		
		if(saveDataManager)
		{
			SaveDataManager::setAutomaticPauseStatus(saveDataManager, this->selection);
		}

		Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
		SoundManager::playSound(SoundManager::getInstance(), &AutomaticPauseConfirmSound, kPlayAll, (const Vector3D*)&position, kSoundWrapperPlaybackNormal, NULL, NULL);

		SplashScreenState::loadNextState(SplashScreenState::safeCast(this));
	}
}
