#ifndef CGLISH_TOOLS_H_INCLUDED
#define CGLISH_TOOLS_H_INCLUDED

void stripStr(char*, char*); // strips the user input
int __isCharStripRelevant(int);
int splitStrToArr(char*, char***); // used to split the user input
void freeArrFromStr(int,char**); // frees memory alloc'd in splitStrToArr
void exitOnNULLPointer(void* pToCheck);  //Exit if pointer is NULL

#endif // CGLISH_TOOLS_H_INCLUDED