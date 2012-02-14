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
        __processInput(sInput);
    printw("\n");
    __conOutPrompt();
}

void __processInput(char *sInput){
    /* RULES
    <ARG> -> look for and exec function in current level
    <CMD> -> switch to level cmd
    <CMD> <CMD> -> switch to cor level
    <CMD> <ARG> -> exec in cmd with arg but stay in cur level
    */
    ADD_DEBUG_ENTRY("mod_console[__processUserInput]: Process Input  <%s>\n",sInput);
    char **sArr=NULL;
    void *pNode=pCurrentNode;
    int nArg=0,i=0;
    histAdd(sInput);
    nArg=splitStrToArr(sInput,&sArr);
    i=0;
    while (i<nArg && (pNode=getNodeByPrompt(pNode,sArr[i])))
    {
        ADD_DEBUG_ENTRY("mod_console[__processUserInput]: Found User Arg <%i> <%s> at <%p>\n",i,sArr[i],pNode);
        i++;
    }
    if (i==nArg) // Only CMD in sArg
        switchToNode(pNode);

    freeArrFromStr(nArg,sArr);
}
