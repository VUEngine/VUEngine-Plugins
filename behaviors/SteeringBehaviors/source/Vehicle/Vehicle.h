/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Actor.h>
#include <SteeringBehavior.h>


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// A Vehicle Spec
/// @memberof Vehicle
typedef struct VehicleSpec
{
	ActorSpec actorSpec;

	/// Vector3D accumulation method: kPrioritized, kWeightedAverage
	uint16 summingMethod;

	/// If true, the steering behavior is run at half speed
	bool runSteeringBehaviorsAtHalfSpeed;

} VehicleSpec;

/// A Vehicle spec that is stored in ROM
/// @memberof Vehicle
typedef const VehicleSpec VehicleROMSpec;


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

///
/// Class Vehicle
///
/// Inherits from Actor
///
/// Implements various physics based behaviors to steer AI actors.
class Vehicle : Actor
{
	/// @protectedsection

	/// Total force to apply to the vehicle's body
	Vector3D accumulatedForce;

	/// Cache the vehicle's radius
	fixed_t radius;

	/// Cache the friction to mass ratio
	fixed_t frictionMassRatio;

	/// If true, a collision check is performed before trying to move the vehicle
	bool checkIfCanMove;

	/// Keeps track of the cycle when running the steering behaviors at half the speed
	int8 evenCycle;

	/// Linked list of steerhing behaviors
	VirtualList steeringBehaviors;

	/// @publicsection

	/// Class' constructor
	/// @param vehicleSpec: Specification that determines how to configure the vehicle
	/// @param internalId: ID to keep track internally of the new instance
	/// @param name: Name to assign to the new instance
	void constructor(VehicleSpec* vehicleSpec, int16 internalId, const char* const name);

	/// Retrieve the object's radius.
	/// @return Radius
	override fixed_t getRadius();

	/// Make the vehicle ready to start operating once it has been completely intialized.
	/// @param recursive: If true, the ready call is propagated to its children, grand children, etc.
	override void ready(bool recursive);

	/// Update this instance's logic.
	override void update();

	/// Apply a force to the vehicle's body.
	/// @param force: Force to be applied
	/// @param checkIfCanMove: If true, the vehicle checks that none of its colliders will
	/// @return True if the force was succesfully applied to the vehicle's body
	override bool applyForce(const Vector3D* force, bool checkIfCanMove);

	/// Retrieve the vehicle's list of steering behaviors.
	/// @return The vehicle's list of steering behaviors
	VirtualList getSteeringBehaviors();

	/// Retrieve the vehicle's friction to mass ratio.
	/// @return The vehicle's friction to mass ratio
	fixed_t getFrictionMassRatio();

}


#endif
