/* VUEngine - Virtual Utopia Engine <https://www.vuengine.dev>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>, 2007-2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef ADJUSTMENT_SCREEN_STATE_H_
#define ADJUSTMENT_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SplashScreenState.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define __ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE				-64


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

dynamic_singleton class AdjustmentScreenState : SplashScreenState
{
	static AdjustmentScreenState getInstance(void);
	override void initNextState();
	override void enter(void* owner);
	override void exit(void* owner);
	override void suspend(void* owner);
	override void resume(void* owner);
	override void processUserInput(UserInput userInput);
}


#endif
