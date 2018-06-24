VUEngine Components: SaveDataManager
====================================

Manages persistence of user data in SRAM.

![Preview Image](preview.png)


USAGE
-----

Add the following to the COMPONENTS variable in your project's `config.make` file to include this component:

	vuengine-components/other/SaveDataManager

You need to initialize the manager before using it. The recommended way is to call the function `SaveDataManager::initialize(SaveDataManager::getInstance());` from your game's main function before calling `Game::start(…);`.

**Dependency**: you will need to include the component `vuengine-components/other/AutomaticPause` for recovering of the automatic pause status from SRAM on initialization to work.

See `source/SaveDataManagerConfig.h` for the available macros to modify the save manager's behaviour. Define the desired macro in your game's `config.h` file to override.
