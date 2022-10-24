/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <SteeringBehavior.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef struct VehicleSpec
{
	// animated entity
	ActorSpec actorSpec;

	// Force accumulation method: kPrioritized, kWeightedAverage
	int32 summingMethod;

	/// Run steering behaviors at half speed
	bool runSteeringBehaviorsAtHalfSpeed;

} VehicleSpec;

/// @ingroup base
class Vehicle : Actor
{
	Vector3D accumulatedForce;
	fixed_t radius;
	bool checkIfCanMove;
	int8 evenCycle;

	VirtualList steeringBehaviors;

	/// @publicsection
	void constructor(VehicleSpec* vehicleSpec, int16 internalId, const char* const name);

	int32 getSummingMethod();
	bool updateForce();
	VirtualList getSteeringBehaviors();
	Velocity getVelocity();
	fixed_t getFrictionMassRatio();

	virtual const Vector3D* getReferencePosition();
	virtual const Direction3D* getDirection3D();

	override void ready(bool recursive);
	override void update(uint32 elapsedTime);
	override fixed_t getRadius();
	override void applyForce(const Force* force, bool checkIfCanMove);
}


#endif
