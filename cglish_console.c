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
        clear();
        __keyInit();
}

void __keyInit()
{
    int i;
    for (i=0;i<sizeof(keyFunc)/sizeof(void (*)());i++)
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
    __keyLeft();
    delch();
}
void __keyUp(){

}
void __keyDown(){

}
void __keyLeft(){ // x=col, y=row
    move(getcury(stdscr),getcurx(stdscr)-1);
}
void __keyRight(){
    move(getcury(stdscr),getcurx(stdscr)+1);
}
void __keyExit(){
    __quit();
}

void __keyEnter(){

}

void conQuit() {// Close the screen and free resources
        nocbreak();
        echo();
        endwin();
}

void conMainLoop(){
    unsigned int c;
    while ((c=getch()))
    {
        if (keyFunc[c]) keyFunc[c]();
        else
        {
            printw("%i",c);
        }
    }
}


