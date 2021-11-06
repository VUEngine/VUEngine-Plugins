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

#include <Game.h>
#include <Camera.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <LanguageSelectionScreenState.h>
#include <KeypadManager.h>
#include <SoundManager.h>
#include <I18n.h>
#include <Languages.h>
#include <SaveDataManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec LanguageSelectionScreenStage;
extern LangROMSpec* _languages[];
extern EntitySpec FlagCursorEntity;
extern EntitySpec FlagUnknownEntity;
extern Sound LangConfirmSound;
extern Sound LangSelectSound;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void LanguageSelectionScreenState::constructor()
{
	Base::constructor();

	// init members
	this->stageSpec = (StageSpec*)&LanguageSelectionScreenStage;
	this->flagCursorEntity = NULL;
	this->languageSelector = NULL;
	this->selection = 0;
	this->flagsTotalHalfWidth = 0;
}

void LanguageSelectionScreenState::destructor()
{
	if(this->languageSelector)
	{
		delete this->languageSelector;
	}

	// destroy base
	Base::destructor();
}

void LanguageSelectionScreenState::processUserInput(UserInput userInput)
{
	if(userInput.pressedKey & (K_LU | K_RU | K_LL | K_RL))
	{
		LanguageSelectionScreenState::select(this, false);
	}
	else if(userInput.pressedKey & (K_LD | K_RD | K_LR | K_RR))
	{
		LanguageSelectionScreenState::select(this, true);
	}
	else if(userInput.pressedKey & (K_A | K_STA))
	{
		Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
		SoundManager::playSound(SoundManager::getInstance(), &LangConfirmSound, kPlayAll, (const Vector3D*)&position, kSoundWrapperPlaybackNormal, NULL, NULL);

		SplashScreenState::loadNextState(SplashScreenState::safeCast(this));
	}
}

void LanguageSelectionScreenState::enter(void* owner)
{
	Base::enter(this, owner);

	Object saveDataManager = Game::getSaveDataManager(Game::getInstance());

	// get active language from sram
	uint8 activeLanguage = I18n::getActiveLanguage(I18n::getInstance());
	if(saveDataManager)
	{
		activeLanguage = SaveDataManager::getLanguage(saveDataManager);
	}
	I18n::setActiveLanguage(I18n::getInstance(), activeLanguage);
	this->selection = activeLanguage;

	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 0)

		// create options selector and populate with language names
		this->languageSelector = new OptionsSelector(1, 8, __LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);
		VirtualList languageNames = new VirtualList();
		uint8 optionsWidth = 0;
		int32 i = 0;
		for(; _languages[i]; i++)
		{
			Option* option = new Option;
			option->value = (char*)_languages[i]->name;
			option->type = kString;
			VirtualList::pushBack(languageNames, option);

			FontSize strOptionSize = Printing::getTextSize(Printing::getInstance(), option->value, __LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);
			optionsWidth = (strOptionSize.x > optionsWidth) ? strOptionSize.x : optionsWidth;
		}
		OptionsSelector::setOptions(this->languageSelector, languageNames);
		delete languageNames;

		// print options
		OptionsSelector::printOptions(this->languageSelector, (__HALF_SCREEN_WIDTH_IN_CHARS) - (optionsWidth >> 1), 10);
		OptionsSelector::setSelectedOption(this->languageSelector, activeLanguage);

		LanguageSelectionScreenState::printSelection(this);

	#endif
	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 1)

		// add flags to stage
		this->flagsTotalHalfWidth = LanguageSelectionScreenState::getFlagsTotalHalfWidth(this);
		uint8 i = 0;
		this->flagCursorEntity = LanguageSelectionScreenState::addFlagToStage(this, &FlagCursorEntity, 0);
		for(i = 0; _languages[i]; i++)
		{
			// add flag
			EntitySpec* entitySpec = (_languages[i]->entitySpec != NULL)
				? _languages[i]->entitySpec
				: &FlagUnknownEntity;
			LanguageSelectionScreenState::addFlagToStage(this, entitySpec, i);
		}

		LanguageSelectionScreenState::printSelection(this);

	#endif
}

void LanguageSelectionScreenState::print()
{
	const char* strTitle = I18n::getText(I18n::getInstance(), kStringLanguageSelectTitle);
	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 0)

		// print header
		FontSize strHeaderSize = Printing::getTextSize(Printing::getInstance(), strTitle, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		uint8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strHeaderSize.x >> 1);
		uint8 strHeaderYPos = 9 - strHeaderSize.y;
		Printing::text(Printing::getInstance(), "                                                ", 0, strHeaderYPos, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		Printing::text(Printing::getInstance(), strTitle, strHeaderXPos, strHeaderYPos, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);

	#endif
	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 1)

		// print header
		FontSize strHeaderSize = Printing::getTextSize(Printing::getInstance(), strTitle, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		uint8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strHeaderSize.x >> 1);
		uint8 strHeaderYPos = 11 - strHeaderSize.y;
		Printing::text(Printing::getInstance(), "                                                ", 0, strHeaderYPos, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		Printing::text(Printing::getInstance(), strTitle, strHeaderXPos, strHeaderYPos, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);

		// print language
		char* strLanguageName = I18n::getActiveLanguageName(I18n::getInstance());
		FontSize strLanguageNameSize = Printing::getTextSize(Printing::getInstance(), strLanguageName, __LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);
		int32 strLanguageNameXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strLanguageNameSize.x >> 1);
		int32 strLanguageNameYPos = ((LanguageSelectionScreenState::getFlagYPosition(this) + __LANGUAGE_SELECTION_SCREEN_IMAGE_HEIGHT) >> 3) - 1;
		Printing::text(Printing::getInstance(), "                                                ", 0, strLanguageNameYPos, __LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);
		Printing::text(Printing::getInstance(), strLanguageName, strLanguageNameXPos, strLanguageNameYPos, __LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);

	#endif
}

void LanguageSelectionScreenState::printSelection()
{
	LanguageSelectionScreenState::print(this);

	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 1)

		// set cursor position
		Vector3D position =
		{
			__PIXELS_TO_METERS(LanguageSelectionScreenState::getFlagXPosition(this, this->selection)),
			__PIXELS_TO_METERS(LanguageSelectionScreenState::getFlagYPosition(this)),
			0,
		};
		Entity::setLocalPosition(this->flagCursorEntity, &position);

	#endif
}

void LanguageSelectionScreenState::select(bool next)
{
	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 0)
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
	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 1)
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

	Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
	SoundManager::playSound(SoundManager::getInstance(), &LangSelectSound, kPlayAll, (const Vector3D*)&position, kSoundWrapperPlaybackNormal, NULL, NULL);
}

void LanguageSelectionScreenState::persistChoice()
{
	Object saveDataManager = Game::getSaveDataManager(Game::getInstance());

	I18n::setActiveLanguage(I18n::getInstance(), this->selection);
	if(saveDataManager)
	{
		SaveDataManager::setLanguage(saveDataManager, this->selection);
	}
}

uint8 LanguageSelectionScreenState::getNumLangs()
{
	uint8 i, numLangs = 0;
	for(i = 0; _languages[i]; i++)
	{
		numLangs++;
	}

	return numLangs;
}

uint8 LanguageSelectionScreenState::getFlagsTotalHalfWidth()
{
	return ((LanguageSelectionScreenState::getNumLangs(this) - 1) * (__LANGUAGE_SELECTION_SCREEN_IMAGE_WIDTH)) >> 1;
}

Entity LanguageSelectionScreenState::addFlagToStage(EntitySpec* entitySpec, uint8 position)
{
	PositionedEntity flagPositionedEntity = {
		entitySpec,
		{
			LanguageSelectionScreenState::getFlagXPosition(this, position),
			LanguageSelectionScreenState::getFlagYPosition(this),
			0,
			0,
		},
		0, NULL, NULL, NULL, false
	};

	return Stage::addChildEntity(Game::getStage(Game::getInstance()), &flagPositionedEntity, true);
}

int32 LanguageSelectionScreenState::getFlagXPosition(uint8 position)
{
	return 192 - this->flagsTotalHalfWidth + (position * (__LANGUAGE_SELECTION_SCREEN_IMAGE_WIDTH));
}

int32 LanguageSelectionScreenState::getFlagYPosition()
{
	return 96 + ((__LANGUAGE_SELECTION_SCREEN_IMAGE_HEIGHT) >> 1);
}
