<div id="top"></div>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/prograG2/tpfinal-frogger">
	<img src="images/logo.jpeg" alt="Logo" width="120" height="120">
  </a>

<h3 align="center">Frogger</h3>

  <p align="center">
	Trabajo Práctico Final de 22.07 - Programación I, curso de 1er año de Ingeniería Electrónica del Instituto Tecnológico Buenos Aires (<a href="https://www.itba.edu.ar/">ITBA</a>).
	<br />
	<a href="https://github.com/prograG2/tpfinal-frogger"><strong>Explore the docs »</strong></a>
	<br />
	<br />
	<a href="https://drive.google.com/file/d/1EKTfY6lPXKl7aFBDEpkf0zVYqBhvdM_r/view?usp=sharing">View Demo</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
	<li>
	  <a href="#about-the-project">About The Project</a>
	</li>
	<li>
	  <a href="#features">Features</a>
	</li>
	<li>
	  <a href="#getting-started">Getting Started</a>
	  <ul>
		<li>
			<a href="#prerequisites">Prerequisites</a>
		</li>
		<li><a href="#installation">Installation</a></li>
	  </ul>
	</li>
	<li>
	  <a href="#usage">Usage</a>
	  <ul>
	    <li><a href="#corriendo-el-juego">Corriendo el juego</a></li>
	  </ul>
	</li>
	<li><a href="#contact">Contact</a></li>
	<li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>


<br />

<!-- ABOUT THE PROJECT -->
## About The Project

<br />
<div align="center">
  <a href="https://github.com/prograG2/tpfinal-frogger">
	<img src="images/collage.jpg" alt="Screenshot" width="600" height="500">
  </a>
</div>
<br />

Este proyecto se corresponde con el trabajo práctico final del curso 22.07 - Programación I, del primer año de Ingeniería Electrónica del Instituto Tecnológico Buenos Aires (<a href="https://www.itba.edu.ar/">ITBA</a>).

* Fecha de cursada: 2021 Q1
* Fecha de presentación: febrero de 2022

La consigna fue implementar el clásico juego *Frogger* en lenguaje `C` para ejecutarse tanto en una
**PC** con interfaz gráfica como en una **Raspberry Pi** con interfaz de display matricial y joystick.

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- Features -->
## Features

A continuación se mencionan algunas de las característimas destacables de la implementación, tanto las comunes para ambas plataformas como las específicas de cada una.

### Generales
* **Menú**: el juego cuenta con un sistema de menú, caracterizable en 3 partes:
  * *Menú principal*: al que se llega al inicar ejecutar el juego. Desde el mismo, se puede:
    * Pasar al ingreso de nombre del jugador para posteriormente iniciar la partida
    * Seleccionar entre tres dificultades: fácil, normal, difícil
    * Ver el ranking de jugadores
    * Ver los créditos
    * Salir del juego
  * *Menú de pausa*: permite reiniciar la partida, continuarla, o volver al menú principal. Muestra el nombre del jugador, su puntaje actual, y su puntaje máximo si le corresponde
  * *Menú de game over*: permite reiniciar la partida o volver al menú principal. Muestra el nombre del jugador, el puntaje que obtuvo, y si logró batir su récord

* **Audio**: se cuenta con cinco músicas según la ubicación en la que uno esté dentro del juego, además de diversos efectos de sonidos, tanto en el menú como en la partida en sí
* **Ranking**: cada jugador se irá registrando en el mismo cada vez que pierda una partida y haya logrado un puntaje mayor a 0. Si el jugador ya estaba en el ranking, solo se actualizará en él si lo superara. De no ingresar un nombre, se le asignará el de `PLAYER`. Se lo puede visualizar desde el menú principal
* **Créditos**: dentro del menú principal, se puede acceder a la sección de cŕeditos

### PC

### RPi


<p align="right">(<a href="#top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

Para ambas plataformas, será necesario contar con las herramientas `gcc` y `make`, además de estar corriendo un Unix-like OS.

#### PC
* <a href="https://github.com/liballeg/allegro_wiki/wiki">allegro5</a>
  * Arch Linux
	```sh
	sudo pacman -Syu
	sudo pacman -S allegro
	```
  * Ubuntu 18.04+
	```sh
	sudo apt-get update
	sudo add-apt-repository ppa:allegro/5.2
	sudo apt-get install liballegro*5.2 liballegro*5-dev
	```

#### RPi
<br />

### Installation

1. Clonar el repositorio
	```sh
	git clone https://github.com/prograG2/tpfinal-frogger.git
	```
2. Entrar al directorio root
	```sh
	cd tpfinal-frogger
	```
3. Compilar el proyecto y crear el ejecutable
	```sh
	make
	```

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

### Corriendo el juego
El ejecutable del juego se encuentra en `/bin`, el mismo directorio donde se encontrará oportunamente el ranking de jugadores.

Para ejecutarlo:
* Desde `/bin`
	```sh
	./frogger_PC
	```
	ó
	```sh
	./frogger_RPI
	```
* Desde directorio root
	```sh
	make run
	```
	> Correr `make run` en el ítem 3 de la instalacion compila, crea el ejecutable y lo ejecuta



<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

AGRIPPINO, Franco - fagrippino@itba.edu.ar
<br />
ÁLVAREZ, Matías Ezequiel - matalvarez@itba.edu.ar
<br />
CASTRO, Tomás Agustín - tomacastro@itba.edu.ar
<br />
HEIR, Alejandro Nahuel - aheir@itba.edu.ar

Project Link: [https://github.com/prograG2/tpfinal-frogger](https://github.com/prograG2/tpfinal-frogger)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* Cátedra de 22.07 - Programación I
  * JACOBY, Daniel Andrés
  * MAGLIOLA, Nicolás
  * VACATELLO, Pablo Daniel
  * *Ayudantes*
* [Allegro](https://github.com/liballeg/allegro_wiki/wiki)
* [Sprites de tortugas, autos, muerte, y follaje](https://www.pinclipart.com/pindetail/hhxmRb_frogger-arcade-graphic-frogger-sprite-sheet-clipart/)
* [Sprite de coin](https://www.pinclipart.com/pindetail/ibiTJwi_coin-sprite-sheet-png-clipart/)
* Música
  * Menú principal: [VipeorofVic](https://www.youtube.com/watch?v=iXHix_kdJWI&t=101s), Dark Souls III - Main Theme - 8 Bit Revision
  * Ranking: [Jaxxtir](https://www.youtube.com/watch?v=ykt-5q13GGs), GTA San Andreas Theme - 8 Bit Remix
  * Créditos: [8 Bit Universe](https://www.youtube.com/watch?v=kRkBnSbwvk8), Curb Your Enthusiasm Theme - 8 Bit
  * Partida: [Super Jumbo Trainer 98](https://www.youtube.com/watch?v=t4xAVyQ3LpY&t=107s), Frogger (Arcade) Stage Theme Extended
  * Menú de pausa: [Retro Game Audio](https://soundcloud.com/retrogameaudio/firelink-shrine-nes-famicom), Dark Souls - Firelink Shrine (NES/ Famicom + VRC6 audio)
  * Menú de game over: [MB Music](https://www.youtube.com/watch?v=br3OzOrARh4), Game Over (8-Bit Music)
* [Simple SDL2 Audio](https://github.com/jakebesworth/Simple-SDL2-Audio)
* [algif5](https://github.com/allefant/algif5)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
