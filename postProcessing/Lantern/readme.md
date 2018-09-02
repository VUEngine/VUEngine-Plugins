VUEngine Plugin: PostProcessingLantern
======================================

Adds a lantern like effect to any SpatialObject, where everything outside of a certain radius around the SpatialObject is rendered black. 

![Preview Image](preview.png)


USAGE
-----

Add the following to the PLUGINS variable in your project's `config.make` file to include this plugin:

	vuengine/plugins/postProcessing/Lantern

Add to any SpatialObject using either `Game::pushFrontProcessingEffect` or `Game::pushBackProcessingEffect`. 
