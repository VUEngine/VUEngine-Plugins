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

#ifndef SEEK_STEERING_BEHAVIOR_H_
#define SEEK_STEERING_BEHAVIOR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SteeringBehavior.h>


//---------------------------------------------------------------------------------------------------------
//											 DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// defines an entity in ROM memory
typedef struct SeekSteeringBehaviorSpec
{
	SteeringBehaviorSpec steeringBehaviorSpec;

	/// Distance when it is considered that the target has been reached
	fix10_6 reachedDistanceThreshold;

	/// Distance when easing starts to apply to the computed force
	fix10_6 easingDistanceThreshold;

} SeekSteeringBehaviorSpec;

typedef const SeekSteeringBehaviorSpec SeekSteeringBehaviorROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

//  Given a target, this behavior returns a steering force which will
//  direct the agent towards the target

/// @ingroup base
class SeekSteeringBehavior : SteeringBehavior
{
	Vector3D target;
	fix10_6 reachedDistanceThreshold;
	fix10_6 easingDistanceThreshold;
	bool slowDownWhenReachingTarget;
	bool reachedTarget;
	bool allowEasing;

	void constructor(const SeekSteeringBehaviorSpec* seekSteeringBehaviorSpec);

	Vector3D getTarget();
	void setTarget(Vector3D value);
	bool getAllowEasing();
	void setAllowEasing(bool value);
	bool getSlowDownWhenReachingTarget();
	void setSlowDownWhenReachingTarget(bool value);
	fix10_6 getReachedDistanceThreshold();
	void setReachedDistanceThreshold(fix10_6 value);
	override Vector3D calculate(Vehicle owner);
}


#endif
