VUEngine Plugin: Automatic Pause
================================

Automatically pauses the game every 30 minutes. Also comes with a default Automatic Pause Screen.


USAGE
-----

For the automatic pause to work, you need to first activate it. The recommended way is to call the function `AutomaticPauseManager::setActive(AutomaticPauseManager::getInstance(), true);` from your game's main function before calling `Game::start(…);`.

See `source/config.h` for numerous available macros that allow you to modify the auto pause screen appearance. Define the desired macro in your game's `config.h` file to override.

You can set the desired delay before automatic pause (in minutes) with `setAutomaticPauseDelay(u8 automaticPauseDelay)`. You can set another state to use as the automatic pause state with `setAutomaticPauseState(GameState automaticPauseState)`.
