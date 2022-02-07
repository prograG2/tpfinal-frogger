## Directorio `/lib` (libraries)

Contiene la biblioteca `rpiutils`, que concentra los objetos de los drivers de RPi para el display y para el joystick, proveídos por la Cátedra.

Se linkea en el Makefile si se está en la plataforma correspondiente.

> Para el audio de la RPi, se está empleando [simpleSDL2audio](https://github.com/jakebesworth/Simple-SDL2-Audio), que se ha ido actualizando últimamente. El código fuente está en `src/platform/rpi/simpleSDL2audio`.