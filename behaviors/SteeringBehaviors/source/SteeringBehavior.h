/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
	kTargetReached = kEventEngineLast + 1,
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
	int32 priority;

	/// Weight to this behavior on the overal effect (range: 0-1)
	fixed_t weight;

	/// Maximum force to apply
	fixed_t maximumForce;

	/// Random deviation range
	fixed_t deviation;

} SteeringBehaviorSpec;

typedef const SteeringBehaviorSpec SteeringBehaviorROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/// @ingroup base
class SteeringBehavior : Behavior
{
	const SteeringBehaviorSpec* steeringBehaviorSpec;

	Vector3D force;

	// higher value has more priority
	int32 priority;
	fixed_t weight;
	fixed_t maximumForce;
	fixed_t deviation;

	void constructor(const SteeringBehaviorSpec* steeringBehaviorSpec);

	static Vector3D calculateForce(Vehicle vehicle);
	int32 getPriority();
	void setPriority(int32 value);
	fixed_t getWeight();
	void setWeight(fixed_t value);
	fixed_t getMaximumForce();
	void setMaximumForce(fixed_t value);
	void reset();
	const SteeringBehaviorSpec* getSteeringBehaviorSpec();
	Vector3D getForce();

	virtual Vector3D calculate(Vehicle owner) = 0;
}


#endif
