"Bends down" the left and right edges of the screen to make the game world look like a very small planet. 

This effect reads and writes a fourth of the screen and is therefore quite heavy on hardware, reducing the frame rate by about 50%.

![](https://raw.githubusercontent.com/VUEngine/VUEngine-Plugins/master/postProcessing/DwarfPlanet/preview.png)

Usage
-----
	
Add to list of post processing effects of any stage or start manually using either `VUEngine::pushFrontProcessingEffect` or `VUEngine::pushBackProcessingEffect`. 
