#ifndef MOD_CONSOLE_H_INCLUDED
#define MOD_CONSOLE_H_INCLUDED

#include <ncurses.h>

#define MAX_INPUT 1024

#define OUTPUT_INFO(MSG,...) printw(MSG,##__VA_ARGS__); // Go to info screen
#define OUTPUT_CMD(MSG,...) printw(MSG,##__VA_ARGS__); // Go to cmd screen

void conInit();
void __conModuleInit();
void conQuit();
void conMainLoop();
void __conDbgChar2Code(int nArg, char **sArr);
void __processInput(char *sInput);

// Struct holding the functions for key actions
void (*keyFunc[340])(); // Maybe not the best solution for keypress to function?

// Key Actions
void __keyHelp();
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


