/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

#ifndef STEERING_BEHAVIOR_H_
#define STEERING_BEHAVIOR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Behavior.h>


//---------------------------------------------------------------------------------------------------------
//											 DEFINITIONS
//---------------------------------------------------------------------------------------------------------

class Vehicle;

enum SteeringBehaviorEvents
{
	kTargetReached = kLastEngineEvent + 1,
};

enum SummingMethod
{
	kPrioritized = 1,
	kWeightedAverage
};

// defines an entity in ROM memory
typedef struct SteeringBehaviorSpec
{
	/// BehaviorSpec
	BehaviorSpec behaviorSpec;

	/// Priority: higher values have more priority
	int priority;

	/// Weight to this behavior on the overal effect (range: 0-1)
	fix10_6 weight;

	/// Maximum force to apply
	fix10_6 maximumForce;

	/// Distance when it is considered that the target has been reached
	fix10_6 reachedDistanceThreshold;

	/// Distance when easing starts to apply to the computed force
	fix10_6 easingDistanceThreshold;

} SteeringBehaviorSpec;

typedef const SteeringBehaviorSpec SteeringBehaviorROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/// @ingroup base
class SteeringBehavior : Behavior
{
	// higher value has more priority
	int priority;
	fix10_6 weight;
	fix10_6 maximumForce;
	fix10_6 reachedDistanceThreshold;
	fix10_6 easingDistanceThreshold;

	void constructor(const SteeringBehaviorSpec* steeringBehaviorSpec);

	static Vector3D calculateForce(Vehicle vehicle);
	int getPriority();
	void setPriority(int value);
	fix10_6 getWeight();
	void setWeight(fix10_6 value);
	fix10_6 getMaximumForce();
	void setMaximumForce(fix10_6 value);
	fix10_6 getEasingDistanceThreshold();
	void setEasingDistanceThreshold(fix10_6 value);
	fix10_6 getReachedDistanceThreshold();
	void setReachedDistanceThreshold(fix10_6 value);

	virtual Vector3D calculate(Vehicle owner) = 0;
}


#endif
