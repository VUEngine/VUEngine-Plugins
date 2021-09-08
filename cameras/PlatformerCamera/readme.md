Implements a common platformer camera that follows an entity.

Usage
-----

To setup to your needs, call:

	PlatformerCameraMovementManager::configure(
		uint32 focusEntityInGameType,
		uint32 focusEntityLayer,
		uint32 cameraTriggerLayer,
		PixelSize boundingBoxSize,
		Vector3D boundingBoxDisplacement
	);
