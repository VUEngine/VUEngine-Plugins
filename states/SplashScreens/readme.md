VUEngine Plugin: SplashScreens
==============================

A collection of default splash screens.
- Precaution screen
- IPD/Focus adjustment screen
- Automatic Pause selection screen
- Language selection screen

![Preview Image](preview.png)


USAGE
-----

See `source/config.h` for numerous available macros that allow you to modify the splash screens' appearance. Define the desired macro in your game's `config.h` file to override.

In addition, you can modify the screens' order through the `SplashScreenState::setNextState()` function. You will at least have to call that function on the language selection screen to define which state should be switched to after the splash screen sequence. The recommended way is to call the function from your game's main function before calling `Game::start();`.
