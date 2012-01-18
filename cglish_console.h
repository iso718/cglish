#ifndef CGLISH_CONSOLE_H_INCLUDED
#define CGLISH_CONSOLE_H_INCLUDED

#include <ncurses.h>

#define INPUT_NORMAL 0
#define INPUT_NORMAL 0

enum {GETCOL,GETROW};

void conInit(); // inits the console
void __keyInit();
void conQuit(); // Close the screen and free resources
int conMainLoop(char*);

void __keyBackspace();
void __keyUp();
void __keyDown();
void __keyLeft();
void __keyRight();
int __getCurPos(int); //o=x, 1=y
void __getCurLine(chtype *sDst);

void conInfo(); // Print various settings
void conRefresh(); // refresh the screen
void conClear(); // empty the screen
void conOut(char *sOut); // console output
int conInChar(); // console single char input
void conInStr(char *sDst); // console string input. /0 terminated
void conInStrN(char *sDst, int nMax ); // console string input with max N chars. /0 terminated
void conTestChar(); // Testfunction which echoes and print the keycode

void (*keyFunc[270])(); // Maybe not the best solution for keypress to function?


#endif // CGLISH_CONSOLE_H_INCLUDED
