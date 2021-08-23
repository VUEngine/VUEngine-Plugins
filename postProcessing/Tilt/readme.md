VUEngine Plugin: PostProcessingTilt
===================================

"Tilts" the game image by a few percent by gradually shifting columns.

This effect reads and write almost the whole screen and is therefore not feasible on hardware. 


USAGE
-----

Add the following to the PLUGINS variable in your project's `config.make` file to include this plugin:

	vuengine/plugins/postProcessing/Tilt

Add to list of post processing effects of any stage or start manually using either `Game::pushFrontProcessingEffect` or `Game::pushBackProcessingEffect`. 
