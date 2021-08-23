VUEngine Plugin: PostProcessingRhombus
======================================

Draws a rhombus emitted from any SpatialObject.
 
This effect only writes to the framebuffers, but does not read them. Since write access is much quicker than reading, and since only a few pixels are affected, this effect runs well on hardware. 


USAGE
-----

Add to any SpatialObject using either `Game::pushFrontProcessingEffect` or `Game::pushBackProcessingEffect`. 
