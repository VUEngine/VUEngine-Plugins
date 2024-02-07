Shows a flashing low power indicator on screen when the system power is low.

Uses the printing layer to do so. If you can spare the extra World, you can instead use the `vuengine//entities/LowPowerEntity` plugin, which uses an Entity.

![](https://raw.githubusercontent.com/VUEngine/VUEngine-Plugins/master/other/LowPowerIndicator/preview.png)

## Usage

For the low power indicator to work, you need to first activate it. The recommended way is to call the function `LowPowerManager::setActive(LowPowerManager::getInstance(), true);` from your game's main function before calling `VUEngine::start(…);`.

The LowPowerManager assumes that characters 2 and 3 of your default font contain the low power indicator image. See the VUEngine default font for an example.

The default position of the low power indicator is 1, 1 (top left corner), where x and y are columns and rows in tiles, *not* pixel positions. It can be changed via `__PLUGIN_LOW_POWER_INDICATOR_X_POSITION` and `__PLUGIN_LOW_POWER_INDICATOR_Y_POSITION`. The position can also be manipulated at any time using the `LowPowerManager::setPosition()` function.
