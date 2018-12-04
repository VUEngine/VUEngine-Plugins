VUEngine Plugin: PlatformerCamera
==========================================

Implements a common platformer camera.

It follows an entity.


USAGE
-----

Add the following to the PLUGINS variable in your project's `config.make` file to include this plugin:

	vuengine/plugins/cameras/Platformer


To setup to your needs, call:

	PlatformerCameraMovementManager::configure(u32 focusEntityInGameType, u32 focusEntityLayer, u32 cameraTriggerLayer, PixelSize boundingBoxSize, Vector3D boundingBoxDisplacement);