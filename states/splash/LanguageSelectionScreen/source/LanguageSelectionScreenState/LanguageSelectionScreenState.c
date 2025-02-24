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

#include <I18n.h>
#include <Languages.h>
#include <Printer.h>
#include <SaveDataManager.h>
#include <Singleton.h>
#include <SoundManager.h>
#include <VirtualList.h>
#include <VUEngine.h>

#include "LanguageSelectionScreenState.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

extern StageROMSpec LanguageSelectionScreenStage;
extern LangROMSpec* _languages[];
extern ActorSpec FlagCursorActorSpec;
extern ActorSpec FlagUnknownActorSpec;
extern SoundSpec LanguageConfirmSoundSpec;
extern SoundSpec LanguageSelectSoundSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LanguageSelectionScreenState::enter(void* owner)
{
	Base::enter(this, owner);

	ListenerObject saveDataManager = VUEngine::getSaveDataManager();

	// Get active language from sram
	uint8 activeLanguage = I18n::getActiveLanguage(I18n::getInstance());
	if(saveDataManager)
	{
		activeLanguage = SaveDataManager::getLanguage(saveDataManager);
	}
	I18n::setActiveLanguage(I18n::getInstance(), activeLanguage);
	this->selection = activeLanguage;

	#if(__PLUGIN_LANGUAGE_SELECTION_SCREEN_VARIANT == 0)

		// Create options selector and populate with language names
		this->languageSelector = new OptionsSelector(1, 8, __PLUGIN_LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT, NULL, NULL);
		VirtualList languageNames = new VirtualList();
		uint8 optionsWidth = 0;
		int32 i = 0;
		for(; _languages[i]; i++)
		{
			Option* option = new Option;
			option->value = (char*)_languages[i]->name;
			option->type = kString;
			VirtualList::pushBack(languageNames, option);

			FontSize strOptionSize = Printer::getTextSize(option->value, __PLUGIN_LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);
			optionsWidth = (strOptionSize.x > optionsWidth) ? strOptionSize.x : optionsWidth;
		}
		
		OptionsSelector::setOptions(this->languageSelector, languageNames);
		delete languageNames;

		// Print options
		OptionsSelector::print(this->languageSelector, (__HALF_SCREEN_WIDTH_IN_CHARS) - (optionsWidth >> 1), 10, kOptionsAlignLeft, 0);
		OptionsSelector::setSelectedOption(this->languageSelector, activeLanguage);

		LanguageSelectionScreenState::printSelection(this);

	#endif
	#if(__PLUGIN_LANGUAGE_SELECTION_SCREEN_VARIANT == 1)

		// Add flags to stage
		this->flagsTotalHalfWidth = ((LanguageSelectionScreenState::getNumLangs(this) - 1) * (__PLUGIN_LANGUAGE_SELECTION_SCREEN_IMAGE_WIDTH)) >> 1;
		uint8 i = 0;
		this->flagCursorActor = LanguageSelectionScreenState::addFlagToStage(this, &FlagCursorActorSpec, 0);
		for(i = 0; _languages[i]; i++)
		{
			// Add flag
			ActorSpec* actorSpec = (_languages[i]->actorSpec != NULL)
				? _languages[i]->actorSpec
				: &FlagUnknownActorSpec;
			LanguageSelectionScreenState::addFlagToStage(this, actorSpec, i);
		}

		LanguageSelectionScreenState::printSelection(this);

	#endif
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LanguageSelectionScreenState::processUserInput(const UserInput* userInput)
{
	if(userInput->pressedKey & (K_LU | K_RU | K_LL | K_RL))
	{
		LanguageSelectionScreenState::select(this, false);
	}
	else if(userInput->pressedKey & (K_LD | K_RD | K_LR | K_RR))
	{
		LanguageSelectionScreenState::select(this, true);
	}
	else if(userInput->pressedKey & (K_A | K_STA))
	{
		SoundManager::playSound(&LanguageConfirmSoundSpec, NULL, kSoundPlaybackNormal, NULL);

		SplashScreenState::loadNextState(SplashScreenState::safeCast(this));
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LanguageSelectionScreenState::print()
{
	const char* strTitle = I18n::getText(I18n::getInstance(), kStringLanguageSelectTitle);
	#if(__PLUGIN_LANGUAGE_SELECTION_SCREEN_VARIANT == 0)

		// Print header
		FontSize strHeaderSize = Printer::getTextSize(strTitle, __PLUGIN_LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		uint8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strHeaderSize.x >> 1);
		uint8 strHeaderYPos = 9 - strHeaderSize.y;
		Printer::text("                                                ", 0, strHeaderYPos, __PLUGIN_LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		Printer::text(strTitle, strHeaderXPos, strHeaderYPos, __PLUGIN_LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);

	#endif
	#if(__PLUGIN_LANGUAGE_SELECTION_SCREEN_VARIANT == 1)

		// Print header
		FontSize strHeaderSize = Printer::getTextSize(strTitle, __PLUGIN_LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		uint8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strHeaderSize.x >> 1);
		uint8 strHeaderYPos = 11 - strHeaderSize.y;
		Printer::text("                                                ", 0, strHeaderYPos, __PLUGIN_LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		Printer::text(strTitle, strHeaderXPos, strHeaderYPos, __PLUGIN_LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);

		// Print language
		char* strLanguageName = I18n::getActiveLanguageName(I18n::getInstance());
		FontSize strLanguageNameSize = Printer::getTextSize(strLanguageName, __PLUGIN_LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);
		int32 strLanguageNameXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strLanguageNameSize.x >> 1);
		int32 strLanguageNameYPos = ((LanguageSelectionScreenState::getFlagYPosition(this) + __PLUGIN_LANGUAGE_SELECTION_SCREEN_IMAGE_HEIGHT) >> 3) - 1;
		Printer::text("                                                ", 0, strLanguageNameYPos, __PLUGIN_LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);
		Printer::text(strLanguageName, strLanguageNameXPos, strLanguageNameYPos, __PLUGIN_LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);

	#endif
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LanguageSelectionScreenState::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	// Init members
	this->stageSpec = (StageSpec*)&LanguageSelectionScreenStage;
	this->flagCursorActor = NULL;
	this->languageSelector = NULL;
	this->selection = 0;
	this->flagsTotalHalfWidth = 0;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LanguageSelectionScreenState::destructor()
{
	if(this->languageSelector)
	{
		delete this->languageSelector;
	}

	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LanguageSelectionScreenState::printSelection()
{
	LanguageSelectionScreenState::print(this);

	#if(__PLUGIN_LANGUAGE_SELECTION_SCREEN_VARIANT == 1)

		// Set cursor position
		Vector3D position =
		{
		#ifdef __LEGACY_COORDINATE_PROJECTION
			__PIXELS_TO_METERS(LanguageSelectionScreenState::getFlagXPosition(this, this->selection)),
			__PIXELS_TO_METERS(LanguageSelectionScreenState::getFlagYPosition(this)),
		#else
			__PIXELS_TO_METERS(this->selection * (__PLUGIN_LANGUAGE_SELECTION_SCREEN_IMAGE_WIDTH) - this->flagsTotalHalfWidth),
			0,
		#endif
			0,
		};
		Actor::setLocalPosition(this->flagCursorActor, &position);

	#endif
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LanguageSelectionScreenState::select(bool next)
{
	#if(__PLUGIN_LANGUAGE_SELECTION_SCREEN_VARIANT == 0)
		if(next)
		{
			OptionsSelector::selectNext(this->languageSelector);
		}
		else
		{
			OptionsSelector::selectPrevious(this->languageSelector);
		}
		this->selection = OptionsSelector::getSelectedOption(this->languageSelector);
	#endif
	#if(__PLUGIN_LANGUAGE_SELECTION_SCREEN_VARIANT == 1)
		uint8 numLangs = LanguageSelectionScreenState::getNumLangs(this);
		if(next)
		{
			this->selection = (this->selection < (numLangs - 1)) ? this->selection + 1 : 0;
		}
		else
		{
			this->selection = (this->selection > 0) ? this->selection - 1 : (numLangs - 1);
		}
	#endif

	LanguageSelectionScreenState::persistChoice(this);
	LanguageSelectionScreenState::printSelection(this);

	SoundManager::playSound(&LanguageSelectSoundSpec, NULL, kSoundPlaybackNormal, NULL);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LanguageSelectionScreenState::persistChoice()
{
	ListenerObject saveDataManager = VUEngine::getSaveDataManager();

	I18n::setActiveLanguage(I18n::getInstance(), this->selection);
	if(saveDataManager)
	{
		SaveDataManager::setLanguage(saveDataManager, this->selection);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

uint8 LanguageSelectionScreenState::getNumLangs()
{
	uint8 i, numLangs = 0;
	for(i = 0; _languages[i]; i++)
	{
		numLangs++;
	}

	return numLangs;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

Actor LanguageSelectionScreenState::addFlagToStage(ActorSpec* actorSpec, uint8 position)
{
	PositionedActor flagPositionedActor = {
		actorSpec,
		{
		#ifdef __LEGACY_COORDINATE_PROJECTION
			LanguageSelectionScreenState::getFlagXPosition(this, position),
			LanguageSelectionScreenState::getFlagYPosition(this),
		#else
			position * (__PLUGIN_LANGUAGE_SELECTION_SCREEN_IMAGE_WIDTH) - this->flagsTotalHalfWidth,
			0,
		#endif
			0
		},
		{0, 0, 0}, 
		{1, 1, 1},
		0, NULL, NULL, NULL, false
	};

#ifdef __LEGACY_COORDINATE_PROJECTION
	return Stage::spawnChildActor(this->stage, &flagPositionedActor, true);
#else
	return UIContainer::spawnChildActor(this->uiContainer, &flagPositionedActor);
#endif
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

int32 LanguageSelectionScreenState::getFlagXPosition(uint8 position)
{
	return 192 - this->flagsTotalHalfWidth + (position * (__PLUGIN_LANGUAGE_SELECTION_SCREEN_IMAGE_WIDTH));
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

int32 LanguageSelectionScreenState::getFlagYPosition()
{
	return 96 + ((__PLUGIN_LANGUAGE_SELECTION_SCREEN_IMAGE_HEIGHT) >> 1);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
