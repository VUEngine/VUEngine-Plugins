Shows a flashing low power indicator on screen when the system power is low.

Uses an actor to do so. If you want to save the extra World needed, you can instead use the `vuengine//other/LowPowerIndicator` plugin, which makes use of the printing layer instead.

![Preview Image](preview.png)

## Usage

Add `LowPowerIndicatorActorSpec` to your game's stages.

The default position of the low power indicator is 16, 12 (top left corner), where x and y are the pixel position of the actor's center. It can be changed via `__PLUGIN_LOW_POWER_ACTOR_X_POSITION`, `__PLUGIN_LOW_POWER_ACTOR_Y_POSITION`, `__PLUGIN_LOW_POWER_ACTOR_Z_POSITION` AND `__PLUGIN_LOW_POWER_ACTOR_Z_DISPLACEMENT`.
