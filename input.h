/**
 * @file getchmod.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

/* reads from keypress, doesn't echo */
int getch(void);

/* reads from keypress, echoes */
int getche(void);