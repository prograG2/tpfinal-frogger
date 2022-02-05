## Directorio `/lib` (libraries)

Contiene dos **bibliotecas** creadas a partir de códigos objeto, que se linkean en el Makefile de ser necesarias. Dichas bibliotecas son:

- *[algif5](https://github.com/allefant/algif5)*: soporte de gifs para allegro5
  
	> Por problemas de linkeo, el codigo fuente está en `/src/platform/pc/algif5`. Desde el Makefile, se compila y se crea la biblioteca correspondiente.

- *rpiutils*: contiene los objetos de los drivers de display, joystick ~~y audio para la RPi~~, proveídos por la cátedra.
	> Se está usando la biblioteca [simpleSDL2audio](https://github.com/jakebesworth/Simple-SDL2-Audio), la cual se ha ido actualizando últimamente. El código fuente está en `src/platform/rpi/simpleSDL2audio`.

