/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
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

	// Vector3D accumulation method: kPrioritized, kWeightedAverage
	uint16 summingMethod;

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

	uint16 getSummingMethod();
	bool updateForce();
	VirtualList getSteeringBehaviors();
	fixed_t getFrictionMassRatio();

	override void ready(bool recursive);
	override void update();
	override fixed_t getRadius();
	override bool applyForce(const Vector3D* force, bool checkIfCanMove);
}


#endif
