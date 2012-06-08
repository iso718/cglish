#ifndef CGLISH_H_INCLUDED
#define CGLISH_H_INCLUDED


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define RETURN_SUCCESS EXIT_SUCCESS
#define RETURN_FAILURE EXIT_FAILURE

#include "cglish_modules.h"
void test();
void checkPointer(void* pToCheck);  //Exit if pointer is NULL


#endif // CGLISH_H_INCLUDED


/*
DONE: Konzept Module einbinden
Module werden statisch eingebunden. Jedes Modul muss seinen header und seine init function im cglish header eintragen.
*/
/*
TODO: Btree implementation
+) struct node
+) struct data:
+) func abort if pointer is  NULL
+) func create node
-) func addchild
+) func creat node data
-) func add node
*/


