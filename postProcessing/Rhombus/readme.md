Draws a growing rhombus emitted from any SpatialObject.
 
This effect only writes to the framebuffers, but does not read them. Since write access is much quicker than reading, and since only a few pixels are affected, this effect runs well on hardware. 

![](https://raw.githubusercontent.com/VUEngine/VUEngine-Plugins/master/postProcessing/Rhombus/preview.png)

Usage
-----

Add to any SpatialObject using either `VUEngine::pushFrontProcessingEffect` or `VUEngine::pushBackProcessingEffect`. 
