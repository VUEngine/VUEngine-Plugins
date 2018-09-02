VUEngine Plugin: PostProcessingRhombus
======================================

Draws a rhombus emitted from any SpatialObject.
 
This effect only writes to the framebuffers, but does not read them. Since write access is much quicker than reading, and since only a few pixels are affected, this effect runs well on hardware. 

![Preview Image](preview.png)


USAGE
-----

Add the following to the PLUGINS variable in your project's `config.make` file to include this plugin:

	vuengine/plugins/postProcessing/Rhombus

Add to any SpatialObject using either `Game::pushFrontProcessingEffect` or `Game::pushBackProcessingEffect`. 
