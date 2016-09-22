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





enum elState loadSingleItem(FILE * stream, struct Item * item, int * linenumber);
enum elState loadAllItems(struct List * list, char filepath[]);

void lookup(struct List * list, char name[]);

void   initItem(struct Item * item);
struct Item * addItem(struct List * list, struct Item * item);
struct Item * findItemId(struct Item * head, int id);
struct Item * findItemName(struct Item * head, char name[]);
struct Item * cloneItem(const struct Item * item);

void   printItems(struct List * list);
void   showItem(struct Item * item);

void   searchItem(struct List * list, char name[]);

void freeItemList(struct List * list);

char   getHead(char * line);


#endif // EL_ITEMS_H
