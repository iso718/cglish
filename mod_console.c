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
        isINS=true; //not used
        __conModuleInit();
        ADD_LOG_ENTRY("mod_console[init]: Console initialisation done.\n");
}

void __conModuleInit()
{
        void *pConsoleNode, *pDebugNode;
        pConsoleNode=addNode(NULL,"con","Console tools and functions",NULL);
        pDebugNode=addNode(pConsoleNode,"keycode","Tools around keycodes",NULL);
        addNode(pDebugNode,"char2code","Convert gives chars to there keycode. ",&__conDbgChar2Code);
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

void __conDbgChar2Code(int nArg, char **sArr)
{
    int i=0;
    if (nArg==0) //no Arg given
        return;
    if (strcmp(sArr[0],"0")==0) // realtime
        { OUTPUT_INFO("Start realtime live. Press <q> to exit\n");
        unsigned int c;
        while ((c=getch())!='q')
        {
            OUTPUT_INFO("Key Entered: <%c> Keycode: <%i> <%#x> \n",c,c,c);
        }
    }
    else
    {
        while (sArr[0][i])
        {
            OUTPUT_INFO("Key Entered: <%c> Keycode: <%i> <%#x>\n",sArr[0][i],sArr[0][i],sArr[0][i]);
            i++;
        }
    }
}

// Helpers
void __conOutPrompt(){
        iCurrentPromptLen=strlen(sCurrentPrompt);
        OUTPUT_CMD("%s>",sCurrentPrompt);
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
    keyFunc[63]=&__keyHelp;
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
    OUTPUT_CMD("\n");
    stripStr(sInput,sInput);
    if (!strIsEmpty(sInput))
        {
            histAdd(sInput);
            __processInput(sInput);
        }
    __conOutPrompt();
}

void __keyHelp(){
    // ? should show current nodes and his children's help
    OUTPUT_INFO("?\nReal man help themself!\n");
    __conOutPrompt();
}

void __processInput(char *sInput){
    ADD_DEBUG_ENTRY("mod_console[__processUserInput]: Process Input  <%s>\n",sInput);
    int i;
    void *pTmpNode;
    char **sArr=NULL; int nArg=0;
    nArg=splitStrToArr(sInput,&sArr);

    for (i=0;i<nArg;i++)
    {
        ADD_DEBUG_ENTRY("mod_console[__processUserInput]: Current: <%i> String: <%s> pCurrentNode: <%p> func: <%p>\n",i, sArr[i],pCurrentNode,pCurrentNode->pFunc);
        if ((pTmpNode=getNodeByPrompt(NULL,sArr[i]))) // Is cmd
        {
            switchToNode(pTmpNode);
            continue;
        }
        if (pCurrentNode->pFunc) // Function exist? Call Func with remaining arg's
        {
            pCurrentNode->pFunc(nArg-i,&sArr[i]);
            break;
        }
        OUTPUT_INFO("Fehler: Befehl nicht gefunden und keine Funktion definiert.\n");
        }
    freeArrFromStr(nArg,sArr);
}
