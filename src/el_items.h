/*
 * File:      el_items.h
 * Copyright: (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:   GPLv2 (see file COPYING)
 *
 */

#ifndef EL_ITEMS_H
#define EL_ITEMS_H


#include <string.h>
#include <stdbool.h>

#include "el_defs.h"





elState loadSingleItem(FILE * stream, Item * item, int * linenumber);
elState loadAllItems(List * list, char filepath[]);

void lookup(List * list, char name[]);

void   initItem(Item * item);
Item * addItem(List * list, Item * item);
Item * findItemId(Item * head, int id);
Item * findItemName(Item * head, char name[]);
Item * cloneItem(const Item * item);

void   printItems(List * list);
void   showItem(Item * item);

void   searchItem(List * list, char name[]);

void freeItemList(List * list);

char   getHead(char * line);


#endif // EL_ITEMS_H
