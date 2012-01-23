#include "cglish.h"
#include <ncurses.h>


void conInit(){ // inits the console
        initscr();
        nonl();
        intrflush(stdscr, FALSE);
        keypad(stdscr, TRUE);
        scrollok(stdscr,TRUE);
        raw();
        noecho();
        conClear();
        __keyInit();
}

void __keyInit()
{
    int i;
    for (i=0;i<sizeof(keyFunc)/sizeof(void (*)());i++)
        keyFunc[i]=NULL;
    keyFunc[8]=&__keyBackspace;
    keyFunc[127]=&__keyBackspace;
    keyFunc[258]=&__keyDown;
    keyFunc[259]=&__keyUp;
    keyFunc[260]=&__keyLeft;
    keyFunc[261]=&__keyRight;
    keyFunc[263]=&__keyBackspace;
}

void __keyBackspace(){

}
void __keyUp(){

}
void __keyDown(){

}
void __keyLeft(){

}
void __keyRight(){

}
int __getCurPos(int xy){
    int x,y;
    getyx(stdscr,y,x);
    MSG_DBG("x: %i, y: %i",x,y);
    return xy==GETROW ? y : x;
}
void __getCurLine(chtype *sDst){
    int y,x;
    getyx(stdscr,y,x);
    move(y,0);
    inchnstr(sDst,MAX_INPUT);
}

void __curMvLeft(int n){
}
void __curMvRight(int n){
}


void conQuit() {// Close the screen and free resources
        nocbreak();
        echo();
        endwin();
}

int conMainLoop(char *sDst){
    unsigned int c;
    int nCurPos;
    chtype inputStr[MAX_INPUT];
    sDst[0]='\0';
    while ((c=getch())!=13)
    {
        if (keyFunc[c]) keyFunc[c]();
        else
        {
            printw("%c",c);
        }
    }
    __getCurLine(inputStr);
    MSG_DBG("\n<%s>\n",inputStr);
    return '\0';
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
