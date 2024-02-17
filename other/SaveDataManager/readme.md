Manages persistence of user data in SRAM.

![Preview Image](preview.png)

## Usage

You'll want to restore the previously saved settings for language and auto pause on startup. The recommended way is to call the following from your game's main function before calling `VUEngine::start(…);`: 
`	AutomaticPauseManager::setActive(AutomaticPauseManager::getInstance(), GameSaveDataManager::getAutomaticPauseStatus(GameSaveDataManager::getInstance()));
	I18n::setActiveLanguage(I18n::getInstance(), GameSaveDataManager::getLanguage(GameSaveDataManager::getInstance()));`

See `headers/onfig.h` for the available macros to modify the save manager's behavior. Define the desired macro in your game's `Config.h` file to override.

Note that any game extending SaveData MUST override the `SaveDataManager::getSaveDataSize()` method to return the correct value!
