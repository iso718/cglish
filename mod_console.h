#ifndef MOD_CONSOLE_H_INCLUDED
#define MOD_CONSOLE_H_INCLUDED

/*
mod_console
IS MANDATORY
Do: The shell
Might be replaced by smth other (grafical?)
*/


// Define
#define MAX_INPUT 1024

// Include
#include "cglish.h"
#include <ncurses.h>


#define OUTPUT_INFO(MSG,...) printw(MSG,##__VA_ARGS__); // Go to info screen
#define OUTPUT_CMD(MSG,...) printw(MSG,##__VA_ARGS__); // Go to cmd screen
#define OUTPUT_ERR(MSG,...) printw("Error: "MSG,##__VA_ARGS__); // Go to cmd screen
#define OUTPUT_HELP(MSG,...) printw(MSG,##__VA_ARGS__); // Go to cmd screen

/* Public Functions */
void conInit();
void conQuit();
void conMainLoop();
/* Public global vars */
// none

/* Private Functions */
void __conModuleInit();
void __conDbgChar2Code(int nArg, char **sArr);
void __processInput(char *sInput);
void __conOutPrompt();
void __conGetCurInput(char*);
void __conClearLine();
int __conGetCurLineLength();
// Private global vars
int iCurrentPromptLen;
bool isINS;
void (*keyFunc[340])(); // Key to action functionallity
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
void __keyPageUp();
void __keyPageDown();


#endif // MOD_CONSOLE_H_INCLUDED


