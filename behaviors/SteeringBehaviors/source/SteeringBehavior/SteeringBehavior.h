/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef STEERING_BEHAVIOR_H_
#define STEERING_BEHAVIOR_H_


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <Events.h>
#include <Behavior.h>


//=========================================================================================================
// FORWARD DECLARATIONS
//=========================================================================================================

class Vehicle;


//=========================================================================================================
// CLASS' DATA
//=========================================================================================================

enum SteeringBehaviorEvents
{
	kTargetReached = kEventEngineLast + 1,
};

enum SummingMethod
{
	kPrioritized = 1,
	kWeightedAverage
};

/// A SteeringBehavior Spec
/// @memberof SteeringBehavior
typedef struct SteeringBehaviorSpec
{
	BehaviorSpec behaviorSpec;

	/// Priority: higher values have more priority
	int32 priority;

	/// Weight to this behavior on the overal effect (range: 0-1)
	fixed_t weight;

	/// Maximum force to apply
	fixed_t maximumForce;

	/// Random deviation range
	fixed_t deviation;

} SteeringBehaviorSpec;

/// A SteeringBehavior spec that is stored in ROM
/// @memberof SteeringBehavior
typedef const SteeringBehaviorSpec SteeringBehaviorROMSpec;


//=========================================================================================================
// CLASS' DECLARATION
//=========================================================================================================

///
/// Class Behavior
///
/// Inherits from Behavior
///
/// Defines an interface for steering behaviors
class SteeringBehavior : Behavior
{
	/// Force to apply
	Vector3D force;

	// higher value has more priority
	int32 priority;
	fixed_t weight;
	fixed_t maximumForce;
	fixed_t deviation;

	/// Class' constructor
	/// @param owner: SpatialObject to which the behavior attaches to
	/// @param steeringBehaviorSpec: Specification that determines how to configure the behavior
	void constructor(SpatialObject owner, const SteeringBehaviorSpec* steeringBehaviorSpec);

	const SteeringBehaviorSpec* getSteeringBehaviorSpec();
	void reset();

	static Vector3D calculateForce(Vehicle vehicle, uint16 summingMethod);

	void setPriority(int32 value);
	int32 getPriority();

	void setWeight(fixed_t value);
	fixed_t getWeight();

	void setMaximumForce(fixed_t value);
	fixed_t getMaximumForce();

	virtual Vector3D calculate(Vehicle owner) = 0;
}

#endif
