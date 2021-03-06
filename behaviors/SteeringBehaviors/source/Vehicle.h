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
	int summingMethod;

	/// Run steering behaviors at half speed
	bool runSteeringBehaviorsAtHalfSpeed;

} VehicleSpec;

/// @ingroup base
class Vehicle : Actor
{
	Vector3D steeringForce;
	Vector3D accumulatedForce;
	VehicleSpec* vehicleSpec;
	fix10_6 radius;
	//fix10_6 frictionMassRatio;
	bool checkIfCanMove;
	s8 evenCycle;

	VirtualList steeringBehaviors;

	/// @publicsection
	void constructor(VehicleSpec* vehicleSpec, s16 internalId, const char* const name);

	int getSummingMethod();
	bool updateForce();
	VirtualList getSteeringBehaviors();
	Velocity getVelocity();
	fix10_6 getFrictionMassRatio();

	virtual const Vector3D* getReferencePosition();
	virtual const Direction3D* getDirection3D();

	override void ready(bool recursive);
	override void update(u32 elapsedTime);
	override fix10_6 getRadius();
	override void addForce(const Force* force, bool checkIfCanMove);
}


#endif
