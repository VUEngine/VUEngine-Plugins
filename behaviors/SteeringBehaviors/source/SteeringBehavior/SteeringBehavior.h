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

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Events.h>
#include <Behavior.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// FORWARD DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

class Vehicle;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

enum SteeringBehaviorEvents
{
	kEventSteeringTargetReached = kEventPluginsFirst + 1,
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

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class Behavior
///
/// Inherits from Behavior
///
/// Defines an interface for steering behaviors.
class SteeringBehavior : Behavior
{
	/// Force to apply
	Vector3D force;

	/// Priority of the steering behavior for the accumulation of forces to apply to its vehicle
	/// (higher values mean higher priority)
	int32 priority;

	/// Weight to this behavior on the overal effect (range: 0-1)
	fixed_t weight;

	/// Maximum force to apply
	fixed_t maximumForce;

	/// Random deviation range
	fixed_t deviation;

	/// Calculate the force vector to apply to the provided vechile.
	/// @param vehicle: Vehicle to which the steering behavior is applied
	/// @param summingMethod: The method used to combine the forces of the vehicle's
	/// steering behaviors
	/// @return The force vector to apply to the provided vechile
	static Vector3D calculateForce(Vehicle vehicle, uint16 summingMethod);

	/// Class' constructor
	/// @param owner: Entity to which the behavior attaches to
	/// @param steeringBehaviorSpec: Specification that determines how to configure the behavior
	void constructor(Entity owner, const SteeringBehaviorSpec* steeringBehaviorSpec);

	/// Retrieve the specification used to configure the steering behavior.
	/// @return Specification used to configure the steering behavior
	const SteeringBehaviorSpec* getSteeringBehaviorSpec();

	/// Reset the steering behavior's state.
	void reset();

	/// Set the steering behavior's priority.
	/// @param priority: Priority of the steering behavior for the accumulation of forces to apply 
	/// to its vehicle (higher values mean higher priority)
	void setPriority(int32 priority);

	/// Retrieve the steering behavior's priority.
	/// @return Priority of the steering behavior for the accumulation of forces to apply 
	/// to its vehicle (higher values mean higher priority)
	int32 getPriority();

	/// Set the steering behavior's weight.
	/// @param weight: Weight to this behavior on the overal effect (range: 0-1)
	void setWeight(fixed_t weight);

	/// Retrieve the steering behavior's weight.
	/// @return Weight to this behavior on the overal effect (range: 0-1)
	fixed_t getWeight();

	/// Set the steering behavior's maximum force.
	/// @param maximumForce: Maximum force to apply
	void setMaximumForce(fixed_t maximumForce);

	/// Retrieve the steering behavior's maximum force.
	/// @return Maximum force that this steering behavior can apply
	fixed_t getMaximumForce();

	/// Calculate the force vector to apply.
	/// @param owner: Vehicle that owns the steering behavior
	/// @return The force vector to apply to the provided vechile
	virtual Vector3D calculate(Vehicle owner) = 0;
}

#endif
