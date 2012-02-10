#ifndef MOD_CONSOLE_H_INCLUDED
#define MOD_CONSOLE_H_INCLUDED

#include <ncurses.h>

#define MAX_INPUT 1024


void conInit();
void conQuit();
void conMainLoop();

// Struct holding the functions for key actions
void (*keyFunc[340])(); // Maybe not the best solution for keypress to function?

// Key Actions
void __keyInit();
void __keyBackspace();
void __keyUp();
void __keyDown();
void __keyLeft();
void __keyRight();
void __keyCTRL_C();
void __keyEnter();
void __keyDEL();
void __keyINS();

// Helpers
void __conOutPrompt();
void __conGetCurInput(char*);
void __conClearLine();
int __conGetCurLineLength();

// Global Vars
int iCurrentPromptLen;
bool isINS;
#endif // MOD_CONSOLE_H_INCLUDED


