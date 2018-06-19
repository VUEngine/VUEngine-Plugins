VUEngine Components: VirtualBoyFont
===================================

Large font based on the "Virtual Boy" writing from the official IPD/Focus adjustment screen.

![Preview Image](preview.png)


USAGE
-----

Add the following to the COMPONENTS variable in your project's `config.make` file to include this component:

	vuengine-components/fonts/VirtualBoyFont

Included are two versions of the font: 

- `VIRTUAL_BOY_FONT` contains the most important 96 characters (punctuation character, numbers and letters)
- `VIRTUAL_BOY_EXTENDED_FONT` additionally contains the full set of European special characters

Include the desired font version in your `__FONTS` array. Be warned that the extended font uses up a large portion of character memory (1440 chars!).


LICENSE
-------

Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>

This software is licensed under the MIT License, which means you can basically do with it whatever you 
want as long as you include the original copyright and license notice in any copy of the software/source. 

	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
	associated documentation files (the "Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
	the following conditions:
	
	The above copyright notice and this permission notice shall be included in all copies or substantial
	portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
	LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
	NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


CREDITS
-------

V810 is a trade mark of NEC. Virtual Boy is a trade mark of Nintendo. 
Jorge Eremiev and Christian Radke are in no way affiliated with either of these parties.
