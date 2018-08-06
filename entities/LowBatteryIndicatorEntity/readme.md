VUEngine Plugin: LowBatteryIndicatorEntity
==========================================

Shows a blinking low battery indicator on screen when the system power is low.

Uses an entity to do so. If you want to save the extra World needed, you can instead use the `vuengine/plugins/other/LowBatteryIndicator` plugin, which makes use of the printing layer instead.

![Preview Image](preview.png)


USAGE
-----

Add the following to the PLUGINS variable in your project's `config.make` file to include this plugin:

	vuengine/plugins/entities/LowBatteryIndicatorEntity

Add `LOW_BATTERY_INDICATOR_LB` to your game's stages.

The default position of the low battery indicator is 16, 12 (top left corner), where x and y are the pixel position of the entity's center. It can be changed via `__LOW_BATTERY_INDICATOR_ENTITY_X_POSITION`, `__LOW_BATTERY_INDICATOR_ENTITY_Y_POSITION`, `__LOW_BATTERY_INDICATOR_ENTITY_Z_POSITION` AND `__LOW_BATTERY_INDICATOR_ENTITY_Z_DISPLACEMENT`.