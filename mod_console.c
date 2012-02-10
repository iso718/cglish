#include "cglish.h"

// Init and Quit
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
        isINS=true;
        ADD_LOG_ENTRY("mod_console[init]: Console initialisation done.\n");
}
void conQuit() {// Close the screen and free resources
        nocbreak();
        echo();
        endwin();
}

// Main
void conMainLoop(){
    unsigned int c;
    __conOutPrompt();
    while ((c=getch()))
    {
        if (keyFunc[c]) keyFunc[c]();
        else
        {
            //printw("%i",c);
            insch(c);
            move(getcury(stdscr),getcurx(stdscr)+1);
        }
    }
}

// Helpers
void __conOutPrompt(){
        iCurrentPromptLen=strlen(sCurrentPrompt);
        printw("%s>",sCurrentPrompt);
        ADD_LOG_ENTRY("mod_console[conoutprompt]: Current Prompt: <%s>, size: <%i>\n",sCurrentPrompt,iCurrentPromptLen);
}
void __conGetCurInput(char *sInput){
    // Remember current pos
    int x=getcurx(stdscr),y=getcury(stdscr);
    // move to beginning of line
    move(y,iCurrentPromptLen+1);
    //copy string from con
    innstr(sInput,MAX_INPUT);
    // move to old pos
    move(y,x);
}
int __conGetCurLineLength(){
    int i;
    char sInput[MAX_INPUT];
    __conGetCurInput(sInput);
    for (i=strlen(sInput)-1;i>=0;i--)
        if (sInput[i]!=' ')
            break;
    return i+1;
}
void __conClearLine(){
    move(getcury(stdscr),iCurrentPromptLen+1);
    clrtoeol();
}

// Keys
void __keyInit(){
    int i;
    for (i=0;i<sizeof(keyFunc)/sizeof(void (*)());i++) // init array
        keyFunc[i]=NULL;
    keyFunc[3]=&__keyCTRL_C; // CTRL-C
    keyFunc[4]=&__keyBackspace; // CTRL-D
    keyFunc[8]=&__keyBackspace;
    keyFunc[13]=&__keyEnter;
    keyFunc[127]=&__keyBackspace;
    keyFunc[258]=&__keyDown;
    keyFunc[259]=&__keyUp;
    keyFunc[260]=&__keyLeft;
    keyFunc[261]=&__keyRight;
    keyFunc[263]=&__keyBackspace;
    keyFunc[330]=&__keyDEL;
    keyFunc[331]=&__keyINS;
}
void __keyBackspace(){
    if (getcurx(stdscr) <= iCurrentPromptLen+1) return; // at prompt
    __keyLeft();
    delch();
}
void __keyDEL(){
    delch();
}
void __keyUp(){
    char *pHist=histGetPrev();
    if (!pHist) return;
    __conClearLine();
    printw("%s",pHist);
}
void __keyDown(){
    char *pHist=histGetNext();
    if (!pHist) return;
    __conClearLine();
    printw("%s",pHist);
}
void __keyLeft(){
    if (getcurx(stdscr) <= iCurrentPromptLen+1) return; // at prompt
    move(getcury(stdscr),getcurx(stdscr)-1);
}
void __keyRight(){
    int end= __conGetCurLineLength();
    if ((iCurrentPromptLen+end+1)==getcurx(stdscr)) return; // at last pos
    move(getcury(stdscr),getcurx(stdscr)+1);
}
void __keyCTRL_C(){
    conQuit();
    exit (0);
}
void __keyINS(){
    isINS = isINS ? false : true;
}
void __keyEnter(){
    char sInput[MAX_INPUT];
    __conGetCurInput(sInput);
    stripStr(sInput,sInput);
    if (!strIsEmpty(sInput))
        histAdd(sInput);
    printw("\n");
    __conOutPrompt();
}
