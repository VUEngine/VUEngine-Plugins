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
	fix10_6 weight;

	/// Maximum force to apply
	fix10_6 maximumForce;

	/// Random deviation range
	fix10_6 deviation;

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
	fix10_6 weight;
	fix10_6 maximumForce;
	fix10_6 deviation;

	void constructor(const SteeringBehaviorSpec* steeringBehaviorSpec);

	static Vector3D calculateForce(Vehicle vehicle);
	int32 getPriority();
	void setPriority(int32 value);
	fix10_6 getWeight();
	void setWeight(fix10_6 value);
	fix10_6 getMaximumForce();
	void setMaximumForce(fix10_6 value);
	void reset();
	const SteeringBehaviorSpec* getSteeringBehaviorSpec();
	Vector3D getForce();

	virtual Vector3D calculate(Vehicle owner) = 0;
}


#endif
