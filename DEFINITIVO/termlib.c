/**
 * @file termlib.c
 * @author Daniel Jacoby
 * @brief Linux support for keyboard functions for getch and getche and kbhit ansy.sys Like functions added
 * @version 3.0
 * @date 2016-10-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include "termlib.h"
 
// Turns terminal line buffering on or off
 
void changemode(int mode)
{
  static struct termios oldt, newt;
 
  if ( mode == BUFFERED_OFF )
  {
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  }
  else
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}
 
// Check if a key has been pressed at terminal 
int kbhit (void)
{
  struct timeval tv;
  fd_set rdfs;
 
  tv.tv_sec = 0;
  tv.tv_usec = 0;
 
  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);
 
  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);
 
}

// Get next immediate character input (no echo)
int getch(void)
{
	unsigned char temp;
	
	/* stdin = fd 0 */
	if(read(0, &temp, 1) != 1)
		return 0;
	
	return temp;
}

// Get next immediate character input (with echo)
int getche(void)
{
	unsigned char temp;

	/* stdin = fd 0 */
	if(read(0, &temp, 1) != 1)
		return 0;

	putchar(temp);	//Echo

	return temp;
}

// Ansi.sys like

// Set cursor position
void gotoxy(int x, int y) { printf("\x1B[%d;%df", y, x); }

// Clear terminal screen and set cursor to top left
void clrscr() { printf("\x1B[2J\x1B[0;0f"); }


