/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <string.h>

#include <AutomaticPauseManager.h>
#include <I18n.h>
#include <Languages.h>
#include <Printer.h>
#include <SaveDataManager.h>
#include <SoundManager.h>
#include <VUEngine.h>

#include "AutomaticPauseSelectionScreenState.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

extern StageROMSpec AutomaticPauseSelectionScreenStage;
extern SoundSpec AutomaticPauseSelectSoundSpec;
extern SoundSpec AutomaticPauseConfirmSoundSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseSelectionScreenState::processUserInput(const UserInput* userInput)
{
	if(userInput->pressedKey & (K_LL | K_LR))
	{
		this->selection = !this->selection;
		AutomaticPauseSelectionScreenState::renderSelection(this);
		SoundManager::playSound(&AutomaticPauseSelectSoundSpec,  NULL, kSoundPlaybackNormal, NULL);
	}
	else if(userInput->pressedKey & (K_A | K_STA))
	{
		ListenerObject saveDataManager = VUEngine::getSaveDataManager();

		AutomaticPauseManager::setActive(AutomaticPauseManager::getInstance(), this->selection);
		
		if(saveDataManager)
		{
			SaveDataManager::setAutomaticPauseStatus(saveDataManager, this->selection);
		}

		SoundManager::playSound(&AutomaticPauseConfirmSoundSpec, NULL, kSoundPlaybackNormal, NULL);

		SplashScreenState::loadNextState(SplashScreenState::safeCast(this));
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseSelectionScreenState::print()
{
	ListenerObject saveDataManager = VUEngine::getSaveDataManager();

	this->selection = saveDataManager
		? SaveDataManager::getAutomaticPauseStatus(saveDataManager)
		: 0;

	const char* strAutomaticPauseTitle = I18n::getText(I18n::getInstance(), kStringAutomaticPauseSelectionTitle);
	FontSize strAutomaticPauseSize = 
		Printer::getTextSize
		(
			strAutomaticPauseTitle, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT_FONT
		);

	const char* strAutomaticPauseExplanation = I18n::getText(I18n::getInstance(), kStringAutomaticPauseSelectionBody);
	FontSize strAutomaticPauseExplanationSize = 
		Printer::getTextSize
		(
			strAutomaticPauseExplanation, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT_FONT
		);

	uint8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseSize.x >> 1);
	Printer::text
	(
		strAutomaticPauseTitle,
		strHeaderXPos,
		8,
		__PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT_FONT
	);

	uint8 strExplanationXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseExplanationSize.x >> 1);
	Printer::text
	(
		strAutomaticPauseExplanation, strExplanationXPos, 9 + strAutomaticPauseSize.y, 
		__PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT_FONT
	);

	AutomaticPauseSelectionScreenState::renderSelection(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseSelectionScreenState::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	this->stageSpec = (StageSpec*)&AutomaticPauseSelectionScreenStage;
	this->selection = true;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseSelectionScreenState::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseSelectionScreenState::renderSelection()
{
	// Get strings and determine sizes
	const char* strOn = I18n::getText(I18n::getInstance(), kStringAutomaticPauseSelectionOn);
	const char* strOff = I18n::getText(I18n::getInstance(), kStringAutomaticPauseSelectionOff);
	
	FontSize strOnSize = 
		Printer::getTextSize(strOn, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT);
	
	FontSize strOffSize = 
		Printer::getTextSize(strOff, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT);
	
	uint8 selectionStart = (48 - (strOnSize.x + __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_GAP + strOffSize.x)) >> 1;

	// Clear options area
	Printer::text
	(
		"                                                ", 0, 
		__PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS, NULL
	);
	
	Printer::text
	(
		"                                                ", 0, 
		__PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, NULL
	);

	Printer::text
	(
		"                                                ", 0, 
		__PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 2, NULL
	);
	
	if(strOnSize.y > 1) 
	{
		Printer::text
		(
			"                                                ", 0, 
			__PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 3, NULL
		);
	
		if(strOnSize.y > 2)
		{
			Printer::text
			(
				"                                                ", 0, 
				__PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 4, NULL
			);
			
			if(strOnSize.y > 3) 
			{
				Printer::text
				(
					"                                                ", 0, 
					__PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 5, NULL
				);
			}
		}
	}

	// Print options
	Printer::text
	(
		strOn, selectionStart, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, 
		__PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT
	);
	
	Printer::text
	(
		strOff, selectionStart + 3 + strOnSize.x, 
		__PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT
	);

	// Print selector
	uint8 optionStart = 
		this->selection ? selectionStart : selectionStart + __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_GAP + strOnSize.x;
	
	uint8 optionEnd = this->selection ? optionStart + strOnSize.x : optionStart + strOffSize.x;
	optionStart--;
	
	Printer::text
	(
		"\x03\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", 
		optionStart, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS, NULL
	);
	
	Printer::text
	(
		"\x04               ", optionEnd, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS, NULL
	);
	
	Printer::text("\x07", optionStart, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, NULL);
	
	Printer::text("\x07", optionEnd, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, NULL);
	
	if(strOnSize.y > 1) 
	{
		Printer::text("\x07", optionStart, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 2, NULL);
		
		Printer::text("\x07", optionEnd, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 2, NULL);
		
		if(strOnSize.y > 2) 
		{
			Printer::text
			(
				"\x07", optionStart, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 3, NULL
			);
			
			Printer::text
			(
				"\x07", optionEnd, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 3, NULL
			);
			
			if(strOnSize.y > 3)
			{
				Printer::text
				(
					"\x07", optionStart, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 4, NULL
				);
				
				Printer::text
				(
					"\x07", optionEnd, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 4, NULL
				);
			}
		}
	}

	Printer::text
	(
		"\x05\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", 
		optionStart, __PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1 + strOnSize.y, NULL
	);
	
	Printer::text
	(
		"\x06               ", optionEnd, 
		__PLUGIN_AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1 + strOnSize.y, NULL
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
