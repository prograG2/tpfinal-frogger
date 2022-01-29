# Directorio */lib*

Contiene dos **bibliotecas** creadas a partir de códigos objeto, que se linkean en el Makefile principal de ser necesarias. Dichas bibliotecas son:

- *algif*: soporte de gifs para allegro5. Código fuente: [algif5](https://github.com/allefant/algif5)
	> Por problemas de linkeo, el codigo fuente está en */src/platform/pc/algif5*. Desde el Makefile principal, se compila y se crea la biblioteca correspondiente.
- *rpiutils*: contiene los objetos de los drivers de display, joystick y audio para la RPi, proveídos por la cátedra.

