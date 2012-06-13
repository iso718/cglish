#ifndef CGLISH_CONSOLE_H_INCLUDED
#define CGLISH_CONSOLE_H_INCLUDED

#include <ncurses.h>

#define INPUT_NORMAL 0
#define INPUT_NORMAL 0

void conInit(); // inits the console
void conQuit(); // Close the screen and free resources
int conMainLoop(char*);

void __keyBackspace();
void __keyArrowUp();
void __keyArrowDown();
void __keyArrowLeft();
void __keyArrowRight();


void conInfo(); // Print various settings
void conRefresh(); // refresh the screen
void conClear(); // empty the screen
void conOut(char *sOut); // console output
int conInChar(); // console single char input
void conInStr(char *sDst); // console string input. /0 terminated
void conInStrN(char *sDst, int nMax ); // console string input with max N chars. /0 terminated
void conTestChar(); // Testfunction which echoes and print the keycode


#endif // CGLISH_CONSOLE_H_INCLUDED
