#include "cglish.h"
#include <ncurses.h>

void conInit(){ // inits the console
        initscr();
        nonl();
        intrflush(stdscr, FALSE);
        keypad(stdscr, TRUE);
        scrollok(stdscr,TRUE);
        cbreak();
        noecho();
        conClear();
}
void conQuit() {// Close the screen and free resources
        nocbreak();
        echo();
        endwin();
}

int conMainLoop(char *sDst){
    unsigned int c;
    int nCurPos=0;
    sDst[0]='\0';
    while ((c=getch())!=13)
        switch (c)
        {
        case 13: //Return
            return NORMAL;
        case 8: //Backspace
        case 127:
        case 263:
            __keyBackspace();
            break;
        case 258:   // History backward
            __keyArrowDown();
            break;
        case 259:  // History forward
            __keyArrowUp();
            break;
        case 260:   // Cursor left
            __keyArrowLeft();
            break;
        case 261:   //Cursor rightl
            __keyArrowRight();
            break;
        default:
            printw("%c",c);
            sDst[nCurPos]='\0';
        }
    return '\0';
}

void __keyBackspace(){

}

void __keyArrowUp(){
    printw("KeyUp");
}
void __keyArrowDown(){
    printw("KeyDown");
}
void __keyArrowLeft(){
    printw("KeyLeft");
}
void __keyArrowRight(){
    printw("KeyRight");
}




void conInfo() {// Print various settings
    printw("Lines: %d, Cols: %d\n",LINES,COLS);
}

void conRefresh() {// refresh the screen
    refresh();
}
void conClear(){ // empty the screen
    clear();
}
void conOut(char *sOut) {// console output
    printw("%s",sOut);
}
int conInChar() {// console single char input
    return getch();
}
void conInStr(char *sDst) {// console string input. /0 terminated
    int i=0, c;
    while ((c=conInChar())!=13)
        sDst[i++]=c;
    sDst[i]='\0';

}
void conInStrN(char *sDst, int nMax ) { // console string input with max N chars. /0 terminated
    int i=0, c;
    while ((c=conInChar())!=13)
    {
        sDst[i++]=c;
        if (i==nMax-1)
            break;
    }
    sDst[i]='\0';
}


void conTestChar() {// Testfunction which echoes and print the keycode
    int c;
    while ((c=getch())){
      switch (c)
      {
        case 8:
        case 127:
        case 263:
            printw("BACKSPACE, %d",c);
            break;
        case 99:
            conClear();
            printw("Screen cleared\nKeycode: <%d>, char: <%c>", c,c);
            break;
        case KEY_LEFT:
            printw("KEY LEFT");
            break;
        case 113:
            printw ("quit\n");
            return;
        case 114:
            printw ("refresh");
            conRefresh();
            break;
        case 13:
            printw ("return");
            break;
        default:
            printw ("Keycode: <%d>, char: <%c>", c,c);
      }
      printw("\n\r");

    }
}
