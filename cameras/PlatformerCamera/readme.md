Implements a common platformer camera that follows an actor.

## Usage

To setup to your needs, call:

	PlatformerCameraMovementManager::configure(
		uint32 focusActorInGameType,
		uint32 focusActorLayer,
		uint32 cameraTriggerLayer,
		PixelSize boundingBoxSize,
		Vector3D boundingBoxDisplacement
	);
