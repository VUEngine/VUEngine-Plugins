VUEngine Plugin: LowBatteryIndicator
====================================

Shows a blinking low battery indicator on screen when the system power is low.

Uses the printing layer to do so. If you can spare the extra World, you can instead use the `vuengine/plugins/entities/LowBatteryIndicatorEntity` plugin, which uses an Entity.

![Preview Image](preview.png)


USAGE
-----

Add the following to the PLUGINS variable in your project's `config.make` file to include this plugin:

		vuengine/plugins/other/LowBatteryIndicator

For the low battery indicator to work, you need to first activate it. The recommended way is to call the function `LowBatteryIndicatorManager::setActive(LowBatteryIndicatorManager::getInstance(), true);` from your game's main function before calling `Game::start(…);`.

The LowBatteryIndicatorManager assumes that characters 2 and 3 of your default font contain the low battery indicator image. See the VUEngine default font for an example.

The default position of the low battery indicator is 1, 1 (top left corner), where x and y are columns and rows in tiles, *not* pixel positions. It can be changed via `__LOW_BATTERY_INDICATOR_X_POSITION` and `__LOW_BATTERY_INDICATOR_Y_POSITION`. The position can also be manipulated at any time using the `LowBatteryIndicatorManager::setPosition()` function.
