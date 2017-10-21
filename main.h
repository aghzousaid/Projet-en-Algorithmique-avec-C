#ifndef MENU
#define MENU

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dico.h"



void loop();
void afficher_menu();
void clean(const char*, FILE*);
int ChoixEntrer();
int getInt(int);
char* getString();

#endif
