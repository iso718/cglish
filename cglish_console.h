#ifndef CGLISH_CONSOLE_H_INCLUDED
#define CGLISH_CONSOLE_H_INCLUDED

#include <ncurses.h>


void conInit(); // inits the console
void __keyInit();
void conQuit(); // Close the screen and free resources
void conMainLoop();

void __keyBackspace();
void __keyUp();
void __keyDown();
void __keyLeft();
void __keyRight();
void __keyExit();
void __keyEnter();
int __getCurPos(int); //o=x, 1=y
void __getCurLine(chtype *sDst);

void (*keyFunc[270])(); // Maybe not the best solution for keypress to function?


#endif // CGLISH_CONSOLE_H_INCLUDED
