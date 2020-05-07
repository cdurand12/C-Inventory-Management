#ifndef PROJECT3_H
#define PROJECT3_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "item.h"



void updateItem(itemNode *p, struct item *newItem);
itemNode *addItem(itemNode *p, struct item *newItem);
int myGetLine(char line[], int maxinput);
void copy(char to[], char from[]);
int isDigit(int c);
void printInventory(itemNode *p);
double checkInventory(itemNode *inventory, itemNode *item, int amount);



#endif
