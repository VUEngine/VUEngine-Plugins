"Bends down" the left and right edges of the screen to make the world look like a very small planet. 

This effect reads and writes a fourth of the screen and is therefore running OK-ish on hardware, reducing the frame rate by about 50%.

![](https://raw.githubusercontent.com/VUEngine/VUEngine-Plugins/master/postProcessing/DwarfPlanet/preview.png)

Usage
-----
	
Add to list of post processing effects of any stage or start manually using either `Game::pushFrontProcessingEffect` or `Game::pushBackProcessingEffect`. 
