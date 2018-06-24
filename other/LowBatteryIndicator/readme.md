VUEngine Components: LowBatteryIndicator
========================================

Shows a blinking low battery indicator on screen when the system power is low.

![Preview Image](preview.png)


USAGE
-----

Add the following to the COMPONENTS variable in your project's `config.make` file to include this component:

	vuengine-components/other/LowBatteryIndicator

For the low battery indicator to work, you need to first activate it. The recommended way is to call the function `LowBatteryIndicatorManager::setActive(LowBatteryIndicatorManager::getInstance(), true);` from your game's main function before calling `Game::start(…);`.

The LowBatteryIndicatorManager assumes that characters 2 and 3 of your default font contain the low battery indicator image. See the VUEngine default font for an example. 

You can set the position of the low battery indicator using the `LowBatteryIndicatorManager::setPosition(u8 x, u8 y)` function, where x and y are columns and rows in tiles, *not* pixel positions. Default is 45, 1 (top right corner).  