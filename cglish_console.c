#include "cglish.h"
#include <ncurses.h>

char tmp[100];
int nTmp=0;

void conInit(){ // inits the console
        initscr();
        nonl();
        intrflush(stdscr, FALSE);
        keypad(stdscr, TRUE);
        scrollok(stdscr,TRUE);
        raw();
        noecho();
        clear();
        __keyInit();
}

void __keyInit()
{
    int i;
    for (i=0;i<sizeof(keyFunc)/sizeof(void (*)());i++) // init array
        keyFunc[i]=NULL;
    keyFunc[3]=&__keyExit; // CTRL-C
    keyFunc[4]=&__keyBackspace; // CTRL-D
    keyFunc[8]=&__keyBackspace;
    keyFunc[13]=&__keyEnter;
    keyFunc[127]=&__keyBackspace;
    keyFunc[258]=&__keyDown;
    keyFunc[259]=&__keyUp;
    keyFunc[260]=&__keyLeft;
    keyFunc[261]=&__keyRight;
    keyFunc[263]=&__keyBackspace;
}

void __keyBackspace(){
    if (getcurx(stdscr) <= strlen(dataGetPrompt(pCurNode))+1) return; // at prompt
    __keyLeft();
    delch();
}
void __keyUp(){
    MSG_OUT("%s",hist_get(-1));
    //move(getcury(stdscr),strlen(dataGetPrompt(pCurNode))+1);
}
void __keyDown(){
    MSG_OUT("%s",hist_get(1));
    //move(getcury(stdscr),strlen(dataGetPrompt(pCurNode))+1);
}

void __keyLeft(){ // x=col, y=row
    move(getcury(stdscr),getcurx(stdscr)-1);
}
void __keyRight(){
    move(getcury(stdscr),getcurx(stdscr)+1);
    tmp[nTmp++]=inch();
}
void __keyExit(){
    __quit();
}

void __keyEnter(){
    char sInput[MAX_INPUT];
    mvinnstr(getcury(stdscr),0,sInput,MAX_INPUT-1);
    MSG_OUT("%s",sInput); // re-print line. Original line disapear after return..??
    hist_add(sInput);
    processUserInput(&sInput[strlen(dataGetPrompt(pCurNode))+1]);
    MSG_OUT("%s>",dataGetPrompt(pCurNode));
    refresh();
}

void conQuit() {// Close the screen and free resources
        nocbreak();
        echo();
        endwin();
}

void conMainLoop(){
    unsigned int c;
    MSG_OUT("%s>",dataGetPrompt(pCurNode));
    while ((c=getch()))
    {
        if (keyFunc[c]) keyFunc[c]();
        else
        {
            printw("%c",c);
        }
    }
}


